# WiFi Death V1

> A custom ESP32-C3 WiFi testing/hacking device with a 0.96" OLED display and four physical controls.

<img width="950" height="665" alt="image" src="https://github.com/user-attachments/assets/78fe573b-2bf0-43dc-9432-4b25d3a0b8f2" />

## Required Library Setup

Open Arduino IDE
Install OLED libraries: Tools -> Manage Libraries -> search Adafruit SSD1306 -> install
fig1

Add esp32 additional board manager URL: Files -> Preferences -> add https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json to Additional Boards Manager URLs

Install esp32 board manager: Tools -> Board -> Boards Manager -> search esp32 -> install esp32 by Espressif Systems

## Firmware Installation 

1. Clone the repo or Download raw .zip file
2. open Arduino IDE
3. open Wifi_Death_v1.ino
4. upload to your device

---

## What is this?

WiFi Death V1 is a custom ESP32-C3 based wifi hacking/testing hardware project that I designed , The idea started when i saw a video of spacehunns esp8266 deauther and i knew i wanted to make this but with different board like the c3.

## Key Features 
• WiFi Scanning: The project can scan for available WiFi networks in the vicinity and display information about them, such as their name, signal strength, and channel.
• Deauthentication Attacks: With the push of a button, the project can perform deauthentication attacks on specific networks or clients, making it useful for penetration testing and network security auditing.
• 0.96-inch OLED Display: The project uses a small OLED display to show information about the networks in real-time.
• Circuit Design: The project's circuit is relatively simple and only requires connecting the ESP32 board to the OLED display.

---

## Hardware

The current PCB uses:

| Component | Quantity |
|---|---:|
| ESP32-C3 SuperMini | 1 |
| 0.96" 128×64 I2C OLED | 1 |
| 6×6×5 mm tactile buttons | 4 |
| Custom PCB | 1 |

### Controls

The four buttons are:

- **UP**
- **DOWN**
- **SELECT**
- **BACK**

The OLED is used as the main display.

---

## Display

The project uses a:

**0.96" 128×64 SSD1306 I2C OLED**

The OLED is connected directly to the ESP32-C3.

---

## ESP32-C3 Pinout

| Function | ESP32-C3 GPIO |
|---|---:|
| OLED SDA | GPIO6 |
| OLED SCL | GPIO7 |
| UP | GPIO3 |
| DOWN | GPIO4 |
| BACK | GPIO2 |
| SELECT | GPIO1 |

The board is powered through the **USB-C connector on the ESP32-C3 SuperMini**.

---

## PCB

  <img width="1162" height="826" alt="pcb shematics" src="https://github.com/user-attachments/assets/b630e069-4af2-4a78-9cc9-32ca22a03653" />

  <img width="813" height="613" alt="image" src="https://github.com/user-attachments/assets/8ee5f737-824a-4eb3-bf45-3c833226354f" />


  <img width="892" height="682" alt="image" src="https://github.com/user-attachments/assets/c0e94a93-b898-4606-a8b2-27cf3b30f38e" />

  
  <img width="897" height="638" alt="image" src="https://github.com/user-attachments/assets/8c6de4d5-0b36-48f6-b748-5e78e25dcdb8" />


The PCB was designed in **KiCad**.

The repository contains:

- KiCad schematic
- KiCad PCB layout
- Gerber files
- Drill files
- BOM
- PCB production files

The PCB uses a **black solder mask** so it looks cool and has **"WIFI DEATH V1"** on the front silkscreen. I also added the GitHub repo link in the backside of the pcb

---

## 📁 Repository Structure

```text
Wifi-Death-V1/
│
├── Firmware/
│   └── Firmware source
│
├── Images/
│   └── Project photos and renders
│
├── PCB/
│   ├── KiCad project
│   ├── Schematic
│   ├── PCB layout
│   └── BOM
│
├── Production/
│   └── Gerber and drill files
│
└── README.md
