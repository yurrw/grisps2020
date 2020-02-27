package main

// sed -E '/tcp$/!d; s!^([a-zA-Z0-9\-]+)\s+([0-9]+)/\w+!\t\2: "\1",!;' /etc/services  > json.json
import (
	"encoding/json"
	"fmt"
	"html/template"
	"io/ioutil"
	"log"
	"net"
	"net/http"
	"os"
	"strconv"
	"strings"
	"sync"
)

type PortsJson struct {
	Ports []Ports `json:"ports"`
}

type Response struct {
	Ps map[int]string
}
type Response2 struct {
	minV bool
}
type Ports struct {
	Description string `json:"description"`
	Port        string `json:"port"`
	Status      string `json:"status"`
	TCP         bool   `json:"tcp"`
	UDP         bool   `json:"udp"`
}

func bloomString(s string) string {
	s = strings.Replace(s, "[", "", -1)
	s = strings.Replace(s, "]", "", -1)
	return s
}
func toInt(s string) int {
	i, _ := strconv.Atoi(s)
	return i
}
func mapPorts2Services(portas []int, service []string) Response {
	m := make(map[int]string)
	for i, v := range portas {
		m[v] = service[i]
	}

	data := Response{
		Ps: m,
	}
	return data
}

func scanAbuser(url string, startPort int, endPort int, threadsAtTime int) []int {

	waitGroup := sync.WaitGroup{}
	waitGroup.Add(endPort - startPort) // total amount neet
	ports := []int{}                   //return

	guard := make(chan struct{}, threadsAtTime) // vai so de 2 em 2, ou quantos a pessoa setar

	for port := startPort; port < endPort; port++ {

		guard <- struct{}{}

		go func(port int) {
			defer func() {
				waitGroup.Done()
				<-guard
			}()

			opened := scan(port, url+":"+strconv.Itoa(port), &waitGroup)
			ports = append(ports, opened)

		}(port)

	}

	// waitGroup.Done()
	waitGroup.Wait()
	return ports
}

func startScan(w http.ResponseWriter, r *http.Request) {
	if r.Method == "GET" {
		r.ParseForm()
		ip := fmt.Sprint(r.Form["url"])
		startPortTmp := fmt.Sprint(r.Form["startPort"])
		endPortTmp := fmt.Sprint(r.Form["endPort"])
		threadsAtTimeTmp := fmt.Sprint(r.Form["threadsAtTime"])
		// @TODO: verificar se os inputs sao validos

		ip = bloomString(ip)
		startPort := toInt(bloomString(startPortTmp))
		endPort := toInt(bloomString(endPortTmp))
		threadsAtTime := toInt(bloomString(threadsAtTimeTmp))

		t, _ := template.ParseFiles("templates/index.gtpl")

		// por a url
		tmp := scanAbuser(ip, startPort, endPort, threadsAtTime)
		// corringo portas abertas, meio ineficiente, daria pra melhorar
		var portas []int
		for _, v := range tmp {
			if v != -1 {
				portas = append(portas, v)
			}
		}
		service := searchDaService(portas)
		data := mapPorts2Services(portas, service)

		t.Execute(w, data)

	}

}

func scan(port int, address string, waitGroup *sync.WaitGroup) int {

	conn, err := net.Dial("tcp", address)
	if err != nil {
		// fmt.Printf("%d: %s\n", port, err.Error())
		return -1
	}
	conn.Close()
	fmt.Printf("%d: open\n", port)
	return port
}

func searchDaService(portsv []int) []string {

	jsonFile, err := os.Open("ports.json")
	if err != nil {
		fmt.Println(err)
	}
	defer jsonFile.Close()

	var pps PortsJson
	byteValue, _ := ioutil.ReadAll(jsonFile)
	// unmarshal
	json.Unmarshal(byteValue, &pps)

	var ret []string
	f := false
	// o codigo abaixo eh pessimamente otimizado, tem uma biblioteca que faz isso melhor
	// mas a titulo de aprendizado foi bacana pra entender as structs do json
	for _, v := range portsv {
		for i := 0; i < len(pps.Ports); i++ {
			if strconv.Itoa(v) == pps.Ports[i].Port {
				f = true
				ret = append(ret, pps.Ports[i].Description)
			}
		}
		if f != true {
			ret = append(ret, "Description not found")
		}
		f = false
	}

	return ret
}

func index(w http.ResponseWriter, r *http.Request) {
	// fmt.Println("method:", r.Method) //get request method
	if r.Method == "GET" {
		t, _ := template.ParseFiles("templates/index.gtpl")
		t.Execute(w, nil)
	}

}

func main() {
	addr := "127.0.0.1:8081"
	//routes
	http.HandleFunc("/", index)
	http.HandleFunc("/scan", index)
	http.HandleFunc("/startScan", startScan) //GET return scan

	log.Printf("Running web server on: http://%s\n", addr)

	err := http.ListenAndServe(":8081", nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}

}
