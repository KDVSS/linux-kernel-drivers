# ⚙️ Kernel Setup Guide

This document helps you set up a development environment for building and testing Linux kernel modules.

---

## 🧩 1. Install Required Packages
### On Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r) bc git make flex bison libncurses-dev

On Fedora:

sudo dnf groupinstall "Development Tools"
sudo dnf install kernel-devel kernel-headers ncurses-devel

## 🧰 2. Verify Kernel Headers
ls /lib/modules/$(uname -r)/build

## 🧱 3. Build Your First Module
cd examples/hello-module
make
sudo insmod hello.ko
dmesg | tail -n 10
sudo rmmod hello

## 🧪 4. Using QEMU for Safe Testing
sudo apt install qemu-system-x86
qemu-system-x86_64 -kernel bzImage -append "console=ttyS0" -nographic
