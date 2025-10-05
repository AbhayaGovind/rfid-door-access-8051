# RFID Door Access Control System using 8051 Microcontroller

This project implements an **RFID-based door access control system** using an **AT89C51 microcontroller**. It identifies users through RFID tags — **authorized tags open the door**, while **unauthorized tags keep it locked**. The system is programmed in **assembly language** and uses a **DC motor** to represent door movement.

---

##  Project Overview
The system reads the unique ID of an RFID tag through the serial interface.  
If the scanned tag matches a stored valid ID, the microcontroller activates the motor driver to open the door.  
If not, the motor stays still, indicating the door remains locked.

---

##  Features
- RFID-based authentication  
- Uses **L293D motor driver** for door control  
- Displays messages on **16x2 LCD (LM016L)**  
- Easy to implement and understand for beginners  
- Assembly language-based implementation on **8051**  

---

##  Components Used
| Component | Description |
|------------|-------------|
| AT89C51 | 8051 Microcontroller |
| EM-18 RFID Reader | 125 kHz RFID module |
| LM016L LCD | 16x2 character display |
| L293D | Motor driver IC |
| DC Motor | Represents door lock mechanism |
| Battery (5V–12V) | Power supply |
| RFID Tags | Authorized and unauthorized cards |

---

##  Software & Tools
- **Keil µVision** – for assembly programming  
- **Proteus** – for simulation and testing  

*(No Flash Magic or external programmer needed for simulation.)*

---

## Working Principle
1. The RFID reader sends the 12-character tag ID through UART.  
2. The microcontroller compares it with stored valid IDs.  
3. If the ID matches:  
   - LCD shows “ACCESS GRANTED”  
   - Motor rotates to open the door for a few seconds  
4. If not matched:  
   - LCD shows “ACCESS DENIED”  
   - Motor remains stopped (door closed)

---

## Circuit Description
- **RFID TX → RX (P3.0)** of AT89C51  
- **LCD (LM016L)** connected to Port 1  
- **L293D** connected to Port 2 for motor control  
- **Battery** powers both microcontroller and motor  

*(See circuit diagram in repository folder for reference.)*

---

##  Output
| RFID Tag | LCD Message | Motor Action |
|-----------|--------------|--------------|
| Authorized | ACCESS GRANTED | Door opens |
| Unauthorized | ACCESS DENIED | Door locked |

---

**Abhaya Govind**  
Government College of Engineering, Kannur  
Project: *RFID Door Access Control System using 8051 Microcontroller*

---

## Keywords
`RFID` `8051` `assembly language` `microcontroller` `door lock` `access control` `L293D` `RFID project` `embedded systems` `Keil` `Proteus`

---

## 🪪 License
This project is open-source. Feel free to use, modify, and share it for learning purposes.
