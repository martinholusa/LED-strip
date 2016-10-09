# LED-strip
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
