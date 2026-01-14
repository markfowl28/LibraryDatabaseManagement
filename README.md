# C++ SQLite Library Management System

## Overview

This project is a **console-based Library / Inventory Management System** written in **modern C++** using **SQLite** as the embedded database. It demonstrates safe database access, clean architecture, and modern C++ best practices such as **RAII**, **prepared statements**, and **separation of concerns**.

The application allows a user to:

* View all books
* Search for books (case-insensitive)
* Add new books
* Update existing book entries
* Delete books safely

This project was built as a **portfolio piece** to showcase practical C++ skills, database interaction, and thoughtful system design.

---

## Key Technical Highlights

### Modern C++ Practices

* **RAII (Resource Acquisition Is Initialization)** for managing SQLite statements
* Explicit ownership and lifetime management
* No raw `new` / `delete`
* Clear distinction between pointers and references

### Database Safety

* **Prepared statements only** (no string concatenation)
* SQL injection-safe parameter binding
* Automatic statement finalization
* Case-insensitive searching using SQLite collations

### Architecture

The project separates responsibilities into logical modules:

* **Queries** – All `SELECT` operations
* **Commands** – All `INSERT`, `UPDATE`, and `DELETE` operations
* **Statement Wrapper** – RAII abstraction over `sqlite3_stmt*`
* **Models** – Plain data structures representing database rows

This mirrors real-world data-access patterns and improves maintainability.

---

## Project Structure

```
src/
├── Database.h / Database.cpp        # Database connection management
├── Statement.h / Statement.cpp      # RAII wrapper for prepared statements
├── BookQueries.h / BookQueries.cpp  # Read-only database operations
├── BookCommands.h / BookCommands.cpp# Insert / Update / Delete operations
├── Models.h                         # Data structures (Book/User)
├── main.cpp                         # Application entry point
```

---

## Core Features

### View All Books

Retrieves and displays all book records from the database using prepared statements.

### Search (Case-Insensitive)

Allows users to search for books by title regardless of casing using:

```sql
COLLATE NOCASE
```

This avoids application-side string manipulation and preserves index usage.

### Add Book

Safely inserts a new book using a prepared `INSERT` statement. Parameters are bound explicitly and validated before execution.

### Update Book

Users can selectively update:

* Title
* Author
* Availability status

Each update is handled by a dedicated function to avoid dynamic SQL and ensure clarity.

### Delete Book

Deletes a book by identifier using a prepared `DELETE` statement. The application confirms success and handles the case where no matching record exists.

---

## Error Handling Strategy

* SQLite execution errors are treated as failures
* Empty query results are handled gracefully (not treated as exceptions)
* Functions return meaningful status values to the caller

This keeps control flow explicit and predictable.

---

## Why SQLite?

SQLite was chosen because:

* It requires no external server
* It integrates cleanly with C++ via a C API
* It is widely used in production environments

The project focuses on **safe API usage**, not just basic SQL.

---

## Build & Run

### Requirements

* C++17 compatible compiler
* SQLite3 development library

### Build (example)

```bash
g++ -std=c++17 src/*.cpp -lsqlite3 -o library_app
```

### Run

```bash
./library_app
```

---

## What This Project Demonstrates

* Strong understanding of C++ memory management
* Safe interaction with C-style APIs
* Real-world CRUD database operations
* Clean separation of responsibilities
* Thoughtful handling of edge cases

---

## Future Improvements

* Transactions for batch operations
* Optional logging layer
* Unit testing for database commands
* Configuration-driven database initialization

---

## Author

Mark Fowler

---

*This project was built as a learning exercise and portfolio demonstration to highlight modern C++ development practices.*

