# Hotel Reservation System

A console-based hotel management and reservation system developed in C programming language. This project helps administrators manage room bookings, guest records, check-in/check-out dates, and pricing efficiently with file storage support.

## Features
- **Admin Authentication:** Secure login system with username and password verification (up to 3 attempts).
- **Add Reservations:** Record new room bookings including room number, guest name, check-in date, check-out date, and price.
- **Display Reservations:** View all active room reservations in a clean, tabular format.
- **Search & Update:** Instantly search for reservations by room number and update specific details (such as guest name, dates, or price).
- **Delete Reservations:** Remove or cancel existing bookings with automatic record rearrangement.
- **File Handling:** Automatically saves and loads reservation data from a text file (`hotel.txt`) to ensure data persistence between sessions.

## Technologies Used
- **Language:** C Programming
- **Concepts Applied:** 
  - Structures (`struct`)
  - File I/O (`fopen`, `fprintf`, `fscanf`)
  - String Manipulation (`strcmp`, `strcspn`)
  - Control Statements and Functions

## How to Run
1. Clone the repository or download the source code (`.c` file).
2. Open the code in any C-supported compiler or IDE (such as Code::Blocks, VS Code, or Dev-C++).
3. Compile and run the program.
4. Use the default login credentials provided in the code to access the admin panel.
