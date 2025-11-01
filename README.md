# 🐧 Linux Kernel Driver Development

This repository is a collection of **Linux kernel development projects** — including custom kernel modules, device drivers, and experiments that explore how the Linux kernel interacts with hardware and user space.  
It demonstrates low-level programming, debugging, and performance optimisation within the Linux kernel environment.

---

## 🧠 About
This project serves as a **practical learning and showcase repository** for developing Linux kernel drivers and modules.  
Each directory inside `/examples` contains a self-contained kernel project focusing on a specific kernel subsystem or concept.

You’ll find examples of:
- Writing and building kernel modules in C  
- Implementing character & platform device drivers  
- Handling interrupts and device trees  
- Using kernel timers, workqueues, and synchronisation mechanisms  
- Power management experiments and energy-efficient driver design  

---

## 🎯 Goals
- Demonstrate **hands-on Linux kernel programming** skills  
- Explore kernel subsystems through small, reproducible examples  
- Apply debugging and tracing tools (`dmesg`, `ftrace`, `kgdb`, etc.)  
- Practice clean and documented kernel development workflows  
- Build a strong foundation for **system-level software** and embedded Linux work  

---

## 📂 Repository Structure
├── README.md  
├── docs/ # Design notes, debug guides, references  
├── examples/  
│ ├── hello-module/ # Basic loadable kernel module  
│ ├── char-driver/ # Character device driver  
│ ├── platform-driver/ # Platform device & device tree example  
│ ├── irq-demo/ # Interrupt handling example  
│ └── power-mode/ # Power management and sleep demo  
├── scripts/ # Build and testing automation scripts  
├── tools/ # User-space test programs for drivers  
└── .github/workflows/ # CI configuration for module builds
```
