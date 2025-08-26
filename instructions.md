---
title: "Lab 1: Terminal Basics"
subtitle: "AI 1020 | MBZUAI | Fall 2025 (Bakita/Yan)"
author: "Author: Noah Weaver and Prof. Bakita"
---

These steps were last updated <img src onerror="this.replaceWith(document.lastModified)"/>.

Welcome to your AI1020 lab! Today you'll learn to navigate the command line and use basic text editing tools. By the end, you'll have assembled a program that creates a 3D animated molecule - and it will congratulate you personally!

**What you'll practice:**

- Basic terminal navigation
- File searching and copying
- Opening and closing vim

---

## PART 0: Download Assignment

- Type: `ssh ai1020.mbzu.ae` and enter the password you set when prompted (remember, no characters will appear).
- Type:`git clone https://github.com/JoshuaJB/AI1020_LAB_1.git` to download the lab code using git.
- Type: `cd AI1020_LAB_1` to move to the location with the downloaded code.

## PART 1: Navigation Basics (part1/ folder)

**Commands you'll learn:**

- `pwd` - shows your current directory location
- `ls` - lists files and folders 
- `cd` - changes directories
- `cat` - displays file contents
- `vim` - opens the text editor

### Step 1: Where am I?
- Type: `pwd`
- This shows your current location in the file system

### Step 2: What's here?  
- Type: `ls`
- You should see intructions.md and three folders: part1, part2, part3

### Step 3: Enter the basics folder
- Type: `cd part1`
- Type: `pwd` again - notice how your location changed!
- Type: `ls` - see what files are in this folder

### Step 4: Look inside a file
- Type: `cat headers.c`
- This shows you what's inside the file without opening an editor

### Step 5: Open your first file in vim
- Type: `vim headers.c`
- Use arrow keys to move around and read the content
- When you're ready to leave: Type Esc (to ensure you're in normal mode) `:q` and press Enter

### Step 6: Copy the headers to your final program
- Make sure you're in the part1 folder (type `pwd` to check)
- Type: `vim headers.c`
- Select all the content:
  * [Press `ESC` to make sure you're not in edit mode]
  * Use the arrow keys to move your cursor to the beginning of the file
  * Type: 'V' to enter Visual Mode (enables selection)
  * Use the arrow keys to move your cursor to the end of the file (selecting everything)
  * Type: 'y' to copy the selected text (short for "yank"---vim's term for copying)
- Exit this file: Type Esc (to ensure you're in normal mode) then `:q` and press Enter

**Accidentally put some text you didn't want to in your file? Add an exclaimation mark after the q to exit without saving; _i.e._, type `:q!`.**

<details>
  <summary>[Click this text for advanced vim shortcuts.]</summary>
To avoid using the arrow keys after opening the file:

* Type: `gg` (this goes to the top of the file)
* Type: `VG` (capital V, then capital G - this selects everything)
* Type: `y` (this copies the selected text)
</details>

### Step 7: Create your final program file
- Go back to the main directory: `cd ..` (make sure that your prompt now shows `:~/AI_1020_LAB_1$` rather than `:~/AI_1020_LAB_1/part1`)
- Create and open your final file: `vim final.c`
- Paste the headers:
  * Press: `i` (to go into Insert Mode; this lets you edit the file)
  * Press: `ESC` and `p` (short for paste) 
  * You should see the header content appear!
- Save and exit:
  * Press `ESC` (to exit Insert Mode and enter "Normal Mode")
  * Type: `:wq` and press Enter (w=write/save, q=quit)

### Step 8: Check your work
- Type: `cat final.c`
- You should see your headers displayed!

---

## PART 2: Search and Find (part2/ folder)

**The Crime:** Someone has stolen the next section of your code! You have 4 suspects, each with a file containing code. You need to find which suspect has YOUR pattern data. Specifically, you're searching for a 6x7 matrix called 'pattern'.

**Commands you'll learn:**

- `grep` - searches for text patterns in files (like a detective!)
- `cp` - copies files
- `*.c` - wildcard to match all .c files
- `../` - relative path meaning "parent directory"
- `>>` - appends output to end of file

### Step 9: Navigate to the crime scene
- Type: `cd part2`
- Type: `ls`
- You should see 4 suspect files and 1 unrelated file: `suspect1.c`, `suspect2.c`, `suspect3.c`, `suspect4.c`, `old_code.txt`

### Step 10: Search for your stolen code
- You're looking for the definition of the variable called "pattern"
- Type: `grep pattern *.c`
- This searches all suspect files for your stolen pattern data
  * `grep` outputs one line per match, where the format is `file_name:matching_line`.
- Which suspect has your code?!

### Step 11: Examine the evidence
- Type: `cat suspectX.c` (replace X with the guilty suspect number)
- Verify this contains a complete definition of the pattern array

### Step 12: Recover your stolen code
- Type: `cp suspectX.c ../recovered_pattern.c`
  * The `..` means "go up one directory level"
- This recovers your code and gives it a proper name
- Return to headquarters: `cd ..`
- Confirm recovery: `ls` (you should see `recovered_pattern.c`)

### Step 13: Understanding the path
- `../recovered_patten.c` is a "relative path" 
- It means: go up one directory (`..`) then create `recovered_pattern.c`
- Alternative: you could use the full path from root (`/`; what's printed by `pwd`), but relative is shorter!

### Step 14: Add the recovered code to your final program
- Copy and pasting between files with vim was somewhat slow, but there's a faster way!
- Any command that outputs text by default sends that text to your terminal. However, you can _redirect_ the text to a file rather than your terminal by adding `> some_file_name` after your command.
- If you want the text _appended_ to the file (rather than replacing it) you add `>> file_to_append_to` (note the extra `>`).
- Run: `cat recovered_pattern.c >> final.c`
  *  Since running `cat recovered_pattern.c` prints all the text in a file, we redirect that output and append it to `final.c`.

### Step 15: Check your progress
- Type: `vim final.c` and use the arrow keys to move around (try FN+Down or FN+Up to scroll faster)
- You should now see both headers and pattern data!
- Exit vim: Press Esc (to ensure you're in normal mode) then `:q`

---

## PART 3: Assembly (part3/ folder)

**Commands you'll learn:**

- `cat` (with multiple arguments)
- `gcc` - the C compiler
- `./` - runs a program in current directory

### Step 16: Navigate to the assembly folder
- Type: `cd part3`
- Type: `ls`
- You should see two .c files with the remaining code sections

### Step 17: Combine files using cat
- We'll add both files to your existing final.c in one command
- Type: `cat functions.c main.c >> ../final.c`
- `cat` prints the contents of every file passed as an argument (in order)

### Step 18: Check your complete program
- Go back to main directory: `cd ..`
- Look at your finished program: `cat final.c`
- It should now have headers, pattern data, functions, and main section!

### Step 19: Compile and run your creation
- Compile it: `gcc final.c -o final -lm`
  * `gcc` = the C compiler
  * `final.c` = your source code file
  * `-o final` = output an executable named "final"
  * `-lm` = link the math library (needed for sin, cos functions)
- Run it: `./final`
  * `./` means "run the program in this directory"
- Press `Ctrl+C` to stop when you're done admiring your work

**Congratulations!** You've practiced terminal navigation, vim basics, grep searching, and file copying!

## PART 4: Submission
Your final program, when run, will print an alphanumeric "submission ID".
Login to [Moodle](https://lms.mbzuai.ac.ae) open the lecture section of AI 1020 (__not__ the lab section), open the "Lab 1 Submission" assignment at the bottom of the home page, and paste in the submission ID from your program.

Had trouble finishing the lab?
This page will remain up, and you can submit until the end of today.
Still having trouble? Don't worry!
Come by office hours, and we can help you.
We want to make sure everyone is able to complete this lab---you'll need these skills for Assignment 1.
(This lab is zero credit, but may be factored into your participation grade.)

## PART 5: Bonus Challenge (Optional)

Using only the shortcuts and tools practiced in this lab, how could you assemble `final.c` in the command line with as little typing as possible (_i.e._, fewer commands, and/or less characters in each command)?

If we have time, we'll call you up and you can show off your alternate solutions to the class!
If we don't have time, write up a brief explanation of your solution and email it to me---I'll put together an email with your explanations for the class.
