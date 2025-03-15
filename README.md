# TrackHer - Period Tracking Calendar

TrackHer is a lightweight, offline period tracking application developed in C and Raylib. It allows users to log menstrual cycles, predict future periods, and estimate ovulation.

## 🚀 Features
- **Menstrual Cycle Tracking** – Log period start dates and symptoms.
- **Cycle Prediction Algorithm** – Estimates next period and fertile window.
- **Interactive Raylib UI** – Simple graphical interface for ease of use.
- **Offline & Privacy-Focused** – No internet connection required.

## 💻 Tech Stack
- **Programming Language:** C
- **Graphics & UI:** Raylib
- **Data Storage:** TXT/DAT file handling

## 📂 Project Structure

```
📦 code
 ┣ 📂 data                # Stores user cycle data and log_in records
 ┣ 📂 images              # UI assets i.e. icons and image
 ┣ 📂 src                 # Source code
 ┃ ┣ 📜 backend.c         # Core logic for cycle tracking
 ┃ ┣ 📜 backend.h         # Header file for backend functions
 ┃ ┣ 📜 calender.c        # Calendar functionalities
 ┃ ┣ 📜 calender.h        # Header file for calendar logic
 ┃ ┣ 📜 login.c           # User authentication
 ┃ ┣ 📜 login.h           # Header file for login system
 ┃ ┣ 📜 main.c            # Main entry point and login ui
 ┃ ┣ 📜 page_choice.c     # Handles page selection
 ┃ ┣ 📜 page_choice.h     # Header file for page choice
 ┃ ┣ 📜 page_insight.c    # Insights and analytics
 ┃ ┣ 📜 page_insight.h    # Header file for insights
 ┃ ┣ 📜 trial.exe         # Compiled executable for testing
```

## 🛠 Installation & Setup

### Prerequisites
- GCC Compiler
- Raylib (Graphics Library)

### Steps to Install

#### Clone the repository:
```bash
git clone https://github.com/connect-Prajwal-khanal/C_Programming_081BEI.git
```

#### Install Dependencies:
**Linux (Ubuntu/Debian):**
```bash
sudo apt update && sudo apt install build-essential libasound2-dev
```

#### Install Raylib:
```bash
sudo apt install libraylib-dev
```

**Windows:**  
Download and install Raylib manually.

#### Compile the Project:
```bash
gcc -o trial.exe main.c login.c page_choice.c page_insight.c backend.c calender.c -I C:\raylib\include -L C:\raylib\lib -lraylib -lm -lwinmm -lgdi32
```

#### Run the Application:
```bash
./trackher
```

## 🤝 Contributing
1. Fork the repository.
2. Create a feature branch:  
   ```bash
   git checkout -b 28343738
   ```
3. add changes:  
   ```bash
   git add .
   ```
4. Commit changes:  
   ```bash
   git commit -m 'Added new feature'
   ```
5. Push to the branch:  
   ```bash
   git push origin 28343738
   ```
6. Create a pull request.

## 💡 Designed and Developed by:

Prajwal Khanal, Ranjana Kumari Jha, Shakshi Gyawali, Shaunak Baniya 🚀

