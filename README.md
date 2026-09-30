# WiFi Death V1

> A custom ESP32-C3 WiFi security/learning device with a 0.96" OLED display and four physical controls.

![WiFi Death V1](Images/hero.png)

## Project Status

**PCB:** Completed  
**Schematic:** Completed  
**Gerber files:** Completed  
**Firmware:** 🚧 Coming soon  
**Hardware build:** after gennting grant 

This project is currently at the **PCB completed / firmware development** stage.

---

## What is this?

WiFi Death V1 is a small custom ESP32-C3 based hardware project that I designed from the ground up.

The idea was to build a compact handheld device for learning about:

- ESP32-C3 hardware
- WiFi networking
- OLED displays
- Physical button interfaces
- PCB design with KiCad
- Embedded firmware
- Wireless security concepts

This project is also my way of learning how a complete hardware + firmware project comes together.

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

The PCB was designed in **KiCad**.

The repository contains:

- KiCad schematic
- KiCad PCB layout
- Gerber files
- Drill files
- BOM
- PCB production files

The PCB uses a **black solder mask** and has **"WIFI DEATH V1"** on the front silkscreen.

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
