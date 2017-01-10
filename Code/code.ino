#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Hash.h>
#include <FS.h>

#define LED_GREEN   12
#define LED_BLUE    15
#define LED_RED     13
#define USE_SERIAL Serial

#define BUTTON 5
int buttonState = 0;
int anRed = 0;
int anGreen = 0;
int anBlue = 0;

ESP8266WiFiMulti WiFiMulti;
ESP8266WebServer server = ESP8266WebServer(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {
    switch (type) {
        case WStype_DISCONNECTED:
            USE_SERIAL.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED:
        {
            IPAddress ip = webSocket.remoteIP(num);
            USE_SERIAL.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

            // send message to client
            webSocket.sendTXT(num, "Connected");
        }
            break;
        case WStype_TEXT:
            USE_SERIAL.printf("[%u] get Text: %s\n", num, payload);
            if (payload[0] == '#'){
                uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);
                anRed = map(((rgb >> 16) & 0xFF), 0, 255, 0, 1023);
                anGreen = map(((rgb >> 8) & 0xFF), 0, 255, 0, 1023);
                anBlue = map(((rgb >> 0) & 0xFF), 0, 255, 0, 1023);
            }
            break;
    }
}

//Funkce pro vypnutí tlačítka
void turnoff(){
    anRed = 0;
    anBlue = 0;
    anGreen = 0;
}

void setup() {
    USE_SERIAL.begin(115200);
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    pinMode(BUTTON, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON), turnoff, HIGH); //přerušení, definování pinu přerušení

    //Nastavení pinu jako výstupní
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);

    //Konfigurace WiFi
    WiFi.softAP("manin-led", "12345678");
    IPAddress myIP = WiFi.softAPIP();
    USE_SERIAL.print("AP IP address: ");
    USE_SERIAL.println(myIP);
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    if (MDNS.begin("esp8266")) {
        USE_SERIAL.println("MDNS responder started");
    }

    server.on("/", []() {
        // posílá index.html
        //vytvoření webové aplikace
        server.send(200, "text/html",
"                <html><head><script>"
"                var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);"
"                connection.onopen = function () {  connection.send('Connect ' + new Date()); };"
"                connection.onerror = function (error) {    console.log('WebSocket Error ', error);};"
"                connection.onmessage = function (e) {  console.log('Server: ', e.data);};"

"                function sendRGB() {  "
"                var r = parseInt(document.getElementById('r').value).toString(16);  "
"                var g = parseInt(document.getElementById('g').value).toString(16);  "
"                var b = parseInt(document.getElementById('b').value).toString(16);  "
"                if(r.length < 2) { r = '0' + r; }   "
"                if(g.length < 2) { g = '0' + g; }  "
"                if(b.length < 2) { b = '0' + b; }   "
"                var rgb = '#'+b+g+r;    "
"                console.log('RGB: ' + rgb); "
"                connection.send(rgb); }"

"                function off(){"
"                r = '0'; g = '0'; b = '0'; "
"                var rgb = '#'+b+g+r;    "
"                console.log('RGB: ' + rgb);"
"                connection.send(rgb);}"

"                function on(){"
"                r = 'ff';g = 'ff';b = 'ff'; "
"                var rgb = '#'+b+g+r; "
"                console.log('RGB: ' + rgb);"
"                connection.send(rgb); }"

"                function zmena(){"
"                r = Math.floor((Math.random() * 255) + 0);  "
"                g = Math.floor((Math.random() * 255) + 0);  "
"                b = Math.floor((Math.random() * 255) + 0); "
"                var rgb = '#'+b+g+r; "
"                console.log('RGB: ' + rgb); "
"                connection.send(rgb); }"

"                function cer(){"
"                  r = 'ff';g = '00';b = '00'; "
"                  var rgb = '#'+b+g+r; "
"                  console.log('RGB: ' + rgb);"
"                  connection.send(rgb); }"
"                function zel(){"
"                  r = '00';g = 'ff';b = '00'; "
"                  var rgb = '#'+b+g+r; "
"                  console.log('RGB: ' + rgb);"
"                  connection.send(rgb); }"
"                function mod(){"
"                  r = '00';g = '00';b = 'ff'; "
"                  var rgb = '#'+b+g+r; "
"                  console.log('RGB: ' + rgb);"
"                  connection.send(rgb); }"
"                function tyr(){"
"                  r = '00';g = 'ff';b = 'ff'; "
"                  var rgb = '#'+b+g+r; "
"                  console.log('RGB: ' + rgb);"
"                  connection.send(rgb); }"
"                function ruz(){"
"                  r = 'ff';g = '39';b = '99'; "
"                  var rgb = '#'+b+g+r; "
"                  console.log('RGB: ' + rgb);"
"                  connection.send(rgb); }"
"                function zlu(){"
"                  r = 'ff';g = 'ff';b = '00'; "
"                  var rgb = '#'+b+g+r; "
"                  console.log('RGB: ' + rgb);"
"                  connection.send(rgb); }"

"                </script><style>"
"                input[type=range] {"
"                  -webkit-appearance: none;border: 1px solid white;width: 100%;border-radius: 8px;height: 18px;border: 1px solid #bdc3c7;}"
"                input[type=range]::-webkit-slider-runnable-track {"
"                   width: 300px;height: 6px;border: none;border-radius: 3px;}"
"                input[type=range]::-webkit-slider-thumb {"
"                   -webkit-appearance: none;border: none;height: 16px;width: 16px;border-radius: 50%;margin-top: -4px;}"
"                #r::-webkit-slider-thumb {background: #823232;}"
"                #g::-webkit-slider-thumb {background: #386d2a;}"
"                #b::-webkit-slider-thumb {background: #1e395e;}"
"                #j::-webkit-slider-thumb {background: #FFFFFF;}"
"                input[type=range]:focus {outline: none;}"
"                input[type=range]:focus::-webkit-slider-runnable-track {background: #ccc;}"
"                #r{background: #e595a2;}#g{background: #c4edc5;}#b{background: #9eb1d8;}"
"                .myButton {"
"                  -moz-box-shadow: 0px 0px 0px 2px #ffffff;"
"                    -webkit-box-shadow: 0px 0px 0px 2px #ffffff;"
"                   box-shadow: 0px 0px 0px 2px #ffffff;"
"                   filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#f9f9f9', endColorstr='#e9e9e9',GradientType=0);"
"                   -moz-border-radius:10px;"
"                   -webkit-border-radius:10px;"
"                   border-radius:10px;"
"                   border:1px solid #dcdcdc;"
"                   display:inline-block;"
"                   cursor:pointer;"
"                   font-family:Georgia;"
"                   font-size:19px;"
"                   padding:12px 36px;"
"                   text-decoration:none;"
"                   text-shadow:0px 1px 0px #ffffff;"
"                   text-transform: capitalize;}"
"                .myButton:active {position:relative;top:1px;}"
"                .myButton:active {position:relative;top:1px;}"
"                    </style>"
"                <meta charset=\"UTF-8\"></head><body>"
"                <h1 style=\"text-align: center;\">Ovládání RGB LED pásků</h1><br/>"
"                <button onclick=\"zmena()\" class=\"myButton\" style=\"background-color:#f9f9f9;\">náhodná barva</button>"
"                <button onclick=\"on()\" class=\"myButton\" style=\"background-color:#f9f9f9;\">bílá</button>"
"                <button onclick=\"off()\" class=\"myButton\" style=\"background-color:#bfbfbf; color:#000000;\">černá</button>"
                
"                <button onclick=\"cer()\" class=\"myButton\" style=\"background-color:#ff8080; color:#800000\">červená</button>"
"                <button onclick=\"zel()\" class=\"myButton\" style=\"background-color:#99ff99; color:#1a6600\">zelená</button>"
"                <button onclick=\"mod()\" class=\"myButton\" style=\"background-color:#80bfff; color:#0000cc\">modrá</button>"
"                <button onclick=\"tyr()\" class=\"myButton\" style=\"background-color:#99ffff; color:#008080\">tyrkysová</button>"
"                <button onclick=\"ruz()\" class=\"myButton\" style=\"background-color:#ffb3ec; color:#800040\">růžová</button>"
"                <button onclick=\"zlu()\" class=\"myButton\" style=\"background-color:#ffffb3; color:#4d4d00\">žlutá</button>"
                
"                <input id=\"r\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" onchange=\"sendRGB();\" /><br/>"
"                <input id=\"g\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" onchange=\"sendRGB();\" /><br/>"
"                <input id=\"b\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" onchange=\"sendRGB();\" /><br/>"
"                    </body></html>");
    });
    
    server.begin();
    MDNS.addService("http", "tcp", 80);
    MDNS.addService("ws", "tcp", 81);

    digitalWrite(LED_RED, 0);
    digitalWrite(LED_GREEN, 0);
    digitalWrite(LED_BLUE, 0);
}

void loop() {
    webSocket.loop();
    server.handleClient();
    analogWrite(LED_RED, anRed);
    analogWrite(LED_GREEN, anGreen);
    analogWrite(LED_BLUE, anBlue);
}
