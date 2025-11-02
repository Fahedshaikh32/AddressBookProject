📘 Address Book Management System (C Project)

A modern and user-friendly **Address Book System** written in **C language**, designed to manage, search, and organize contacts efficiently using file handling and validation.

🚀 Features
- 📇 Add, view, edit, delete, and search contacts  
- 💾 Data stored permanently in a CSV file  
- 🧠 Input validation for accurate entries  
- 🖥️ Clean, menu-driven user interface  
- ⚙️ Modular code for better readability and maintenance  

⚙️ How to Compile & Run

🧰 Using GCC (Linux / Windows with MinGW)

```bash
gcc main.c contact.c file.c validate.c -o addressbook
./addressbook
```

| File                      | Description                                            |
| ------------------------- | ------------------------------------------------------ |
| main.c                    | Entry point and menu handling                          |
|  contact.c  /  contact.h  | Core contact management (add, delete, search, edit)    |
|  file.c  /  file.h        | Handles CSV read/write for saving and loading contacts |
|  validate.c               | Validates user input (phone numbers, names, etc.)      |
|  contacts.csv             | Stores all saved contact data                          |


🧑‍💻 Developer

Fahed Shaikh
🎓 BE in Electronics & Telecommunication Engineering
💼 Embedded Systems Student at Emertxe, Bangalore


