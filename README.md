[![C++ doctest](https://github.com/Zakariarahman07/ITCS-2550-Week-2-Programming-Assignment/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/Zakariarahman07/ITCS-2550-Week-2-Programming-Assignment/actions/workflows/c-cpp.yml)

# Math Aptitude Analyzer

## Description

The **Math Aptitude Analyzer** is a C++ console application that evaluates a user's math skills and provides feedback to help improve them. The program collects user information, performs calculations, runs a math quiz, and generates formatted report files.

This project was created for **ITCS 2550 (C++ Programming 2)** and demonstrates core C++ programming concepts.

---

## Features

* Friendly welcome banner with console colors
* User input collection with validation
* Calculates estimated problems solved per hour
* 5-question math quiz with difficulty levels (Easy, Medium, Hard)
* Instant quiz feedback based on confidence level
* Stores quiz scores in arrays and calculates averages
* Student report card builder using a class and array of objects
* Writes formatted output to text files

---

## C++ Concepts Demonstrated

* **Selection Statements**: `if / else`, `switch-case`
* **Loops**: `for`, `while`, `do...while`
* **Functions**: value-returning and void functions
* **Arrays**: storing test scores and student objects
* **Structs**: `LearnerProfile` for user data
* **Enumerations**: quiz difficulty levels
* **Classes & Objects**: `Student` class with constructors and member functions
* **File Handling**: writing data to `.txt` files using `ofstream`

---

## How to Run the Program

1. Open **Visual Studio** or **VS Code**
2. Make sure a C++ compiler is installed
3. Compile and run `main.cpp`
4. Follow the on-screen prompts
5. View generated output files:

   * `report.txt`
   * `StudentsReportCard.txt`

---

## Example Interaction

```text
Welcome to the Math Aptitude Analyzer! Sharpen your Math skills and discover your true potential!

Enter your full name: John Doe
Enter your favorite Math Subject: Algebra
Enter the number of Math Problems Solved Per Week: 15
On a scale of 1 to 10, how confident are you in Math: 8
Enter number of hours studying Math per week: 5

Please Complete the Following Five Questions Math Quiz:

Enter difficulty level for the quiz (E for Easy, M for Medium or H for Hard): E

Enter a math operator (+, -, *, /, %): +
5 + 3 = 8
Correct! Well Done!

Your Favorite Subjects are:
Algebra Geometry Trigonometry
```

---

## Student Report Card Interaction

```text
----- Building Report Card For Students -----

Enter the number of students you want to build the report card for: 2

Enter student 1's Information:
Last name: Smith
ID number: 12345
Grade (A, B, C, D, E): A
Last test score: 95

Enter student 2's Information:
Last name: Johnson
ID number: 67890
Grade (A, B, C, D, E): B
Last test score: 85

------ Student Report Card -----
Last Name       ID             Grade   Score
Smith           12345          A       95
Johnson         67890          B       85
```

---

## Output Files

### report.txt

* User name
* Favorite math subject
* Confidence level
* Study hours
* Estimated problems solved per hour
* Test scores and average

### StudentsReportCard.txt

* Student last name
* ID number
* Grade
* Test score
* Automated feedback

---

## Notes

* Input validation is included to prevent invalid data entry
* If invalid input is entered, the user is prompted again
* Console color output may vary depending on the terminal used

---
**Author:** Zakaria Rahman
**Course:** ITCS 2550 – C++ Programming 2
