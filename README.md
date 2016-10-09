# LED-strip
LED pásky jsou celkem levné a když je vhodně použijete, vypadají skvěle. Pásky se můžou nalepit kamkoliv a s pomocí ovlačace měnit barvy. Ovšem s pomocí WiFi ovládání přes mobilní telefon je to zábavnější.
Konečným výsledkem bude plně řiditelný WiFi LED pásek, který můžete nastavit na jakoukoliv barvu.

# Vybavení
LED pásky, které jsem použil jsou SMD 5050 LED diody. Jsou vyrobeny z pružného materiálu desky obvodů s přiléhajícími RGB LED diodami. Můžou se řezat podél předem určených úsecích, takže si je naměříme podle sebe. Na pásu jsou čtyři dráty: 12V, R, G a B. Můžete ovládat LED pásky tím, že dodáte pozitivních 12V na pin 12V a pak uzemníte kteroukoli jiný pin na dokončení obvodu, což způsobuje, že se rozsvítí odpovídající barva. Například, pokud jste uzemnili R kolík pak se rozsvítí plnou červenou.

Většina pásků již mají svůj kontroler, který má dálkový ovladač. Nicméně, aby byla připojena WiFi budeme dělat nový kontroler. K ovládání těchto pásků potřebujeme mikrokontroler, některé tranzistory nebo MOSFET a WiFi. Mohli bychom použít Arduino desku, ale to se může prodražit, zvláště poté, co přidáte do nákladů na Ethernet nebo WiFi štít. Můžeme to udělat lépe a použít relativně nový mikroprocesor: na ESP8266.
Tato deska je užasná. Je velmi levné a má Wi-Fi se snadno použitelnou knihovnou. Můžeme ho naprogramovat stejně jako Arduino, s Arduino IDE. Také již má spoustu digitálních vstupních / výstupních pinů.

# Obvod
K vyrobení obvodu pro ovládání LED diod potřebujete napájení. LED diody potřebují + 12V i když jim může pohánět s pouhými 9V a budou stále fungovat. ESP8266 potřebuje regulované +3,3.



# URL
http://jakebergamin.com/2016/02/08/wifi-led-strip/

http://trevorshp.com/creations/android_led.htm

http://makezine.com/projects/android-arduino-led-strip-lights/
