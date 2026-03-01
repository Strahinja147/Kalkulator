# Advanced C++ Calculator – Shunting-Yard Expression Evaluator (C++, OOP, STL)

## Overview

A high-performance command-line mathematical expression evaluator implemented in C++.  
The project demonstrates advanced algorithmic logic using the **Shunting-Yard algorithm**, Object-Oriented Programming (OOP) principles, and sophisticated state management for Undo/Redo operations.

The calculator supports complex nested expressions, operator precedence, input validation, and session persistence to external files.

---

## Features

### Calculation Engine
- **Shunting-Yard Algorithm** implementation (Dijkstra’s algorithm) for Infix-to-RPN conversion
- **Reverse Polish Notation (RPN)** evaluator for efficient expression solving
- Full support for operator precedence (`/`, `*`, `+`, `-`) and nested parentheses `()`
- Robust error handling for division by zero and malformed mathematical syntax

### State & History Management
- **Undo/Redo** functionality implemented using dual `std::deque` structures
- Dynamic history tracking of all successfully calculated expressions
- Session persistence: Exporting calculation history to a custom `.txt` file

### Modular Command System
- **Command Pattern** implementation using `std::unordered_map` and **Lambda functions**
- Decoupled execution logic for system commands (`i`, `u`, `r`, `s`)
- Reference-based Dependency Injection to ensure memory efficiency and data consistency

### Input Validation
- Pre-calculation syntax analysis to ensure expression integrity
- Verification of operator placement, bracket matching, and character validity
- Hybrid validation for both mathematical expressions and system commands

---

## Architecture Overview

The project is modular and organized into multiple components:

- `Main.cpp` – Entry point, UI loop, and session management
- `KalkulatorMenadzer.cpp` – Central controller coordinating all modules
- `Parser.cpp` – Lexical analyzer (Lexer) that tokenizes raw strings
- `Validator.cpp` – Syntax checker ensuring input safety
- `Racunanje.cpp` – Core algorithmic implementation (Shunting-Yard & RPN)
- `Istorija.cpp` – Management of Undo/Redo stacks and File I/O

**Execution flow:**

User Input → Lexical Analysis (Parser) → Syntax Validation → Shunting-Yard Engine → RPN Evaluation → Result Storage

---

## Technologies & Concepts Used

- **C++17 / C++20 Standard**
- **STL Containers:** `std::vector`, `std::deque`, `std::unordered_map`
- **Functional Programming:** `std::function` and Lambda expressions
- **Memory Management:** Reference-based data passing (Zero-copy principle)
- **Error Handling:** `try-catch` blocks and custom exception throwing
- **File I/O:** `std::ofstream` for data persistence

---

## Memory Safety

The project is designed with modern C++ memory safety principles in mind:

- **RAII (Resource Acquisition Is Initialization)** is utilized to manage object lifecycles.
- Extensive use of **references (&)** instead of raw pointers to prevent memory leaks and null pointer exceptions.
- No manual `new` or `delete` calls; all memory is managed by STL containers and stack allocation.

---

## Build & Run

### Requirements
- Windows OS (recommended) or Linux with C++17 support
- Visual Studio 2022 (or any modern C++ compiler like GCC/Clang)

### Build

**Using Visual Studio:**
1. Open the `Kalkulator.sln` solution file.
2. Set the configuration to **Release** or **Debug**.
3. Press `Ctrl + Shift + B` to build the solution.

### Run

1. Press `F5` in Visual Studio or run the generated `.exe` from the output directory.
2. Enter the desired filename for history logging when prompted.

---

## Example Usage

Basic mathematical expression:

```text
Enter expression: (10 + 5) * 2 / (4 - 1)
Result: 10.000000
'i' - View history
'u' - Undo last operation
'r' - Redo last undone operation
's' - Save history to file
Enter expression: 10 / 0
GRESKA: Deljenje nulom nije moguce!
```
---
## Purpose

The primary goal of this project is to showcase the implementation of complex algorithms (Shunting-Yard) within a clean, modular, and maintainable C++ architecture, bridging the gap between simple CLI tools and professional software engineering.
