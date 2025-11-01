# 🧠 Design Notes

This document summarizes **design considerations, architecture decisions,** and **implementation notes** for each kernel module included in this repository.

---

## 🪶 Hello Module
- **Goal:** Verify module build and load/unload mechanisms.  
- **Design:** Uses `pr_info()` for logging instead of direct `printk()`.  
- **Why:** Keeps kernel log clean and consistent. Demonstrates `module_init()` and `module_exit()` hooks.  
- **File:** `examples/hello-module/hello.c`

---

## 📦 Character Device Driver
- **Goal:** Demonstrate basic user–kernel communication using `/dev` nodes.  
- **Design:** Uses `cdev` registration and dynamically allocates major/minor numbers.  
- **Key APIs:** `alloc_chrdev_region()`, `cdev_add()`, `file_operations`.  
- **Why:** Follows modern Linux device model practices, avoiding hard-coded major numbers.  
- **File:** `examples/char-driver/char_driver.c`

---

## ⚙️ Platform Driver
- **Goal:** Explore platform bus and device tree integration.  
- **Design:** Uses `platform_driver_register()` and `of_match_table` for DT binding.  
- **Why:** Platform devices are widely used in embedded systems with static hardware configuration.  
- **File:** `examples/platform-driver/platform_driver.c`

---

## ⚡ IRQ Demo
- **Goal:** Learn how interrupt handlers work.  
- **Design:** Registers an interrupt line via `request_irq()` and handles it safely with `spinlock`.  
- **Why:** Demonstrates concurrency handling, bottom halves, and interrupt safety.  
- **File:** `examples/irq-demo/irq_demo.c`

---

## 🌙 Power Mode Driver
- **Goal:** Experiment with kernel power management states.  
- **Design:** Uses suspend/resume callbacks and explores sleep state transitions.  
- **Why:** Helps understand energy optimization in embedded Linux.  
- **File:** `examples/power-mode/power_mode.c`

---

> 🧩 *These design notes evolve as more drivers and kernel experiments are added.*