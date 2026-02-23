# 🚇 Metro Booking Service

## 📌 Overview

This project implements a Metro Booking Service that models a metro network as a graph and computes the optimal route between two stops, including proper interchange handling.

The system also supports booking creation and generates a unique QR-compatible string for each booking.

Implemented in **C++** using Object-Oriented Programming principles.

---

## 🧠 Approach

- Metro network modeled as a **graph (adjacency list)**
- Stops → Nodes
- Connections → Edges with route ID
- **Dijkstra’s Algorithm** used for optimal path computation
- Transfer penalty applied when route changes

**Total Cost = Distance + Transfer Penalty**

Time Complexity: `O(E log V)`

---

## 🎟 Booking Features

- Validates source and destination
- Computes optimal route
- Creates booking only if path exists
- Generates QR-compatible string using hashing
- Handles edge cases (invalid stop, same stop, no path)

---

## 🖥 Sample Metro Lines

- Blue: A → B → C → D  
- Yellow: C → E → F → I  
- Red: G → H → D → J → I  

Interchange Stations:
C, D

---

## ▶ How to Run

Compile:
```bash
g++ metro.cpp -o metro
```
```bash
./metro
```
