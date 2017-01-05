# LED pásky s použitím WiFi
LED pásky jsou celkem levné a když je vhodně použijete, vypadají skvěle. Pásky se můžou nalepit kamkoliv a s pomocí ovlačace měnit barvy. Ovšem s pomocí WiFi ovládání přes mobilní telefon je to zábavnější.
Konečným výsledkem bude plně řiditelný WiFi LED pásek, který můžete nastavit na jakoukoliv barvu.

## Vybavení
LED pásky, které jsem použil jsou SMD 5050 LED diody. Jsou vyrobeny z pružného materiálu desky obvodů s přiléhajícími RGB LED diodami. Můžou se řezat podél předem určených úsecích, takže si je naměříme podle sebe. Na pásu jsou čtyři dráty: 12V, R, G a B. Můžeme ovládat LED pásky tím, že dodáme pozitivních 12V na pin 12V a pak uzemníme kteroukoli jiný pin na dokončení obvodu, což způsobuje, že se rozsvítí odpovídající barva. Například, pokud jsme uzemnili R kolík pak se rozsvítí plnou červenou.

![smd5050](https://cloud.githubusercontent.com/assets/14974425/19220342/a4e33834-8e2b-11e6-9568-3aceeac31055.jpg)

Většina pásků již mají svůj kontroler, který má dálkový ovladač. Nicméně, aby byla připojena WiFi budeme dělat nový kontroler. K ovládání těchto pásků potřebujeme mikrokontroler, některé tranzistory nebo MOSFET a WiFi. Mohli bychom použít Arduino desku, ale to se může prodražit, zvláště poté, co přidáte do nákladů na Ethernet nebo WiFi štít. Můžeme to udělat lépe a použít relativně nový mikroprocesor: na ESP8266.
Tato deska je užasná. Je velmi levné a má Wi-Fi se snadno použitelnou knihovnou. Můžeme ho naprogramovat stejně jako Arduino, s Arduino IDE. Také již má spoustu digitálních vstupních / výstupních pinů.

![led_strips_astripsch](https://cloud.githubusercontent.com/assets/14974425/19220349/c51df65c-8e2b-11e6-88c6-9e1631d532d3.png)

## Obvod
K vyrobení obvodu pro ovládání LED diod potřebujete napájení. LED diody potřebují + 12V i když jim může pohánět s pouhými 9V a budou stále fungovat. ESP8266 potřebuje regulované +3,3.

Když jsme poslali některé ze tří kolíků na ESP8266 až vysoké, přepne tranzistor, dokončí okruh a rozsvítí odpovídající barvu. LED lze nastavit pouze na plný nebo úplné vypnutí, takže můžeme použít něco jako pulsní šířková modulace (PWM). PWM je v podstatě, že se zapne a vypne něco okolo stovky krát za sekundu. Takže v případě, že většinu času je to tak, pak LED objeví jasnější a naopak. Můžeme použít funkci analogWrite Arduino k ovládání intenzity nebo jasu.

![ledstrips_schem](https://cloud.githubusercontent.com/assets/14974425/19220357/da5c5022-8e2b-11e6-8b64-d8e2dbe11d8b.png)

## URL
http://jakebergamin.com/2016/02/08/wifi-led-strip/

http://trevorshp.com/creations/android_led.htm

http://makezine.com/projects/android-arduino-led-strip-lights/


https://www.aliexpress.com/item/V3-Wireless-module-NodeMcu-4M-bytes-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266-for/32554198757.html?spm=2114.30010308.3.39.B7rbv2&ws_ab_test=searchweb0_0,searchweb201602_3_10056_10065_10068_10055_10054_10069_10059_10078_10079_10073_10017_10080_10070_10082_10081_10060_10061_10052_10062_10053_10050_10051,searchweb201603_3&btsid=2804e641-0f28-4f96-a73d-972d90f17ed7


https://www.aliexpress.com/item/ESP8266-serial-wifi-wireless-control-ESP-202-test-panel-module-development-test-send-APP/32641032099.html?spm=2114.30010308.3.69.7nUQI4&ws_ab_test=searchweb0_0,searchweb201602_3_10056_10065_10068_10055_10054_10069_10059_10078_10079_10073_10017_10080_10070_10082_10081_10060_10061_10052_10062_10053_10050_10051,searchweb201603_3&btsid=5349eb0c-99f6-4d62-9299-38ae984e4e09

## Kód
{
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

void turnoff() {

    anRed = 0;
    anBlue = 0;
    anGreen = 0;
}

void blik(){
  digitalWrite(LED_RED, anRed);
  digitalWrite(LED_GREEN, anBlue);
  digitalWrite(LED_BLUE, anGreen);
  delay(1000);
  
  digitalWrite(LED_RED, 0);
  digitalWrite(LED_GREEN, 0);
  digitalWrite(LED_BLUE, 0); 
  delay(1000); 
  
}



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

            if (payload[0] == '#') {
                // we get RGB data

                // decode rgb data
                uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);

                anRed = map(((rgb >> 16) & 0xFF), 0, 255, 0, 1023);
                anGreen = map(((rgb >> 8) & 0xFF), 0, 255, 0, 1023);
                anBlue = map(((rgb >> 0) & 0xFF), 0, 255, 0, 1023);
            }

            break;
    }

}

void setup() {
    //USE_SERIAL.begin(921600);
    USE_SERIAL.begin(115200);

    //USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for (uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

  
    pinMode(BUTTON, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON), turnoff, HIGH); //přerušení, definování pinu přerušení

    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);

    digitalWrite(LED_RED, 1);
    digitalWrite(LED_GREEN, 1);
    digitalWrite(LED_BLUE, 1);


    WiFi.softAP("manin-led", "12345678");
    IPAddress myIP = WiFi.softAPIP();
    USE_SERIAL.print("AP IP address: ");
    USE_SERIAL.println(myIP);

    // start webSocket server
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);

    if (MDNS.begin("esp8266")) {
        USE_SERIAL.println("MDNS responder started");
    }



    server.on("/", []() {
        // send index.html
        // replace for better looking
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
"                var rgb = '#'+r+g+b;    "
"                console.log('RGB: ' + rgb); "
"                connection.send(rgb); }"

"                function off(){"
"                r = '0'; g = '0'; b = '0'; "
"                var rgb = '#'+r+g+b;    "
"                console.log('RGB: ' + rgb);"
"                connection.send(rgb);}"

"                function on(){"
"                r = 'ff';g = 'ff';b = 'ff'; "
"                var rgb = '#'+r+g+b;    "
"                console.log('RGB: ' + rgb);"
"                connection.send(rgb); }"

"                function zmena(){"
"                r = Math.floor((Math.random() * 255) + 0);  "
"                g = Math.floor((Math.random() * 255) + 0);  "
"                b = Math.floor((Math.random() * 255) + 0); "
"                var rgb = '#'+r+g+b;    "
"                console.log('RGB: ' + rgb); "
"                connection.send(rgb); }"

"                function cer(){"
"                  r = 'ff';g = '00';b = '00'; "
"                  var rgb = '#'+r+g+b;    "
"                  console.log('RGB: ' + rgb);"
"                  connection.send(rgb); }"
"                function zel(){"
"                  r = '00';g = 'ff';b = '00'; "
"                  var rgb = '#'+r+g+b;    "
"                  console.log('RGB: ' + rgb);"
"                  connection.send(rgb); }"
"                function mod(){"
"                  r = '00';g = '00';b = 'ff'; "
"                  var rgb = '#'+r+g+b;    "
"                  console.log('RGB: ' + rgb);"
"                  connection.send(rgb); }"
"                function tyr(){"
"                  r = '00';g = 'ff';b = 'ff'; "
"                  var rgb = '#'+r+g+b;    "
"                  console.log('RGB: ' + rgb);"
"                  connection.send(rgb); }"
"                function ruz(){"
"                  r = 'ff';g = '39';b = '99'; "
"                  var rgb = '#'+r+g+b;    "
"                  console.log('RGB: ' + rgb);"
"                  connection.send(rgb); }"
"                function zlu(){"
"                  r = 'ff';g = 'ff';b = '00'; "
"                  var rgb = '#'+r+g+b;    "
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

    // Add service to MDNS
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


}
