<p align="center">
  <img src="https://img.shields.io/github/license/Nuggets10/ZshLand?style=for-the-badge&color=9C27B0" />
  <img src="https://img.shields.io/github/stars/Nuggets10/ZshLand?style=for-the-badge&color=FBC02D" />
  <img src="https://img.shields.io/github/forks/Nuggets10/ZshLand?style=for-the-badge&color=FF9800" />
  <img src="https://img.shields.io/github/commit-activity/y/Nuggets10/ZshLand?style=for-the-badge&color=03A9F4" />
  <img src="https://img.shields.io/github/contributors/Nuggets10/ZshLand?style=for-the-badge&color=00BCD4" />
  <img src="https://img.shields.io/github/languages/top/Nuggets10/ZshLand?style=for-the-badge&color=FF5722" />
  <img src="https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Nuggets10/ZshLand/main/.github/badges/loc-badge.json&style=for-the-badge&color=4CAF50" />
</p>

# 🕹️ | ZshLand
ZshLand is a lightweight CLI survival game in a randomly generated world with different terrain types and various resources. The project's name comes from the word Zsh, abbreviation for Z shell, merged with Land, representing the vast world you can explore.
<p align="center">
  <img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/45916444-1a5c-4ca9-8543-b7c7f1deaaa8" />
</p>

## 📚 | Sections

- [📦 | Installation](#--installation)
- [🖼️ | Screenshots](#--screenshots)
- [📜 | Main menu](#--main-menu)
- [❓ | Game wiki](#--game-wiki)
- [⚠️ | Report an issue](#--report-an-issue)
- [📲 | Contribute](#--contribute)
- [🚧 | Roadmap](#--roadmap)

## 📦 | Installation
There are two ways of installing the project on your system. You can either download the latest release (WIP) or compile all the necessary files yourself.
To compile the project follow these steps:
- Clone the project to your system using `git clone https://github.com/Nuggets10/ZshLand.git`
- Navigate to the project root folder, open a terminal and run the following commands depending on your distro.

### Debian / Ubuntu / Kali
- Update the packages list:  
  `sudo apt update`
- Install required dependencies:  
  `sudo apt install clang build-essential libncursesw6 libncursesw6-dev`
- Compile the project:  
  `clang++ -fcolor-diagnostics -fansi-escape-codes -g \
  -I include src/**/*.cpp -lncursesw -o src/core/main`
- Execute the compiled file:  
  `./src/core/main`

---

### Arch Linux / Manjaro
- Update the packages list:  
  `sudo pacman -Syu`
- Install required dependencies *(includes ncursesw support)*:  
  `sudo pacman -S clang ncurses`
- Compile the project:  
  `clang++ -fcolor-diagnostics -fansi-escape-codes -g \
  -I include src/**/*.cpp -lncursesw -o src/core/main`
- Execute the compiled file:  
  `./src/core/main`

---

### Fedora
- Update the packages list:  
  `sudo dnf check-update`
- Install required dependencies *(includes ncursesw support)*:  
  `sudo dnf install clang ncurses ncurses-devel`
- Compile the project:  
  `clang++ -fcolor-diagnostics -fansi-escape-codes -g \
  -I include src/**/*.cpp -lncursesw -o src/core/main`
- Execute the compiled file:  
  `./src/core/main`

## 🖼️ | Screenshots

<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/916c25ff-69f0-4a7b-8acb-21a28a9c9684" />
*An example of random terrain generation*

## 📜 | Main menu
The main menu provides you with two main UI elements:
- A rectangle in the upper part, containing the changelog of the installed version.
-  A selection menu. The options you can choose from are:
   - **"Start"**. Creates a brand new world.
   -  **"Report a bug"**. Gives a brief explanation on what you should open an issue for and gives you a link to the "Issues" tab of this repository.
   -  **"Contribute"**. Gives a brief explanation on how to contribute and gives you a link to the "Pull requests" tab of this repository.
   -  **"Quit"**. Closes the game.
  
<img width="1920" height="1080" alt="Main menu screenshot" src="https://github.com/user-attachments/assets/94e63bae-7a34-4df5-8797-3eb4f09b4d8c" />

## ❓ | Game wiki
In the wiki you'll find all types of informations about the gameplay of ZshLand. Wiki's pages range from lists of available in-game items to full tutorials on how to play. [Wiki Home Page](https://github.com/Nuggets10/ZshLand/wiki/%F0%9F%8F%A1-%7C-Start-Page)

## ⚠️ | Report an issue

### 1. Title

Keep it concise and descriptive.
Avoid vague titles like "Problem" or "Doesn’t work".

### 2. Type of Issue

Add at least one label (tag) to identify the nature of the issue.
**This is mandatory.**

Choose from:
- Bug | low/medium/high priority
- Enhancement
- Documentation
- Question

**Invalid, Wontfix and Duplicate tags should only be used to filter issues by mantainers.**

### 3. Issue Template

Please fill out the relevant sections below based on the type of issue:

**Bug report**

```
**What is the problem?**
Describe what isn’t working. Be clear and specific.

**Steps to Reproduce:**
1. Go to '...'
2. Click on '...'
3. Scroll down to '...'
4. See error

**Expected Behavior:**
Explain what you expected to happen.

**Actual Behavior:**
Describe what actually happens.

**Screenshots (if applicable):**
Attach images or videos to help explain.

**Environment:**
- OS: [e.g. Windows 11 / macOS Ventura]
- App version: [e.g. v1.2.3]
```

**Feature request/Enhancement**
```
**What is the feature or improvement you're requesting?**
Describe the functionality clearly.

**Why is it useful or important?**
Explain the benefit or use case.

**Additional context:**
Include any relevant examples, mockups, or references.
```

**Documentation Issue**
```
**What needs to be changed or added?**
Explain what’s wrong or missing.

**Where is it located?**
Provide the file name or URL (if public).

**Suggested fix (optional):**
Include a possible correction or contribution.
```

**Question**
```
**What do you need help with or want to understand?**
Provide context when necessary.

**What have you tried so far?**
Let contributors know what you’ve done to solve it.
```

## 📲 | Contribute
Feel free to contribute your own code to the project, even if you're a complete beginner and just want to help.
There aren't any rules to follow, just try to make your code maintenable and clean.

**It is preferable to contribute on features listed in the [Roadmap section](#--roadmap).**

If there's anything to modify, I'll personally take care of that or I'll alert you on the pull request before merging to the main branch.

**Don't know how to contribute?**
The simplest way is to fork the repository on your own account, make your modifications and just send a pull request to this repository. After proper revisioning, if the request is accepted, you can freely remove the forked repository from your account.

## 🚧 | Roadmap
The following are the features I am currently working on. Feel free to contribute your own code to speed up development times.
- In-game UI panel to display player's stats such as inventory, hunger, thirst and more.
- Inventory and crafting system
- Resource collection
- Survival mechanics (hunger, thirst, maybe stamina)
