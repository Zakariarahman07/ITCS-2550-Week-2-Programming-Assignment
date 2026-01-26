/*
Author: Zakaria Rahman
Date: January 18, 2026
Description: This program collects user inputs and validates if they enter the correct input.
             Also, it demonstrates file handling by writing to a file. Additionally, it shows the usage 
             of selection statements like if else statements and switch case statements. Furthermore, 
             it also demonstrates the use of repetition structures such as the for loop, do...while loop,
             and while loop, and use of user defined functions. It also demonstrates the use of Arrays and Enumerations.
             This program also shows the useage of data structures like struct. 
             Finally, it incorporates object-oriented programming concepts including classes and objects.
Course: ITCS 2550 (C++ Programming 2)
*/


// header files
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;

// Class Definition
class Student {
    // Private Member Variables
    private:
        string studentLastName;
        string studentID;
        char studentGrade;
        int studentTestScore;
    
    public:
        // Default Constructor
        Student() {
            studentLastName = " ";
            studentID = " ";
            studentGrade = ' ';
            studentTestScore = 0;
        }
        // Constructor with Parameter
        Student(string lastName, string id, char grade, int testScore) {
            studentLastName = lastName;
            studentID = id;
            studentGrade = grade;
            studentTestScore = testScore;
        }

        // Member Functions Prototype
        void setStudentInfo(string lastName, string id, char grade, int testScore);
        string getFeedback() const;
        void printStudentInfo() const;
        void writeStudentInfo(ofstream& out) const;
};


// Enumeration Declaration
enum difficultyLevel { EASY = 'E', MEDIUM = 'M', HARD = 'H'};

// Struct Definition (Global Scope)
struct LearnerProfile {
    string name;
    string favoriteMathSubject;
    int problemsSolvedPerWeek;
    int confidenceLevel;
    double hoursSpentStudyingPerWeek;
};


// Declaring a constant for number of questions asked on the quiz
const int NO_OF_QUESTIONS = 5;
// Some Color Codes as Constants
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string RESET = "\033[0m";

// Constants for array size
const int NUMBER_OF_TEST_SCORES = 5;

// Function prototypes

void changeConsoleTextColor(string color);

void displayWelcomeBanner();

void collectUserInfo(LearnerProfile& learner);

double calculateEstimatedProblemsPerHour(LearnerProfile& learner);

void userInputReportFile(ofstream& userOutputFile, LearnerProfile& learner, double& estimatedProblemsPerHour, double testScores[], double& averageTestScores);

double averageTestScores(double testScorees[], int size);

void mathQuiz(int& noOfCorrectAnswers, char quizDifficultyLevel);

void quizFeedback(int& confidenceLevel, int& noOfCorrectAnswers);

void displayStudentFavoriteSubjects(string favoriteSubjects[], const int NUMBER_OF_FAVORITE_SUBJECTS);

// Helper Function for Unit Testing for ENUM Decision Logic
int getMaxRandomNumberForDifficulty(char difficultyLevel)
{
    switch(difficultyLevel) {
        case EASY:
            return 10;
        case MEDIUM:
            return 100;
        case HARD:
            return 1000;
        default:
            return 10; // For invalid input/guard case
    }
}
// For Unit Testing
#ifdef _DEBUG
    #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
    #include "doctest.h"

    TEST_CASE("Class Method Testing")
    {
        Student testStudent1;
        testStudent1.setStudentInfo("Rahman", "121121", 'A', 80);
        CHECK(testStudent1.getFeedback() == "Excellent work! Keep up the high performance.");

        Student testStudent2;
        testStudent2.setStudentInfo("Doe", "222321", 'F', 0);
        CHECK(testStudent2.getFeedback() == "Needs improvement. Consider extra practice and studying.");

    }

    TEST_CASE("Calculation Testing")
    {
        LearnerProfile testLearner1{"Alice", "Calculus", 50, 8, 10.0};
        CHECK(calculateEstimatedProblemsPerHour(testLearner1) == 5.0);

        LearnerProfile testLearner2{"Bob", "Geometry", 6, 6, 1.0};
        CHECK(calculateEstimatedProblemsPerHour(testLearner2) == 6.0);

        LearnerProfile testLearner3{"John", "Algebra", 12, 10, -5.0}; // Invalid hours
        CHECK(calculateEstimatedProblemsPerHour(testLearner3) == 12.0);

        LearnerProfile testLearner4{"Kiki", "Statistics", 18, 6, 0.0}; // Zero Division
        CHECK(calculateEstimatedProblemsPerHour(testLearner4) == 18.00);
    }

    TEST_CASE("Enum Decision Logic Testing")
    {
        CHECK(getMaxRandomNumberForDifficulty('E') == 10);
        CHECK(getMaxRandomNumberForDifficulty('M') == 100);
        CHECK(getMaxRandomNumberForDifficulty('H') == 1000);
        CHECK(getMaxRandomNumberForDifficulty('X') == 10);
    }
    TEST_CASE("Array Processing Testting")
    {
        double testScores1[3] = { 90.0, 80.0, 70.0};
        CHECK(averageTestScores(testScores1, 3) == doctest::Approx(80.0));

        double testScores2[5] = { 0.0, 0.0, 0.0, 0.0, 0.0};
        CHECK(averageTestScores(testScores2, 5) == doctest::Approx(0.0));

        double testScores3[2] = { 100.0, 100.0};
        CHECK(averageTestScores(testScores3, 2) == doctest::Approx(100.0));
    }
#endif

#ifndef _DEBUG
int main(){
    
    // Calling the function which displays a welcome banner to the user
    displayWelcomeBanner();

    // Declaring some variables
    LearnerProfile userData;
    double userEstimatedProblemsPerHour = 0.0;

    
    // Calling the 'Collect User Info' function to get the user's input
    collectUserInfo(userData);

    // Calling the function to calculate the user's estimated time solving each problem
    userEstimatedProblemsPerHour = calculateEstimatedProblemsPerHour(userData);

    // Using an array to store user's last five test scores
    double userTestScores[NUMBER_OF_TEST_SCORES];

    cout << userData.name << ", please enter your last five " << userData.favoriteMathSubject << "'s test scores: " << endl << endl;
    for (int i = 0; i < NUMBER_OF_TEST_SCORES; i++) {
        // Input Validation for each score using a do...while loop
        double score;
        bool isValid = false;
        do {
            cout << "Test Score " << i + 1 << ": ";
            if (cin >> score && score >= 0.0 && score <= 100.0) {
                userTestScores[i] = score;
                isValid = true;
            } else {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Test Score. Please Enter a score between 0 to 100.\n";
            }
        } while(!isValid);
    }
    cout << endl;
    // Calculating and displaying the average test score
    double totalScores = 0.0;
    double userAverageTestScore = 0.0;
    for (int i = 0; i < NUMBER_OF_TEST_SCORES; i++) {
        totalScores += userTestScores[i];
    }
    userAverageTestScore = totalScores / NUMBER_OF_TEST_SCORES;
    cout << fixed << showpoint << setprecision(2);
    cout << userData.name << ", your average test score in " << userData.favoriteMathSubject << " is: " << userAverageTestScore << endl << endl;


    // File Handling
    ofstream outputFile;

    // Calling the Function for saving the user info to a separate text file
    userInputReportFile(outputFile, userData, userEstimatedProblemsPerHour, userTestScores, userAverageTestScore);

    // Calling the function to insert and display user's favorite subjects using an array
    const int NUMBER_OF_FAVORITE_SUBJECTS = 3;
    string userFavoriteSubjects[NUMBER_OF_FAVORITE_SUBJECTS];
    displayStudentFavoriteSubjects(userFavoriteSubjects, NUMBER_OF_FAVORITE_SUBJECTS);

    // Math Quiz
    cout << "Please Complete the Following Five Quesitions Math Quiz: \n" << endl;


    // Seeding the random number generator once
    srand(time(0));

    // Variable Declaration
    int numberOfCorrectAnswers = 0;

    // Using /a for loop for calling the mathQuiz functions
    char quizDifficultyLevel;
    cout << "Enter difficulty level for the quiz (E for Easy, M for Medium or H for Hard): ";
    cin >> quizDifficultyLevel;
    cout << endl;

    for (int i = 1; i <= NO_OF_QUESTIONS; i++){
        mathQuiz(numberOfCorrectAnswers, quizDifficultyLevel);
    }

    cout << endl;

    // Calling the quizFeedback function
    quizFeedback(userData.confidenceLevel, numberOfCorrectAnswers);

    // Building a report card for students from their teacher

    // Declaring Variables
    int numberOfStudents;
    string lastName;
    string id;
    char grade;
    int testScore;

    cout << "----- Building Report Card For Students -----" << endl << endl;

    cout << "Enter the number of students you want to build the report card for: ";
    cin >> numberOfStudents;
    cout << endl;

    // Creating an array of Student Objects
    Student studentList[numberOfStudents];

    // Setting the information for each student object
    for (int i = 0; i < numberOfStudents; i++) {
        cout << "Enter student " << i + 1 << "'s Information: " << endl << endl;
        cout << "Last name: ";
        cin >> lastName;
        cout << endl;

        cout << "ID number: ";
        cin >> id;
        cout << endl;

        cout << "Grade (A, B, C, D, E): ";
        cin >> grade;
        cout << endl;

        cout << "Last test score: ";
        cin >> testScore;
        cout << endl;

        studentList[i].setStudentInfo(lastName, id, grade, testScore);
        studentList[i].getFeedback();
    }

    cout << endl;

    // Printing out the information in console
    cout << "------ Student Report Card -----" << endl << endl;
    cout << left << setfill(' ') << setw(15) << "Last Name" << setw(15) << "ID" << setw(8) << "Grade" << setw(8) << "Score" << endl << endl;
    for (int i = 0; i < numberOfStudents; i++) {
        studentList[i].printStudentInfo();
        cout << endl;
    }

    // Writing it to a txt file
    ofstream reportFile("StudentsReportCard.txt");

    for (int i = 0; i < numberOfStudents; i++) {
        studentList[i].writeStudentInfo(reportFile);
    }

    reportFile.close();
    
    return 0;
}
#endif


// Function that change the console's text color
// Credit to AI and YouTube Videos
void changeConsoleTextColor(string color) {
    cout << color;
}

// Function that displays the welcome banner to the user
void displayWelcomeBanner(){
    // calling the function to change the color of the console's text
    changeConsoleTextColor(YELLOW);

    // Welcome Message
    cout << left << setfill('-') << setw(100) << "" << endl << endl;
    cout << "Welcome to the Math Aptitude Analyzer! Sharpen your Math skills and discover your true potential!" << endl << endl;
    cout << "Get ready to challenge yourself and see how strong your math skills really are!" << endl << endl;
    cout << "Please enter the following information as prompted. Thank you!" << endl << endl;
    cout << left << setfill('-') << setw(100) << "" << endl << endl;

    // Changing the color back to default
    changeConsoleTextColor(RESET);
}

// Function that collects and validates the data from the user
void collectUserInfo(LearnerProfile& learner) 
{
    // Prompts the user for inputs

    cout << "Enter your full name: ";
    getline(cin, learner.name);
    cout << endl;

    cout << "Enter your favorite Math Subject: ";
    getline(cin, learner.favoriteMathSubject);
    cout << endl;

    // Input Validation using while loop

    cout << "Enter the number of Math Problems Solved Per Week: ";

    while (!(cin >> learner.problemsSolvedPerWeek)){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid Input. Please enter a whole number: " << endl;
    }
    cout << endl;

    cout << "On a scale of 1 to 10, how confident are you in Math (1 being least and 10 being the most): ";

    while(!(cin >> learner.confidenceLevel) || learner.confidenceLevel < 1 || learner.confidenceLevel > 10){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid Input. Please enter a number between 1 - 10: ";
    }
    cout << endl;

    cout << "Enter number of hours studying Math per week: ";

    while (!(cin >> learner.hoursSpentStudyingPerWeek) || learner.hoursSpentStudyingPerWeek < 1 || learner.hoursSpentStudyingPerWeek > 168){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid Input. Please enter a number between 1 to 168: ";
    }
    cout << endl;

}

// Function for Calculation
double calculateEstimatedProblemsPerHour(LearnerProfile& learner){
    
    // despite user entering 0 hours or negative hours, for unit testing purpose, we handle it here to avoid division by zero or negative hours
    if (learner.hoursSpentStudyingPerWeek <=0){
        learner.hoursSpentStudyingPerWeek = 1; // setting it to 1 by default to avoid division by zero or negative hours
    }
    return static_cast<double> (learner.problemsSolvedPerWeek) / learner.hoursSpentStudyingPerWeek;
}

// Function for Writing User's Input to an Output txt file
void userInputReportFile(ofstream& userOutputFile, LearnerProfile& learner, double& estimatedProblemsPerHour, double testScores[], double& averageTestScores) {
    
    userOutputFile.open("report.txt");

    userOutputFile << fixed << showpoint << setprecision(2);

    userOutputFile << left << setfill(' ') << setw(50) << "Name:" << right << setw(20) << setfill(' ') << learner.name << endl;
    userOutputFile << left << setfill(' ') << setw(50) << "Favorite Math Subject:" << right << setw(20) << setfill(' ') << learner.favoriteMathSubject << endl;
    userOutputFile << left << setfill(' ') << setw(50) << "Confidence Level:" << right << setw(20) << setfill(' ') << learner.confidenceLevel << endl;
    userOutputFile << left << setfill(' ') << setw(50) << "# of Hours Studying Math:" << right << setw(20) << setfill(' ') << learner.hoursSpentStudyingPerWeek << endl;
    userOutputFile << left << setfill(' ') << setw(50) << "Estimated Problems Solved Per Hour:" << right << setw(20) << setfill(' ') << estimatedProblemsPerHour << endl;
    userOutputFile << left << setfill(' ') << setw(50) << "Test Scores-" << endl;
    for (int i = 0; i < NUMBER_OF_TEST_SCORES; i++) {
        userOutputFile << left << setfill(' ') << setw(50) << "Test Score " + to_string(i+1) + ": " << right << setw(20) << setfill(' ') << testScores[i] << endl;
    }
    userOutputFile << left << setfill(' ') << setw(50) << "Average Test Scores:" << right << setw(20) << setfill(' ') << averageTestScores << endl;


    userOutputFile.close();
}

// Function for asking the user some basic arithmetic problems
void mathQuiz(int& noOfCorrectAnswers, char quizDifficultyLevel) {
    int randomNum1, randomNum2;
    int result = 0;
    int userAnswer;
    char mathOperator;

    switch(quizDifficultyLevel) {
        case EASY:
            randomNum1 = (rand() % 10) + 1;
            randomNum2 = (rand() % 10) + 1;
            break;
        case MEDIUM:
            randomNum1 = (rand() % 100) + 1;
            randomNum2 = (rand() % 100) + 1;
            break;
        case HARD:
            randomNum1 = (rand() % 1000) + 1;
            randomNum2 = (rand() % 1000) + 1;
            break;
    }

    cout << "Enter a math operator (+, -, *, /, %): ";

    while (!(cin >> mathOperator) || (mathOperator != '+' && mathOperator != '-' && mathOperator != '*' && mathOperator != '/' && mathOperator != '%')){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid Input. Please Enter a correct Math Operator: ";
    }
        cout << endl;

        switch(mathOperator) {
            case '+':
            result = randomNum1 + randomNum2;
            break;
        case '-':
            result = randomNum1 - randomNum2;
            break;
        case '*':
            result =randomNum1 * randomNum2;
            break;
        case '/':
            result = randomNum1 / randomNum2;
            break;
        case '%':
            result = randomNum1 % randomNum2;
            break;
        }

    cout << randomNum1 << " " << mathOperator << " " << randomNum2 << " = ";
    cin >> userAnswer;
    cout << endl;

    if (userAnswer == result){
        // using the console text color function
        changeConsoleTextColor(GREEN);

        cout << "Correct! Well Done!" << endl;

        changeConsoleTextColor(RESET);
        noOfCorrectAnswers++;
    } else{
        changeConsoleTextColor(RED);
        cout << "Wrong Answer! The correct answer was: " << result << endl;
        changeConsoleTextColor(RESET);
    }
    cout << endl;
}


// Function for getting a feedback based on confidence level and quiz results
void quizFeedback(int& confidenceLevel, int& noOfCorrectAnswers) {
    cout << "----- Quiz Feedback -----\n" << endl;


    // Using if/else blocks with compound boolean conditions
    if (noOfCorrectAnswers >= 4 && confidenceLevel >= 7) {
        cout << "Great! Your confidence matches your performance." << endl;
        cout << "You can try more advance problems!" << endl;
    }
    else if (noOfCorrectAnswers >= 3 && confidenceLevel >= 5) {
        cout << "Good work! Keep on practicing to improve." << endl;
        cout << "Solving more problems increases your confidence level." << endl;
    }
    else if (noOfCorrectAnswers >= 3 && confidenceLevel < 5) {
        cout << "Your performance is okay, but your confidence is low." << endl;
        cout << "Focus on building your confidence through consistent practice." << endl;
    }
    else if (noOfCorrectAnswers < 3 && confidenceLevel >=5) {
        cout << "You feel confident, but your performance shows the opposite." << endl;
        cout << "Practice fundamental concepts to match your confidence level." << endl;
    }
    else{
        cout << "Focus on basic concepts and fundamentals of Math." << endl;
        cout << "Practice regularly to improve your skills and confidence level." << endl;
    }

    cout << endl;
}

// Function to insert and display user's favorite subjects
void displayStudentFavoriteSubjects(string favoriteSubjects[], const int NUMBER_OF_FAVORITE_SUBJECTS) {

    cout << "Enter Your Favorite Subjects: " << endl;
    for (int i = 0; i < NUMBER_OF_FAVORITE_SUBJECTS; i++){
        cin >> favoriteSubjects[i];
    }
    cout << endl;

    cout << "Your Favorite Subjects are- " << endl;
    for (int i = 0; i < NUMBER_OF_FAVORITE_SUBJECTS; i++) {
        changeConsoleTextColor(YELLOW);
        cout << favoriteSubjects[i] << " ";
    }
    cout << endl << endl;
    changeConsoleTextColor(RESET);
}

// Class Member Functions Definitions
void Student::setStudentInfo(string lastName, string id, char grade, int testScore){
    studentLastName = lastName;
    studentID = id;
    studentGrade = grade;
    studentTestScore = testScore;
}

string Student::getFeedback() const {
    if (studentGrade == 'A' || studentTestScore >= 90){
        return "Excellent work! Keep up the high performance.";
    }
    else if (studentGrade == 'B' || studentTestScore >= 80){
        return "Good job! You are doing well, but there is room for improvement.";
    }
    else if (studentGrade == 'C' || studentTestScore >= 70) {
        return "Fair performance. Focus on improving weaker areas.";
    }
    else {
        return "Needs improvement. Consider extra practice and studying.";
    }
}

void Student::printStudentInfo() const {
    changeConsoleTextColor(RED);
    cout << left << setfill(' ') << setw(15) << studentLastName << setw(15) << studentID << setw(8) << studentGrade << setw(8) << studentTestScore << endl;
    changeConsoleTextColor(RESET);
}

void Student::writeStudentInfo(ofstream& out) const {
    out << left << setw(15) << studentLastName << setw(15) << studentID << right << setw(5) << studentGrade << setw(8) << studentTestScore << right << setw(90) << getFeedback() << endl;

}

double averageTestScores(double testScores[], int size) {
    double total = 0.0;
    for (int i = 0; i < size; i++) {
        total += testScores[i];
    }
    return total / size;
}