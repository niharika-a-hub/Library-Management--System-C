# Library-Management--System-C
A C-based Library Management System using File Handling (CRUD operations).
# Library Management System (C-Language)

A robust, console-based application designed to manage book records using **Binary File Handling**. This project demonstrates core computer science concepts like CRUD operations, data structures, and persistent storage in C.

# Key Features
* **Secure Admin Login:** Password-protected access to the system.
* **Persistent Storage:** Uses `library.dat` to ensure data remains saved after closing the program.
* **Smart Search:** Case-insensitive partial matching to find books by title or keyword.
* **Borrow/Return Logic:** Real-time tracking of book availability.
* **Popularity Tracker:** Increments a "Read Count" every time a book is issued.
* **Efficient Memory Management:** Uses `fseek()` for direct-access file updates.

# Technical Concepts Used
* **Structures (`struct`):** To define custom data types for books.
* **File I/O:** `fopen`, `fwrite`, `fread`, and `fseek` for binary database management.
* **Casting:** Explicit constant conversion for file offsets.
* **String Manipulation:** `strstr` for searching and buffer clearing for stable inputs.

# How to Run
1.  **Clone the Repo:** ```bash
    git clone [https://github.com/niharika-a-hub/Library-Management--System-C.git](https://github.com/niharika-a-hub/Library-Management--System-C.git)
    ```
2.  **Compile:** Use any C compiler (GCC/Clang).
    ```bash
    gcc main.c -o library
    ```
3.  **Run:**
    ```bash
    ./library
    ```
4.  **Default Password:** `admin123`

---
*Created by Niharika Chouhan*
