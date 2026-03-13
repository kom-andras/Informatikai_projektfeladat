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


[⬆ Vissza a tetejére](#tartalomjegyzék)

## Node-ok beállítása

[⬆ Vissza a tetejére](#tartalomjegyzék)

## Node-RED

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
<a href="https://learnembeddedsystems.co.uk/easy-raspberry-pi-iot-server">Raspberry Pi IoT Server</a>

[⬆ Vissza a tetejére](#tartalomjegyzék)