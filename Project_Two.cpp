//============================================================================
// Name        : CoursePlanner.cpp
// Author      : Michael Geske
// Description : CS 300 Project Two - Course Planner
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Struct for storing course information
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// Convert string to uppercase for case-insensitive comparison
string ToUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// Display a single course with its prerequisites
void DisplayCourse(const Course& course) {
    cout << course.courseNumber << ", " << course.courseName << endl;
    if (!course.prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

// Load course data from CSV file
vector<Course> LoadCoursesFromCSV(const string& filename) {
    vector<Course> courses;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return courses;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course course;

        getline(ss, course.courseNumber, ',');
        getline(ss, course.courseName, ',');

        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        courses.push_back(course);
    }

    file.close();
    cout << "Courses successfully loaded!" << endl;
    return courses;
}

// Print course list in alphanumeric order
void PrintCourseList(const vector<Course>& courses) {
    vector<Course> sortedCourses = courses;

    sort(sortedCourses.begin(), sortedCourses.end(),
        [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
        });

    cout << "\nHere is a sample schedule:\n" << endl;
    for (const Course& course : sortedCourses) {
        cout << course.courseNumber << ", " << course.courseName << endl;
    }
}

// Find and print a specific course
void FindAndPrintCourse(const vector<Course>& courses, const string& courseNum) {
    string upperNum = ToUpper(courseNum);
    for (const Course& course : courses) {
        if (ToUpper(course.courseNumber) == upperNum) {
            cout << endl;
            DisplayCourse(course);
            return;
        }
    }
    cout << "Course not found." << endl;
}

// Main menu interface
int main() {
    vector<Course> courses;
    string input;
    int choice = 0;

    while (choice != 9) {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;

        cout << "\nWhat would you like to do? ";
        cin >> input;

        try {
            choice = stoi(input);
        }
        catch (...) {
            choice = 0;
        }

        switch (choice) {
        case 1:
            courses = LoadCoursesFromCSV("ABCU_Input.csv");
            break;
        case 2:

            if (courses.empty()) {
                cout << "Please load data first." << endl;
            }
            else {
                PrintCourseList(courses);
            }
            break;
        case 3:
            if (courses.empty()) {
                cout << "Please load data first." << endl;
            }
            else {
                cout << "What course do you want to know about? ";
                cin >> input;
                FindAndPrintCourse(courses, input);
            }
            break;
        case 9:
            cout << "\nThank you for using the course planner!" << endl;
            break;
        default:
            cout << "\n" << input << " is not a valid option." << endl;
        }
    }

    return 0;
}