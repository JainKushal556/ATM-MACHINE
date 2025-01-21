<div align="center">
  <img src="https://img.icons8.com/fluency/96/atm.png" alt="ATM Icon">
  <h1>🏦 ATM Simulation System</h1>
  <p><b>A feature-packed ATM simulation program built with C and C++.</b></p>
</div>

---

<div align="center">

![Languages](https://img.shields.io/badge/Language-C%20%7C%20C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Contributions](https://img.shields.io/badge/Contributions-Welcome-brightgreen?style=for-the-badge&logo=github)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-success?style=for-the-badge)

</div>

---

## 🎯 **About The Project**
This **ATM Simulation System** offers users the ability to perform essential banking operations such as withdrawing cash, depositing money, sending funds, and more. Data is securely managed using text files, ensuring simplicity and reliability.

---

## ✨ **Key Features**
- 💵 **Cash Withdraw**: Safely withdraw money from your account.  
- 💰 **Cash Deposit**: Deposit funds directly into your account.  
- 🔄 **Send Money**: Transfer money from one card to another securely.  
- 📊 **Check Balance**: Instantly view your current balance.  
- 🔒 **Change PIN**: Update your PIN to enhance account security.  
- 🤔 **Forgot Password**: Recover access to your account safely.  

---

## 🛠️ **Technologies Used**
| Language | Purpose                 |
|----------|-------------------------|
| **C**    | Core functionalities    |
| **C++**  | Object-oriented features|
| **File Handling** | Secure data storage in `data.txt`|

---

## 🗂️ **Project Structure**

The **ATM Simulation System** is thoughtfully organized for simplicity and scalability:

```plaintext
📦 atm-simulation
├── 📜 atm.c                # Core ATM functionalities implemented in C
├── 📜 atm.cpp              # Optional C++ features for object-oriented design
├── 📜 data.txt             # Stores user data (card info, PINs, balances)
├── 📜 card_count.txt       # Tracks the total number of cards/accounts created
├── 📜 README.md            # Project documentation (you're reading this!)
├── 📜 LICENSE              # Licensing information (MIT license)
├── 📂 assets/              # Visual assets for the project
│   ├── atm_icon.png        # Icon for the README header
│   └── demo.gif            # GIF showcasing the program in action
├── 📂 test_cases/          # Test cases for program validation
│   ├── input1.txt          # Sample input for Cash Withdraw
│   ├── input2.txt          # Sample input for Cash Deposit
│   ├── input3.txt          # Sample input for Money Transfer
│   └── expected_output.txt # Expected results for the test cases
├── 📂 logs/                # Logs for debugging and tracking
│   └── error_log.txt       # Tracks errors encountered during execution
└── 📂 future/              # Modules for planned enhancements
    ├── encryption_module.c  # For encrypting sensitive data (upcoming feature)
    └── database_support.c   # For integrating a database system (upcoming feature)

