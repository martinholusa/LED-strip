# LED pásky s použitím WiFi
OBSAH
ÚVOD		6
1.	VÝROBA KONTROLÉRU NA LED PÁSKY	7
2.	VYUŽITÉ TECHNOLOGIE	8
2.1.	VYBAVENÍ	8
      2.1.1	PROCESOR..........	8
      2.1.1	LED PÁSKY..........	9
      2.1.1	TRANZISTOR..........	10
     2.2	SOFTWARE..........	10
3.	ZPŮSOBY ŘEŠENÍ A POUŽITÉ POSTUPY	11
      3.1	SEZNAM NUTNÝCH SOUČÁSTEK..........	11
      3.2	SCHÉMA ZAPOJENÍ..........	11
4.	VÝSLEDKY ŘEŠENÍ, VÝSTUPY, UŽIVATELSKÝ MANUÁL	12
     4.1	UKÁZKA KÓDU..........	12
     4.2	UKÁZKA HTML..........	13
     4.3	PŘEVOD 12V NA 3,3V..........	13
ZÁVĚR		14
SEZNAM POUŽITÝCH INFORMAČNÍCH ZDROJŮ	15


 
#ÚVOD
Většina pásků již mají svůj kontrolér, který má dálkový ovladač. Nicméně, aby byla připo-jena WiFi budeme dělat nový kontrolér. K ovládání těchto pásků potřebujeme mikrokont-rolér, některé tranzistory nebo MOSFET a WiFi. 
Mohli bychom použít Arduino desku, ale to se může prodražit, zvláště poté, co přidáte do nákladů na Ethernet nebo WiFi štít. Můžeme to udělat lépe a použít relativně nový mikro-procesor ESP8266. Tato deska je úžasná. Je velmi levná a má WiFi se snadno použitelnou knihovnou. Můžeme ho naprogramovat stejně jako Arduino s Arduino IDE. Také již má spoustu digitálních vstupních / výstupních pinů.

1.	VÝROBA KONTROLÉRU NA LED PÁSKY
Cílem tohoto projektu bylo vytvoření plošného spoje, naprogramování mikrokontroléru a následné vytvoření softwarové aplikace pro ovládání RGB LED pásku. 
Na začátku projektu bylo velice důležité vybrat si správné technologie, které budou použi-ty. První věc, kterou jsem musel udělat, bylo představit si, jak celé zařízení bude pracovat, jak to bude vypadat ve skutečnosti. Po utvoření představy bylo nutné vybrat si správný mikroprocesor, který celé zařízení bude řídit. Po uvážení jsem si zvolil procesor ESP8266 NodeMCU V3.
Dalším krokem bylo nakreslení plošného spoje se všemi potřebnými součástkami. Při kres-lení spoje jsem několikrát měnil finální podobu.
Po nakreslení schématu zapojení celého zařízení bylo načase nakoupení všech potřebných součástek. Nejdříve jsem zapojení zkoušel na nepájivém kontaktním poli, kde jsem zkoušel správnou funkčnost zařízení. 
Poté našel správný čas na psaní programu, který jsem se rozhodl psát v Arduino IDE. Pár projektů jsem zkoušel přes tento program, takže to byla nejsnazší volba. 
Když vše fungovalo správně na kontaktním poli, rozhodl jsem se pro vytvoření plošného spoje. Po zasazení součástek do těchto otvorů už jen stačí propojit správně součástky podle schématu zapojení cínem, případně jiným vodičem určeným pro pájení. 
Po dokončení všech částí už jen zbývalo ho vyzkoušet v praxi. Zařízení jsem dal do kra-bičky, vyvrtal otvor pro napájecí kabel. Po zapnutí zařízení se stačí připojit na WiFi, kterou vytvoří mikrokontrolér a poté v prohlížeči napsat IP adresu. Načte stránka, kde pomocí tlačítek a posuvníků můžeme ovládat pásky.
2.	VYUŽITÉ TECHNOLOGIE
2.1.	VYBAVENÍ
	2.1.1	PROCESOR
ESP8266 NodeMCU V3 je jedním z nejlevnějších připojení WiFi moduly na trhu. V3 nebo Version3 je nejnovější verze tohoto modulu. Založeno na čipu ESP12-E.
Piny: 15-pinů s přístupem k GPIO, SPI, UART, ADC, a napájecích kolíků.
Parametry:
•	4MB FLASH paměť
•	Komunikační napětí 3,3V
•	Wireless 802.11 b/g/n
















	2.1.2	LED PÁSKY
LED pásky, které jsem použil jsou SMD 5050 LED diody. Jsou vyrobeny z pružného mate-riálu desky obvodů s přiléhajícími RGB LED diodami. Můžou se řezat podél předem urče-ných úsecích, takže si je naměříme podle sebe. Na pásu jsou čtyři dráty: 12V, R, G a B. Můžeme ovládat LED pásky tím, že dodáme pozitivních 12V na pin 12V a pak uzemníme kteroukoli jiný pin na dokončení obvodu, což způsobuje, že se rozsvítí odpovídající barva. Například, pokud jsme uzemnili R kolík pak se rozsvítí plnou červenou. Většina pásků již mají svůj kontrolér, který má dálkový ovladač. Nicméně, aby byla připojena WiFi budeme dělat nový kontrolér.

	2.1.3	TRANZISTOR
Tranzistor je polovodičová součástka, kterou tvoří dvojice přechodů PN. Tranzistory jsou základní aktivní součástky, které se používají jako zesilovače, spínače a invertory. Jsou základem všech dnešních integrovaných obvodů, jako např. procesorů, pamětí atd.
TIP31 tranzistory jsou označeny jako TIP31A, TIP31B,  TIP31C, TIP31.
Pro svoji práci jsem použil tranzistory TIP31C.
Parametry:
•	Napětí: 115V
•	Proud: 3A
•	Výkon: 40W




2.2	Software
Arduino Software (IDE- Integrated Development Environment) obsahuje textový editor pro psaní kódu, textovou konzoli, nástrojovou lištu s tlačítky pro společných funkcí a řadou nabídek. To se připojí k hardwaru, nahraje programy a komunikuje s nimi. Programy jsou zapsány v textovém editoru a jsou uloženy s příponou souboru .ino. Poskytuje zpětnou vazbu při ukládání a exportu a také zobrazuje chyby.
 
Obr. 6 Logo arduino IDE
3.	ZPŮSOBY ŘEŠENÍ A POUŽITÉ POSTUPY
3.1.  SEZNAM NUTNÝCH SOUČÁSTEK
•	ESP8266 nodeMCU V3
•	LED pásek SMD 5050
•	Konvertor 12V na 3,3V
•	Adaptér na 12V
•	3x Tranzistor TIP31C
•	3x rezistor 10K Ω 
•	Nepájivé kontaktní pole (později pájivé pole) 

3.2  SCHÉMA ZAPOJENÍ
 
Obr. 7 Schéma zapojení
4.	VÝSLEDKY ŘEŠENÍ, VÝSTUPY, UŽIVATELSKÝ MANUÁL 
4.1	UKÁZKA KÓDU
 
Obr. 8 Ukázka kódu v Arduino IDE
V této části kódu se nastaví sériová linka, která poté vypíše odpočet a nastartuje se WiFi Access point, ke kterému se poté můžeme připojit telefonem nebo noteboo-kem. Sériová linka poté vypíše IP adresu, na kterou se připojíme přes prohlížeč a můžeme ovládat LED pásky.






4.2	 Ukázka HTML 
 
Obr. 9 Ukázka HTML kódu
V této části kódu jsou vytvořeny tlačítka a posuvníky pro každou složku zvlášť: červená, zelená, modrá. Jsou nastaveny na hodnotu od 0 do 255 a poté posílá zada-nou barvu do mikrokontroléru.

4.3	 Převod 12V na 3,3V
Jelikož jsem nechtěl aby zařízení mělo 2 napájení, tak jsem musel vyřešit aby přes jeden adaptér, který je na 12V, šlo taky převést napětí na 3,3V. K tomu jsem použil modul, kterému dáme vstupní napětí 12V a výstupní bude podle nastavení od 0V do 5V. Výstupní napětí je jen 3,3V, tak jsem musel napájet dva vodiče na vstupní napětí 12V a pak je přivést k LED páskům.

Závěr
Cílem tohoto projektu bylo vytvoření funkčního kontroléru. Určené cíle byly splněny jako sestavení plošného spoje, vytvoření programu pro ovládání pásku a webové aplikace.
 Do budoucna by bylo možné vytvořit webovou aplikaci, kde by byla paleta barev a bylo by možné si vybrat jakoukoliv barvu bez posuvníků.  
Tento kontrolér jsem navrhl pro vlastní potřebu. Samozřejmě lze podobný kontrolér koupit již hotový, ale proč za to utrácet peníze, když si takový můžu vyrobit doma. Mám jej na-montovaný za stolem. Pásky dost svítí, takže nemusím ani svítit v pokoji.
