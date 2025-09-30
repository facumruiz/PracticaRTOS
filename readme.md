# FreeRTOS Linux Port

This repository contains **ONLY** the FreeRTOS Linux port that you can use right away. It doesn't include anything else. 

> **Note**: This port isn't real-time, but you can use it to try and learn about FreeRTOS as fast as possible. Happy tasking!

---

## ⚠️ Disclaimer

I'm neither the owner nor tightly involved in the FreeRTOS project (but I love it!). I'm just packing it for my future self and your convenience, nothing more. 

For any questions about the kernel, ports, memory models, and libraries, please use the [official FreeRTOS forums](https://forums.freertos.org/).

---

## 🚀 How to Use It

### 1. Clone or Download the Repository

**Option 1 - Clone via Git:**
```bash
git clone https://fjrg76@bitbucket.org/fjrg76/freertosv202107.00_linux_port_only.git
```

**Option 2 - Download:**
- Click the "Download repository" option (look for the 3 dots in a row just to the right of the Clone button)

- Uncompress it wherever you want


### 2. Navigate to the Demo
```bash
FreeRTOS/ → Demo/ → my_demo/
```

### 3. Build the Project
Open a terminal in the project folder and run:
```bash
make
```

### 4. Run the Demo

```bash
./build/posix_demo
```

## 6. Clean the Project

```bash
make clean
```