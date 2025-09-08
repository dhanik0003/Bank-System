# 💳 Bank System (C++ + SQLite)

![C++](https://img.shields.io/badge/language-C++-blue?style=for-the-badge)
![SQLite](https://img.shields.io/badge/database-SQLite-green?style=for-the-badge)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey?style=for-the-badge)
![Release](https://img.shields.io/badge/release-v1.0.0-orange?style=for-the-badge)
![License](https://img.shields.io/badge/license-MIT-lightblue?style=for-the-badge)

A console-based banking system built in **C++** with **SQLite** database integration.  
It simulates real-world banking operations for both users and admins with persistent data storage, modular code design, and an interactive terminal interface.

---

## 📖 Table of Contents
- [Features](#-features)
- [Project Structure](#-project-structure)
- [Installation](#️-installation)
- [Usage Examples](#️-usage-examples)
- [Screenshots](#-screenshots)
- [Contributing](#-contributing)
- [License](#-license)

---

## ✨ Features

### 👤 User Features
- Create a new account with personal details & PIN  
- Deposit and withdraw money securely  
- Check balance and view account details  
- Update details (Name, Address, PIN, etc.)  
- Logout with session safety  

### 🛠️ Admin Features
- Login with secure username & PIN  
- View all accounts in the system  
- Update user account details  
- Delete individual accounts or clear the entire database  
- Logout safely  

---

## 📂 Project Structure

```
Bank-System/
│── Bank-System/
│   ├── main.cpp               # Entry point
│   ├── account_manager.cpp    # Handles user & admin logic
│   ├── sqlite_helper.cpp      # SQLite operations
│   ├── console_utils.cpp      # Console utilities (cursor, colors, etc.)
│   ├── art.cpp                # ASCII art, banners
│   ├── helper.cpp             # Misc helper functions
|   ├── bank_server.db         # SQLite database (auto-created)
│   └── *.h files              # Header files
│
│── README.md                  # Project documentation
│── .gitignore                 # Git ignore rules
│── Screenshots/               # Screenshots & banner images

```
---

## ⚙️ Installation

```bash
# Clone the repository
git clone https://github.com/dhanik0003/Bank-System.git
```

```bash
# Navigate into the project
cd Bank-System/Bank-System
```

```bash
# Compile the program
g++ main.cpp account_manager.cpp sqlite_helper.cpp console_utils.cpp art.cpp helper.cpp sqlite3.o -o bank_system
```

```bash
# Run the program
./bank_system
```
---

## 🖥️ Usage Examples

User Journey
Open the program and create a new account.
Deposit money into your account.
Withdraw and check your balance.
Update your PIN or personal information.
Logout safely.

Admin Journey
Login using your admin username and PIN.
View all user accounts.
Update or delete user accounts.
Clear the database if required.
Logout.

---

## 📸 Screenshots

Startup Loading

<img width="1027" height="305" alt="Screenshot 2025-09-08 193820" src="https://github.com/user-attachments/assets/673c8ae3-ca35-4123-befb-c847d4b790cd" />


Login Menu/Main Menu

<img width="536" height="341" alt="Screenshot 2025-09-08 193257" src="https://github.com/user-attachments/assets/276c2cb4-d481-4307-9715-dadb4ebbe9e4" />

User Dashboard

<img width="446" height="252" alt="Screenshot 2025-09-08 193513" src="https://github.com/user-attachments/assets/f7c5a743-5f35-4ced-b1d7-49f442f72dca" />
<img width="430" height="385" alt="Screenshot 2025-09-08 193541" src="https://github.com/user-attachments/assets/b0d8a6e2-b297-4508-822d-57b260862083" />


Admin Panel

<img width="487" height="246" alt="Screenshot 2025-09-08 193630" src="https://github.com/user-attachments/assets/d100e3fc-a4d5-443e-a754-5f3e3d35b4be" />
<img width="484" height="363" alt="Screenshot 2025-09-08 193703" src="https://github.com/user-attachments/assets/c8eb944b-65cf-44df-b105-1f91d6c9d010" />

Exit

<img width="674" height="183" alt="Screenshot 2025-09-08 193734" src="https://github.com/user-attachments/assets/8027180f-1d59-4edf-b5a1-d3243418fa8d" />

---

## 🤝 Contributing

Contributions are welcome! 🎉

1. Fork the repository.

2. Create a new branch:

    git checkout -b feature-branch


3. Commit your changes:

    git commit -m "Add new feature"


4. Push to your branch:

    git push origin feature-branch


5. Submit a Pull Request.

    Please follow [Conventional Commits]([https://example.com](https://www.conventionalcommits.org/en/v1.0.0/))

---

## 📜 License

This project is licensed under the MIT License – feel free to use, modify, and distribute it.
