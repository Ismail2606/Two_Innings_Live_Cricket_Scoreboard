# 🏏 Two Innings Live Cricket Scoreboard 

A terminal-based cricket match simulation written in **C**, capable of handling a **two-innings match** with live score updates, player statistics, bowling figures, and match summary saved to a file.

---

## 📌 Project Overview

This project simulates a real-world cricket match between two teams:

* Takes team and player details as input
* Runs **two innings** (batting & chasing)
* Maintains **batting and bowling statistics**
* Displays live score updates
* Saves match summary to a file

The focus is on **modular programming, structures, pointers, and file handling in C**.

---

## 🎯 Features

* Two-innings cricket match simulation
* Custom team names and player names
* Live score tracking
* Batting statistics:

  * Runs
  * Balls faced
  * Fours & Sixes
  * Out status
* Bowling statistics:

  * Overs & balls
  * Runs conceded
  * Wickets
* Target-based second innings
* Match summary stored in a file

---

## 🧠 Concepts Used

* Structures (`struct`)
* Arrays of structures
* Functions and pointers
* Modular programming
* Standard I/O
* File handling
* Input validation

---

## 🗂️ Project Structure

```text
.
├── main.c              # Program entry point
├── scoreboard.h        # Structure definitions & function prototypes
├── scoreboard.c        # Core match logic
├── file.c              # File handling (save match summary)
├── README.md           # Project documentation
```

---

## ▶️ How to Compile & Run

```bash
gcc main.c scoreboard.c file.c -o scoreboard
./scoreboard
```

---

## 🧪 Sample Flow

1. Enter total overs
2. Enter Team A & Team B names
3. Enter players for both teams
4. Team A plays first innings
5. Team B chases the target
6. Match summary saved to file

---

## 📄 Output File

The match result and scorecard are saved in a text file for future reference.

---

## 🚀 Future Enhancements

* Display live scoreboard on **CLCD (Character LCD)**
* Update runs, wickets, and extras using **keypad input**
* Real-time ball-by-ball score update without terminal input
* Embedded system version using **microcontroller + CLCD + keypad**

---

## 👨‍💻 Author

**Ismail Pasha**
Embedded Systems & C Programmer

---
