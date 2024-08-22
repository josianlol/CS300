#include <iostream>   // Required for input/output operations
#include <fstream>    // Required for file operations
#include <sstream>    // Required for string stream operations
#include <vector>     // Required for using vectors
#include <string>     // Required for using strings
#include <algorithm>  // Required for sorting

using namespace std;

// Structure to represent a course
struct Course {
    string courseNumber;          // The unique course number (e.g., CSCI100)
    string name;                  // The name of the course (e.g., Introduction to Computer Science)
    vector<string> prerequisites; // A list of prerequisite course numbers
};

// Function to prompt the user for the file name and load courses from that file into a vector of Course structures
vector<Course> loadCourses() {
    string csvPath;  // Variable to hold the file path entered by the user
    cout << "Enter the path to the CSV file (including the .csv extension): ";
    getline(cin, csvPath);  // Use getline to capture the entire path, including spaces if any

    cout << "Attempting to open file: " << csvPath << endl;  // Debugging output to show the file path being opened

    vector<Course> courses;       // Vector to store the loaded courses
    ifstream file(csvPath);       // Open the CSV file for reading

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cout << "Error: Could not open file " << csvPath << endl;
        return courses;           // Return an empty vector if the file cannot be opened
    }

    string line;  // Variable to hold each line of the CSV file
    // Loop through each line in the file
    while (getline(file, line)) {
        stringstream ss(line);    // Create a string stream from the line
        string token;             // Variable to hold each part of the line
        Course course;            // Create a Course object

        // Read the course number and name from the line
        getline(ss, course.courseNumber, ',');
        getline(ss, course.name, ',');

        // Read any prerequisites from the line
        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token); // Add each prerequisite to the vector
        }

        courses.push_back(course);  // Add the course to the vector of courses
    }

    file.close();  // Close the file after reading all lines
    cout << "Successfully loaded " << courses.size() << " courses." << endl;
    return courses;  // Return the vector of loaded courses
}

// Function to print the information of a specific course
void printCourseInfo(const Course& course) {
    cout << course.courseNumber << ", " << course.name << endl;
    // Check if the course has prerequisites
    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";
        // Loop through and print each prerequisite
        for (const auto& prereq : course.prerequisites) {
            cout << prereq << " ";
        }
        cout << endl;
    }
}

// Function to print all courses in alphanumeric order
void printAllCourses(const vector<Course>& courses) {
    vector<Course> sortedCourses = courses;  // Create a copy of the courses vector for sorting
    // Sort courses by course number
    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    // Loop through and print each course
    for (const auto& course : sortedCourses) {
        cout << course.courseNumber << ", " << course.name << endl;
    }
}

// Function to search for a specific course by course number
Course* searchCourse(vector<Course>& courses, const string& courseNumber) {
    // Loop through the courses to find a match
    for (auto& course : courses) {
        if (course.courseNumber == courseNumber) {
            return &course;  // Return a pointer to the course if found
        }
    }
    return nullptr;  // Return nullptr if the course is not found
}

// Function to display the menu options to the user
void displayMenu() {
    cout << "\nMenu Options:" << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

// Function to handle the user's menu selection
void handleMenuSelection(int choice, vector<Course>& courses) {
    switch (choice) {
    case 1: {
        courses = loadCourses();  // Load course data from the CSV file
        break;
    }
    case 2:
        // Print all courses in sorted order
        if (courses.empty()) {
            cout << "Error: No data loaded." << endl;
        }
        else {
            cout << "\nHere is a sample schedule:\n";
            printAllCourses(courses);
        }
        break;
    case 3: {
        // Print information for a specific course
        if (courses.empty()) {
            cout << "Error: No data loaded." << endl;
        }
        else {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;

            // Clear the input buffer before reading a new line to avoid issues.
            cin.ignore();

            Course* course = searchCourse(courses, courseNumber);
            if (course != nullptr) {
                printCourseInfo(*course);
            }
            else {
                cout << "Course " << courseNumber << " not found." << endl;
            }
        }
        break;
    }
    case 9:
        // Exit the program
        cout << "Thank you for using the course planner!" << endl;
        break;
    default:
        // Handle invalid menu options
        cout << choice << " is not a valid option." << endl;
        break;
    }
}

// Main function to run the program
int main(int argc, char* argv[]) {
    vector<Course> courses;  // Vector to store the courses

    int choice = 0;  // Variable to store the user's menu choice
    string input;  // String to handle menu input
    cout << "Welcome to the course planner.\n";
    // Loop until the user chooses to exit
    while (choice != 9) {
        displayMenu();  // Display the menu options
        getline(cin, input);  // Use getline to handle input

        try {
            choice = stoi(input);  // Convert string input to integer
        }
        catch (invalid_argument& e) {
            cout << "Invalid input. Please enter a number." << endl;
            continue;  // Prompt the menu again if input is invalid
        }

        handleMenuSelection(choice, courses);  // Process the user's choice
    }

    return 0;  // Return 0 to indicate successful completion
}
