# Ovládání LED pásků použitím WiFi
![20161224_084756](https://cloud.githubusercontent.com/assets/14974425/21686999/c2d20ca4-d367-11e6-8ff9-544ee313400b.jpg)
 
## ÚVOD
Většina pásků již mají svůj kontrolér, který má dálkový ovladač. Nicméně, aby byla připo-jena WiFi budeme dělat nový kontrolér. K ovládání těchto pásků potřebujeme mikrokont-rolér, některé tranzistory nebo MOSFET a WiFi. 
Mohli bychom použít Arduino desku, ale to se může prodražit, zvláště poté, co přidáte do nákladů na Ethernet nebo WiFi štít. Můžeme to udělat lépe a použít relativně nový mikro-procesor ESP8266. Tato deska je úžasná. Je velmi levná a má WiFi se snadno použitelnou knihovnou. Můžeme ho naprogramovat stejně jako Arduino s Arduino IDE. Také již má spoustu digitálních vstupních / výstupních pinů.

## 1.	VÝROBA KONTROLÉRU NA LED PÁSKY
Cílem tohoto projektu bylo vytvoření plošného spoje, naprogramování mikrokontroléru a následné vytvoření softwarové aplikace pro ovládání RGB LED pásku. 
Na začátku projektu bylo velice důležité vybrat si správné technologie, které budou použi-ty. První věc, kterou jsem musel udělat, bylo představit si, jak celé zařízení bude pracovat, jak to bude vypadat ve skutečnosti. Po utvoření představy bylo nutné vybrat si správný mikroprocesor, který celé zařízení bude řídit. Po uvážení jsem si zvolil procesor ESP8266 NodeMCU V3.
Dalším krokem bylo nakreslení plošného spoje se všemi potřebnými součástkami. Při kres-lení spoje jsem několikrát měnil finální podobu.
Po nakreslení schématu zapojení celého zařízení bylo načase nakoupení všech potřebných součástek. Nejdříve jsem zapojení zkoušel na nepájivém kontaktním poli, kde jsem zkoušel správnou funkčnost zařízení. 
Poté našel správný čas na psaní programu, který jsem se rozhodl psát v Arduino IDE. Pár projektů jsem zkoušel přes tento program, takže to byla nejsnazší volba. 
Když vše fungovalo správně na kontaktním poli, rozhodl jsem se pro vytvoření plošného spoje. Po zasazení součástek do těchto otvorů už jen stačí propojit správně součástky podle schématu zapojení cínem, případně jiným vodičem určeným pro pájení. 
Po dokončení všech částí už jen zbývalo ho vyzkoušet v praxi. Zařízení jsem dal do kra-bičky, vyvrtal otvor pro napájecí kabel. Po zapnutí zařízení se stačí připojit na WiFi, kterou vytvoří mikrokontrolér a poté v prohlížeči napsat IP adresu. Načte stránka, kde pomocí tlačítek a posuvníků můžeme ovládat pásky.

## 2.	VYUŽITÉ TECHNOLOGIE

### 2.1.	VYBAVENÍ
#### 	2.1.1	PROCESOR
ESP8266 NodeMCU V3 je jedním z nejlevnějších připojení WiFi moduly na trhu. V3 nebo Version3 je nejnovější verze tohoto modulu. Založeno na čipu ESP12-E.
Piny: 15-pinů s přístupem k GPIO, SPI, UART, ADC, a napájecích kolíků.
Parametry:

-4MB FLASH paměť

-Komunikační napětí 3,3V

-Wireless 802.11 b/g/n

![screenshot_1](https://cloud.githubusercontent.com/assets/14974425/21687625/56f00b5a-d36a-11e6-895a-fc49016041eb.png)

#### 	2.1.2	LED PÁSKY
LED pásky, které jsem použil jsou SMD 5050 LED diody. Jsou vyrobeny z pružného mate-riálu desky obvodů s přiléhajícími RGB LED diodami. Můžou se řezat podél předem urče-ných úsecích, takže si je naměříme podle sebe. Na pásu jsou čtyři dráty: 12V, R, G a B. Můžeme ovládat LED pásky tím, že dodáme pozitivních 12V na pin 12V a pak uzemníme kteroukoli jiný pin na dokončení obvodu, což způsobuje, že se rozsvítí odpovídající barva. Například, pokud jsme uzemnili R kolík pak se rozsvítí plnou červenou. Většina pásků již mají svůj kontrolér, který má dálkový ovladač. Nicméně, aby byla připojena WiFi budeme dělat nový kontrolér.

![smd5050](https://cloud.githubusercontent.com/assets/14974425/21687630/5f601d7a-d36a-11e6-80fa-2e9e957e0315.jpg)

![screenshot_2](https://cloud.githubusercontent.com/assets/14974425/21687634/626cc162-d36a-11e6-80bc-87163da70fb1.png)


#### 	2.1.3	TRANZISTOR
Tranzistor je polovodičová součástka, kterou tvoří dvojice přechodů PN. Tranzistory jsou základní aktivní součástky, které se používají jako zesilovače, spínače a invertory. Jsou základem všech dnešních integrovaných obvodů, jako např. procesorů, pamětí atd.
TIP31 tranzistory jsou označeny jako TIP31A, TIP31B,  TIP31C, TIP31.
Pro svoji práci jsem použil tranzistory TIP31C.
Parametry:

-Napětí: 115V

-Proud: 3A

-Výkon: 40W

![screenshot_3](https://cloud.githubusercontent.com/assets/14974425/21687647/695e31ea-d36a-11e6-90d8-c637ecebea40.png)

### 2.2	Software
Arduino Software (IDE- Integrated Development Environment) obsahuje textový editor pro psaní kódu, textovou konzoli, nástrojovou lištu s tlačítky pro společných funkcí a řadou nabídek. To se připojí k hardwaru, nahraje programy a komunikuje s nimi. Programy jsou zapsány v textovém editoru a jsou uloženy s příponou souboru .ino. Poskytuje zpětnou vazbu při ukládání a exportu a také zobrazuje chyby.
 
 ![screenshot_4](https://cloud.githubusercontent.com/assets/14974425/21687649/6ba78c58-d36a-11e6-9432-4b98753912d7.png)
 
## 3.	ZPŮSOBY ŘEŠENÍ A POUŽITÉ POSTUPY

### 3.1.  SEZNAM NUTNÝCH SOUČÁSTEK

-ESP8266 nodeMCU V3

-LED pásek SMD 5050

-Konvertor 12V na 3,3V

-Adaptér na 12V

-3x Tranzistor TIP31C

-3x rezistor 10K Ω 

-Nepájivé kontaktní pole (později pájivé pole) 


### 3.2  SCHÉMA ZAPOJENÍ

![screenshot_5](https://cloud.githubusercontent.com/assets/14974425/21687653/6d483e04-d36a-11e6-9d74-9eff828b9ff8.png) 
 
## Závěr
Cílem tohoto projektu bylo vytvoření funkčního kontroléru. Určené cíle byly splněny jako sestavení plošného spoje, vytvoření programu pro ovládání pásku a webové aplikace.
Do budoucna by bylo možné vytvořit webovou aplikaci, kde by byla paleta barev a bylo by možné si vybrat jakoukoliv barvu bez posuvníků. 
Tento kontrolér jsem navrhl pro vlastní potřebu. Samozřejmě lze podobný kontrolér koupit již hotový, ale proč za to utrácet peníze, když si takový můžu vyrobit doma. Mám jej na-montovaný za stolem. Pásky dost svítí, takže nemusím ani svítit v pokoji.
