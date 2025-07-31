# Adaptive Cruise Control (ACC) in ADAS: Concepts & Interview Questions

This document provides a breakdown of Adaptive Cruise Control (ACC)—a key feature in Advanced Driver Assistance Systems (ADAS)—along with interview-style questions and sample answers to help you prepare for technical roles in automotive and embedded systems.

---

## 🚗 What is Adaptive Cruise Control (ACC)?

**Definition:**
Adaptive Cruise Control is an advanced driver assistance feature that automatically adjusts a vehicle’s speed to maintain a safe following distance from the vehicle ahead. Unlike traditional cruise control, ACC uses sensors (like radar and cameras) to monitor traffic conditions and dynamically control acceleration and braking.

---

## 🧠 Interview Questions & Sample Answers

### 1. How does Adaptive Cruise Control work?
**Sample Answer:**
ACC uses a combination of radar, camera, and sometimes LiDAR to detect vehicles ahead. It maintains a set speed but automatically slows down or speeds up to keep a safe distance. The system continuously monitors the relative speed and distance to the lead vehicle and adjusts throttle and braking accordingly.

### 2. What sensors are typically used in ACC systems?
**Sample Answer:**
- Radar sensors (usually long-range, mounted on the front grille) for distance and speed detection.
- Cameras (often mounted near the rear-view mirror) for object classification and lane detection.
- Some systems also use ultrasonic sensors or LiDAR for enhanced perception in complex environments.

### 3. What are the limitations of ACC?
**Sample Answer:**
- Poor weather conditions (rain, fog, snow) can impair sensor performance.
- Sudden cut-ins by other vehicles may not be handled smoothly.
- Stationary objects (e.g., stopped vehicles) may not always be detected.
- ACC is not a substitute for driver attention—it requires the driver to remain alert.

### 4. How is ACC different from Autonomous Emergency Braking (AEB)?
**Sample Answer:**
ACC is a comfort feature that maintains speed and distance, while AEB is a safety feature that automatically applies brakes to prevent or mitigate collisions. AEB is reactive and event-driven, whereas ACC is proactive and continuous.

### 5. What role does the camera play in ACC?
**Sample Answer:**
The camera helps in:
- Classifying objects (e.g., distinguishing between vehicles, pedestrians, and road signs).
- Lane detection to support lane-aware cruise control.
- Fusion with radar data to improve accuracy and reduce false positives.

---

## Other ADAS Feature Concepts & Interview Questions

### 6. What is Lane Keeping Assist (LKA)?
**Sample Answer:**
Lane Keeping Assist uses cameras to detect lane markings and gently steers the vehicle to keep it centered in its lane. It provides corrective steering input if the vehicle drifts out of its lane without signaling.

### 7. How does Autonomous Emergency Braking (AEB) work?
**Sample Answer:**
AEB uses radar and camera sensors to detect imminent collisions with vehicles, pedestrians, or obstacles. If a collision risk is detected and the driver does not react, the system automatically applies the brakes to prevent or mitigate the impact.

### 8. What is Traffic Sign Recognition (TSR)?
**Sample Answer:**
TSR uses forward-facing cameras and image processing algorithms to detect and classify road signs (e.g., speed limits, stop signs). The system can alert the driver or adjust vehicle behavior based on recognized signs.

### 9. What is Blind Spot Detection?
**Sample Answer:**
Blind Spot Detection uses radar sensors mounted on the sides or rear of the vehicle to monitor adjacent lanes. It alerts the driver if another vehicle is detected in the blind spot, typically via visual or audible warnings.

### 10. How do ADAS systems ensure safety and reliability?
**Sample Answer:**
ADAS systems undergo rigorous testing, including simulation, hardware-in-the-loop (HIL), and real-world driving scenarios. Redundancy, sensor fusion, and compliance with safety standards (e.g., ISO 26262) are key to ensuring reliable operation.

---

**End of ACC and ADAS Feature Interview Questions & Concepts**
