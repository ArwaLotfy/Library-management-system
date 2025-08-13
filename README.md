# Library Management System (C++)

A console-based library management system for the **Programming Fundamentals** course (C-CS112, Spring 2025).  
It supports two types of users: **Librarians** and **Customers**, with features for managing and borrowing books.

---

## Features

### For Librarians
- Add or delete user accounts
- View user information
- Add, remove, or search books
- View borrowed and available books

### For Customers
- Search books (by title, author, or category)
- View borrowed books
- Borrow up to 5 books
- Return books

---

## How to Compile and Run

1. **Navigate to the `SRC` folder**  
   This folder contains all `.cpp` and `.h` source files.

2. **Compile the project** (example using g++):
   ```bash
   g++ *.cpp -o library
