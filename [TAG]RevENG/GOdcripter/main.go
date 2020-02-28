package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strconv"
	"strings"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func getKey2Decrypt() int {
	//a key que ele gera na funcao system_integrity_check() e salva no /tmp/key
	tmp, err := ioutil.ReadFile("/tmp/key")
	check(err)
	key := string(tmp)

	key = strings.TrimSuffix(key, "\n") //remove enter, was breaking Atoi
	k, err := strconv.Atoi(key)
	check(err)

	return k
}

func decrypt(fileName string, key int) {
	//LEIO
	f, err := ioutil.ReadFile(fileName)
	check(err)

	//ABRO PRA ESCREVER OS NOVOS BITS
	file2RW, err := os.OpenFile(fileName, os.O_RDWR, 0644)
	check(err)
	defer file2RW.Close()

	for i, v := range f { //i: indice, v: valor
		// removo do byte que ta la o que foi somado que vimos no descompilado do 2c6V
		_, err := file2RW.WriteAt([]byte{uint8(v) - uint8(key)}, int64(i))
		check(err)
	}

}

func main() {
	key := getKey2Decrypt()
	path := "./" + os.Getenv("USER") + "/"

	files, err := ioutil.ReadDir(path)
	check(err)
	// 'desencripto'
	for _, f := range files {
		decrypt(path+f.Name(), key)
	}
	//renomeio
	for _, f := range files {
		oldFileName := f.Name()
		newFileName := strings.TrimRight(oldFileName, ".leo")

		err := os.Rename(path+oldFileName, path+newFileName)
		check(err)
	}
	fmt.Println("DONEE==================")
}
