Formula student mock kod za testiranje telemetrije - radjeno na osnovu realnih f1 podataka

1. korak:
U folderu data pokrenuti python skriptu za prikupljanje podataka koje zelite prikazati na ekranu.
Za dodatne informacije posjetite sajt: https://docs.fastf1.dev/examples/index.html

Nakon toga biste u data folderu trebali ImeVozaca_GodinaMod_Drzava json fajl - primjer: HAM_2020R_Italy
gdje je ImeVozaca prva 3 slova prezimena, Godina je godina trke, Mod je practice, quali, race (P,Q,R - provjeriti za free practice na stranici navedenoj iznad)

2. korak:
Instalirati mosquitto sa linka https://mosquitto.org/download/
Ja sam instalirao mosquitto-2.0.21a-install-windows-x64.exe
Obavezno putanju dodati u PATH inace nece raditi (izbacivat ce 3 missing dll errora)

3. korak:
U samom kodu nastimati konekciju na broker, topic...

4. korak:
u samom folderu gdje se nalazi main.cpp otvoriti cmd prompt i kompajlirati naredbom: (kopira se citav red ispod)
g++ -I./include -L"C:/Program Files/mosquitto/" main.cpp -o main -lmosquitto 

zatim pokrenuti sa:
./main.exe ili ./main

Ako nesto od ovoga ne bude radilo, popravljajte!
- Benjamin Uzunovic 17.3.2025.