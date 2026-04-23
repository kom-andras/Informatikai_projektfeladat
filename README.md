<h1>Ipari IoT Gateway</h1>

#### Tartalomjegyzék
- [A projektről](#a-projektről)
- [Raspberry pi telepítése](#raspberry-pi-telepítése)
- [Node-ok beállítása](#node-ok-beállítása)
- [Node-RED](#node-red)
- [Grafana](#grafana)
- [Időbeosztás](#időbeosztás)
- [Források](#források)

## A projektről
Egy demonstrációs **ipari IoT gateway rendszer**, amely több szenzor node-ról gyűjt adatokat, majd azokat egy edge gateway-n keresztül feldolgozza, eltárolja és vizualizálja.

A projekt célja egy kis léptékű **Industry 4.0** architektúra megvalósítása otthoni környezetben.

A projekt egy olyan rendszer megvalósítása, amely:
- több **ESP32** alapú szenzor **node**-ról gyűjt adatokat
- **MQTT** protokollon keresztül kommunikál
- egy **Raspberry Pi gateway** dolgozza fel az adatokat
- az adatokat idősoros adatbázisban tárolja
- egy webes dashboardon jeleníti meg az adatokat
A rendszer demonstrálja az edge computing, IoT kommunikáció és adatvizualizáció alapelveit.

[⬆ Vissza a tetejére](#tartalomjegyzék)

## Raspberry pi telepítése

Felhasznált hardware: Raspberry Pi 4B 4Gb

A telepítéshez a Raspberry Pi Imagert használtam és egy Raspberry pi OS-t telepítettem, beállítottam a wifi jelszót is és a Pi Connectet is, ami igazából a Raspberry beépített távoli asztal alkalmazása, így bárhonnan hozzá lehet férni a pi-hoz. Ez nem feltétlenül szükséges, elég az SSH-t beállítani.

Először frissíteni kell mindent:
>sudo apt update</br>
>sudo apt upgrade

Majd telepítjük az IoT Stack-et és újraindítjuk a pi-t:
>curl -fsSL https://raw.githubusercontent.com/SensorsIot/IOTstack/master/install.sh | bash</br>
>sudo shutdown -r now

Telepítés után lépjünk bele a mappába és indítsuk el a menu scriptet:
>cd IOTstack/</br>
>./menu.sh

A menüben a következő komponenseket kell kiválasztanunk:
- Grafana
- InfluxDB
- Mosquitto
- Node-RED
- Portainer-CE

A következő lépésben létre kell hoznunk az adatbázist:
>docker exec -it influxdb influx</br>
>CREATE DATABASE sensor_data</br>
>quit

Ha mindent jól csináltunk, akkor ha beírjuk egy böngészőbe a pi ipcímét és utána a :9000-es portot, megjelenik a portainer ami a konténereinket kezeli.

Az 1880-as porton elérjük a Node-RED-et és a 3000-es porton a Grafana-t.

[⬆ Vissza a tetejére](#tartalomjegyzék)

## Node-ok beállítása

Én Node-oknak ESP32-es mikrovezérlőket hasznátam. Először a teszt kedvéért egy potmétert kötöttem hozzá, a 3-as pinre és feltöltöttem a kódot (mqtt_node_potmeter.ino).
Egy másik node-ra egy fény ellenállást és egy dupla relé modult kötöttem. (mqtt_node_LDR.ino)
Később azt is beállítottam, hogy az esp32 ledjeit is lehessen kapcsolgatni.
A két ESP32 két külön topicra kapja az utasításokat és küldi az adatokat.
Adatok amit küldenek: Fényellenállás(%), potméter(%), LED-ek állapota(0-1), Relék állapota(0-1)
Adatok amit kapnak: LED-ek bekapcsolása(0-1), Relék bekapcsolása(0-1)

[⬆ Vissza a tetejére](#tartalomjegyzék)

## Node-RED

Ahogy már említettem a 1880-as porton elérjük a Node-RED-et. Innen a böngészőből elérünk mindent.
Három darab flow-m van, az elsőben beérkeznek az adatok, feldolgozásra kerülnek és bekerülnek az adatbázisba.
Illetve itt detektálom, hogy ha 30 másodpercig nem küldenek adatot, egy üzenetet küld Telegramon keresztül.
A második flowban manuálisan tudjuk kapcsolgatni a fentebb említett kimeneteket, illetve van egy kis automatizáció, ha a fényellenállás értéke 20 vagy az alá esik, akkor bekapcsolja az 1-es relét, ha 20 fölé emelkedik akkor kikapcsolja azt. Ha a potméter értéke 95 felé emelkedik bekapcsol a 2-es relé ha 95 alá csökken kikapcsol.
A harmadik flow a Telegramos adat lekérdezésért felel, ha a Telegramos botnak
>/data
üzenetet küldünk, akkor feldob 4 lehetőséget aminek az értékét le tudjuk kérdezni:

- Fényellenállás értéke(%)
- Potméter értéke(%)
- Relé 1 állapota (on-off)
- Relé 2 állapota (on-off)

[⬆ Vissza a tetejére](#tartalomjegyzék)

## Grafana

[⬆ Vissza a tetejére](#tartalomjegyzék)

## Időbeosztás
1. március 9-15
    - GitHub README

2. március 16-22
    - Raspberry telepítése, beállítása

3. március 23-29
    - Node-ok összeállítása, felprogramozása

4. március 30 - április 5
    - Node-RED és Grafana beállítása

5. április 6-12
    - Szerver-kliens kapcsolat tesztelése

6. április 13-19
    - További Node-ok telepítése, Node-RED, Grafana beállítások módosítása

7. április 20-26
    - Tovább fejlesztés, módosítások eszközlése

8. április 27 - május 3
    - Esetleges csúszás behozása
    
9. május 7
    - Bemutatás

[⬆ Vissza a tetejére](#tartalomjegyzék)

## Források
<a href="https://learnembeddedsystems.co.uk/easy-raspberry-pi-iot-server">Raspberry Pi IoT Server</a></br>
<a href="https://www.youtube.com/playlist?list=PLKYvTRORAnx6a9tETvF95o35mykuysuOw">Node_RED tutorials</a></br>
<a href="https://learnembeddedsystems.co.uk/node-red-telegram-iot-bot-integration">Node-RED Telegram IoT Bot</a>

[⬆ Vissza a tetejére](#tartalomjegyzék)