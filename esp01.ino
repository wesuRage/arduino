#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *nome_da_rede = "ARD";

const char *senha = "12345678";

int pino_LED = 2;

ESP8266WebServer servidor (80);

String page = "";
String ligado = "";
String desligado = "";

void setup() {
  page = "<html>\n"
    "\n"
    "<style>\n"
    "body {\n"
    "background: #009541; \n"
    "}\n"
    ".button {\n"
    "background-color: #312682;\n"
    "border: none;\n"
    "color: white;\n"
    "padding: 15px 32px;\n"
    "text-align: center;\n"
    "display: inline-block;\n"
    "font-size: 48px;\n"
    "margin: 4px 2px;\n"
    "cursor: pointer;\n"
    "border-radius: 12px;\n"
    "width: 450px;\n"
    "}\n"
    "\n"
    ".disabled {\n"
    "opacity: 0.5;\n"
    "color: black;\n"
    "}\n"
    "</style>\n"
    "<section><center>\n"
    "<br><br>\n"
    "<font size=\"6\"> \n"
    "<h1>&#129302; "
    "ROB&Oacute;TICA PARAN&Aacute; "
    "&#129302; </h1>\n"
    "<h1>Aula 38 - IoT com Atuadores</h1>\n"
    "<p><h1>&#128246; "
    "Controle Wireless do LED&#128161;</h1>\n"
    "</font>\n";
  
  ligado = "<p><a href=\"/desligar\">"
    "<button class=\"button button\">"
    "LIGADO</button></a>\n"
    "</center></section>\n"
    "</html>";
  
  desligado = "<p><a href=\"/ligar\">"
    "<button class=\"button disabled\">"
    "DESLIGADO</button></a>\n"
    "</center></section>\n"
    "</html>";
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  digitalWrite(pino_LED, LOW);
  
  WiFi.softAP(nome_da_rede, senha);
  
  servidor.on("/", []() {
    servidor.send(200, "text/html", page + desligado);
  });
  
  servidor.on("/ligar", []() {
    servidor.send(200, "text/html", page + ligado);
    digitalWrite(pino_LED, HIGH);
  });
  
  servidor.on("/desligar", []() {
    servidor.send(200, "text/html", page + desligado);
    digitalWrite(pino_LED, LOW);
  });
  
  servidor.begin();
}

void loop() {
  servidor.handleClient();
}
