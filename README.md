# Roboteq CANOpen Motor Control Library

## 📖 Overview
This project provides a **robust, structured, and modular library** for controlling **Roboteq SBL2360T** motor controllers over **CANOpen** using an **STM32F103C8T6 (Blue Pill)** microcontroller.  
It supports **two motors**:
- **LIFT** (Channel 2)
- **TURN** (Channel 1)  

The library implements **position control, speed control, open-loop control, emergency stop handling, and real-time feedback via CANOpen**.

---

## 🛠️ **Wiring & Hardware Setup**
### **🖥️ Required Components**
| Component             | Quantity | Purpose |
|----------------------|----------|---------|
| STM32F103C8T6 (Blue Pill) | 1  | Microcontroller for CAN Communication |
| ST-LINK V2 | 1  | STM32 Debugging |
| Roboteq SBL2360T | 1  | Motor Controller |
| SN65HVD230 CAN Transceiver | 1 | Converts STM32 CAN to Differential CAN Bus |
| 24-48V Power Supply | 1 | Powers the motors |
| Brushed/BLDC Motors | 2 | One for LIFT, one for TURN |

### **🔌 Wiring Diagram**
| STM32 (Blue Pill)  | SN65HVD230 CAN Transceiver | Roboteq SBL2360T | ST-Link V2 |
|--------------------|--------------------------|------------------|--------------|
| **PA12 (CAN_TX)**  | TX                       | CANH             | -            |
| **PA11 (CAN_RX)**  | RX                       | CANL             | -   |
| **3.3V**           | VCC                      | -                | 3.3V    |
| **GND**            | GND                      | GND              | GND    |
| **PB3**            | -                      | -              | SWO    |
| **SWCLK**           | -                      | -                | SWCLK    |
| **SWDIO**            | -                      | -              | SWDIO    |

Motor Wiring and setup instructions - https://docs.google.com/document/d/1Llj52syTjyN0EF2rgQW3TEIN6TNUVU3SYv9_LhJtZhs/edit?usp=sharing

⚠ **Important Note:** Ensure STM32 **3.3V logic level** is compatible with the CAN transceiver.

---

<!-- ## ⚙️ **Controller Configuration (Roboteq)**
### **📌 General Settings**
| Setting | Value | Notes |
|---------|-------|-------|
| **CAN Mode** | **CANOpen** | Ensures compatibility with SDO/PDO |
| **Node ID** | **1** | This is fixed in our library |
| **CAN Baud Rate** | **500 kbit/s** | Recommended for stable communication |
| **Motor 1 (TURN) Mode** | Open-loop / Closed-loop | Change as needed |
| **Motor 2 (LIFT) Mode** | Open-loop / Closed-loop | Change as needed | -->

### **📌 How to Configure**
1. Open **Roborun+ Utility**.
2. Navigate to **CAN Configuration**.
3. Set **CAN Mode** to **CANOpen**.
4. Set **Node ID** to `1`.
5. Set **Baud Rate** to `125 kbit/s`.
6. Configure each motor for **Open-loop (PWM) or Closed-loop (Position/Speed)**.
7. **Save & Apply** settings before testing.

---

## 📜 **Library Features**
### **✅ Motor Control**
| Function | Description |
|----------|-------------|
| `roboteq_setMotorCommand(MOTOR_TURN, speed);` | Open-loop control (-1000 to 1000) |
| `roboteq_setMotorSpeed(MOTOR_LIFT, rpm);` | Closed-loop speed control (-65535 to 65535 RPM) |
| `roboteq_setMotorPosition(MOTOR_TURN, position);` | Closed-loop absolute position control |
| `roboteq_setMotorAngle(MOTOR_LIFT, angle);` | Position control using degrees (0° to 360°) |

### **✅ Queries & Debugging**
| Function | Description |
|----------|-------------|
| `roboteq_queryVoltage();` | Read system voltage |
| `roboteq_queryEncoderPosition(MOTOR_TURN);` | Read current motor position |

---

## 📝 **How to Use**
1. **Setup wiring** as shown above.
2. **Flash firmware** onto STM32 using **STM32CubeIDE or PlatformIO**.
3. **Uncomment functions in `main.c`** to test each feature **one by one**.
4. **Check Serial Output** for CAN messages and debugging info.

### **Example: Move Motor to 90 Degrees**
```c
roboteq_setMotorAngle(MOTOR_LIFT, 90);
HAL_Delay(3000);
roboteq_queryEncoderPosition(MOTOR_TURN);
HAL_Delay(2000);
```

## 🖥️ **Enabling Serial Monitor in STM32CubeIDE**
To view debug messages and CAN responses via **Serial Wire (ITM Debugging)** in **STM32CubeIDE**, follow these steps:

### **🔹 Step 1: Enable ITM Debugging**
1. Open **STM32CubeIDE**.
2. Go to **Project Explorer** → Open your project.
3. Open **Core > Src > main.c**.
4. Add the following **ITM Debugging function** at the top of `main.c`:
    ```c
    int _write(int file, char *ptr, int len) {
        for (int i = 0; i < len; i++) {
            ITM_SendChar(*ptr++);
        }
        return len;
    }
    ```
5. This redirects `printf()` to the **Serial Monitor**.

### **🔹 Step 2: Enable SWO in Debug Configurations**
1. Click **Run > Debug Configurations**.
2. Select your project under **"GDB OpenOCD Debugging"**.
3. Go to the **Debugger** tab.
4. **Enable Serial Wire Viewer (SWV)** by checking:
   - ✅ **Enable Serial Wire Viewer (SWV)**
   - ✅ **SWO Clock: 72000000** (match with your CPU clock)
   - ✅ **Port 0**
5. Click **Apply** and **Debug**.

### **🔹 Step 3: Open SWV Console**
1. Start **Debugging (F11)**.
2. Go to **"Window > Show View > SWV > SWV ITM Data Console"**.
3. Click **Configure Trace** (gear icon).
4. Select **Port 0** and click **Start**.
5. You should now see `printf()` messages in **SWV Console**.

🚀 Now all debug messages (e.g., CAN responses, errors, and motor status) will be displayed in **STM32CubeIDE’s SWV console!** 🎯
