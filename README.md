# Hotel Management System (OOP Project)
**Author:** Niya Neykova  
**Language:** C++  
**Concepts:** Object-Oriented Programming (OOP)

---

## ✨ Features

### 👥 Users
- **Manager** – Full access: manage rooms, guests, reservations, users, and reports.
- **Receptionist** – Manage guests, reservations, and rooms.
- **Accountant** – View-only access to reservations and financial reports.

---

### 🛏️ Rooms
- Add new rooms with **automatic room numbers**.
- View all rooms or filter by **availability**.
- Room types:
  - Single
  - Double
  - Deluxe
  - Conference Hall
  - Apartment

---

### 👤 Guests
- Register new guests with **validations** (name, phone, email).
- Automatically update **guest status**:
  - Regular
  - Gold *(after several reservations – 10% discount)*
  - Platinum *(20% discount)*

---

### 📅 Reservations
- Create, edit, and delete reservations.
- **Smart dynamic pricing** based on season and occupancy.
- Discounts:
  - Gold guests: **10%**
  - Platinum guests: **20%**

---

### 📊 Reports
- Revenue by **day**, **month**, and **year**.
- Revenue and **occupancy by room type**.
- **Top earning rooms**.

---

### 🔐 Login System
- Users login with **username & password**.
- All operations are **logged** (`log.txt`).

---

## 🗂️ File Structure

| File             | Description                                  |
|------------------|----------------------------------------------|
| `main.cpp`       | Main menu and application logic              |
| `Guest.{h,cpp}`  | Guest information and validation             |
| `Room.{h,cpp}`   | Room data and dynamic pricing logic          |
| `Reservation.{h,cpp}` | Reservation management with validation and file persistence |
| `User.{h,cpp}`   | User authentication, roles, and file save/load |

---

## 💾 Data Persistence

**Data is saved/loaded from:**
- `guests.txt`
- `rooms.txt`
- `reservations.txt`
- `users.txt`

**Logs are appended to:**
- `log.txt`

**Reports are written to:**
- `report.txt`
- `room_report.txt`
---


Did I slay?💅🏻
