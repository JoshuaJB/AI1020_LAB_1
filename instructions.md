
# Lab 1: Terminal and Vim Basics

Welcome to your AI1020 lab! Today you'll learn to navigate the command line and use basic text editing tools. By the end, you'll have assembled a program that creates a 3D animated molecule - and it will congratulate you personally!

**What you'll learn:**
- Basic terminal navigation
- File searching and copying
- Text editing with vim

---

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
- When you're ready to leave: Press `ESC`, then type `:q` and press Enter

### Step 6: Copy the headers to your final program
- Make sure you're in the part1 folder (type `pwd` to check)
- Type: `vim headers.c`
- Select all the content:
  * Press `ESC` to make sure you're not in edit mode
  * Type: `gg` (this goes to the top of the file)
  * Type: `VG` (capital V, then capital G - this selects everything)
  * Type: `y` (this copies the selected text)
- Exit this file: Press `ESC`, then type `:q` and press Enter

### Step 7: Create your final program file
- Go back to the main directory: `cd ..`
- Create and open your final file: `vim final.c`
- Paste the headers:
  * Press: `i` (this lets you edit the file)
  * Press: `esc` and `p` 
  * You should see the header content appear!
- Save and exit:
  * Press `ESC`
  * Type: `:wq` and press Enter (w=write/save, q=quit)

### Step 8: Check your work
- Type: `cat final.c`
- You should see your headers displayed!

---

## PART 2: Search and Find (part2/ folder)

**The Crime:** Someone has stolen the next section of your code! You have 4 suspects, each with a file containing code. You need to find which suspect has YOUR pattern data. Specifically, your searching for a 6x7 matrix called 'pattern'.

**Commands you'll learn:**
- `grep` - searches for text patterns in files (like a detective!)
- `cp` - copies files
- `*.c` - wildcard to match all .c files

### Step 9: Navigate to the crime scene
- Type: `cd part2`
- Type: `ls`
- You should see 4 suspect files: suspect1.c, suspect2.c, suspect3.c, suspect4.c

### Step 10: Search for your stolen code
- You're looking for the pattern data (contains "pattern[")
- Type: `grep "pattern\[" *.c`
- This searches all suspect files for your stolen pattern data
- Which suspect has your code?!

### Step 11: Examine the evidence
- Type: `cat suspect[X].c` (replace [X] with the guilty suspect number)
- Verify this contains your pattern array data

### Step 12: Recover your stolen code
- Type: `cp suspect[X].c ../recovered_pattern.c`
- This recovers your code and gives it a proper name
- Return to headquarters: `cd ..`
- Confirm recovery: `ls` (you should see recovered_pattern.c)

### Step 13: Add the recovered code to your final program
- Type: `vim recovered_pattern.c`
- Copy all content: `ESC`, then `gg`, then `VG`, then `y`
- Exit: `ESC`, then `:q`
- Open your final file: `vim final.c`
- Go to the end: `ESC`, then `G`
- Start a new line: press `o`
- Paste the recovered data: `ESC` `p`
- Save and exit: `ESC`, then `:wq`

### Step 14: Check your progress
- Type: `cat final.c`
- You should now see both headers and pattern data!

---

## PART 3: Assembly (part3/ folder)

**Commands you'll learn:**
- `>>` - appends output to end of file
- `../` - relative path meaning "parent directory"
- `gcc` - the C compiler
- `./` - runs a program in current directory

### Step 15: Navigate to the assembly folder
- Type: `cd part3`
- Type: `ls`
- You should see two .c files with the remaining code sections

### Step 16: Combine files using cat
- We'll add both files to your existing final.c in one command
- Type: `cat functions.c main.c >> ../final.c`
- The `>>` means "append to the end of the file"
- The `..` means "go up one directory level"

### Step 17: Understanding the path
- `../final.c` is a "relative path" 
- It means: go up one directory (..) then find final.c
- Alternative: you could use the full path from root, but relative is shorter!

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

**Congratulations!** You've learned terminal navigation, vim basics, grep searching, file copying, and efficient assembly!
