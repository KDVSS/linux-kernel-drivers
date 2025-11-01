# 🪲 Kernel Debugging & Tracing Guide

This guide covers common debugging, tracing, and performance analysis techniques for Linux kernel modules.

---

## 🧾 1. Checking Kernel Logs
```bash
dmesg | tail -n 20

## 🧠 2. Enabling Dynamic Debug Messages
```bash
sudo bash -c 'echo "file hello.c +p" > /sys/kernel/debug/dynamic_debug/control'

## 🧩 3. Using ftrace
```bash
sudo mount -t tracefs nodev /sys/kernel/tracing
echo function_graph > /sys/kernel/tracing/current_tracer
cat /sys/kernel/tracing/trace

## 🧵 4. Using kgdb (Kernel Debugger)
```bash
kgdbwait kgdboc=ttyS0,115200
qemu-system-x86_64 -s -S -kernel bzImage -append "console=ttyS0 kgdbwait"
gdb vmlinux
(gdb) target remote :1234

##⚡ 5. Profiling with perf
```bash
sudo perf top
sudo perf record -a sleep 5
sudo perf report

