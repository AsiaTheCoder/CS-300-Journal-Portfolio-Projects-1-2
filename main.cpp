#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <limits>

// Class to represent Course objects
class Course {
public:
    std::string courseNumber;
    std::string courseName;
    std::vector<std::string> prerequisites;

    // Constructors
    Course() {}
    Course(std::string number, std::string name, std::vector<std::string> prereqs)
            : courseNumber(number), courseName(name), prerequisites(prereqs) {}
};

// Function to read course data from a file into a vector
void readCourseData(std::vector<Course> &courses, const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Error opening file.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            std::cout << "Error: Invalid line format.\n";
            continue;
        }

        std::string courseNumber = tokens[0];
        std::string courseName = tokens[1];
        std::vector<std::string> prerequisites(tokens.begin() + 2, tokens.end());

        Course newCourse(courseNumber, courseName, prerequisites);
        courses.push_back(newCourse);
    }

    file.close();
}

// Function to print a list of all courses
void printCourseList(const std::vector<Course> &courses) {
    for (const auto &course : courses) {
        std::cout << course.courseNumber << " - " << course.courseName << "\n";
    }
}

// Function to print information about a specific course
void printCourseInfo(const std::vector<Course> &courses, const std::string &courseNumber) {
    for (const auto &course : courses) {
        if (course.courseNumber == courseNumber) {
            std::cout << "Course Number: " << course.courseNumber << "\n";
            std::cout << "Course Name: " << course.courseName << "\n";
            std::cout << "Prerequisites: ";
            for (const auto &prerequisite : course.prerequisites) {
                std::cout << prerequisite << " ";
            }
            std::cout << "\n";
            return;
        }
    }
    std::cout << "Course not found.\n";
}

// Main function
int main() {
    std::vector<Course> courses;  // Vector to hold course objects
    std::string fileName = "C:\\Users\\Asiam\\Documents\\College\\CS 300 Data Structures and Algorithm\\Project Two\\CS 300 - Module  7 Project 2\\course_data.txt";  // Hardcoded file name
    int choice;  // User choice for menu

    // Main menu loop
    while (true) {
        std::cout << "Menu:\n";
        std::cout << "1. Load Data Structure\n";
        std::cout << "2. Print Course List\n";
        std::cout << "3. Print Course\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Clear the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                courses.clear();  // Clear the existing vector
                readCourseData(courses, fileName);  // Using the hardcoded file name

                // Sort courses in alphanumeric order
                std::sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
                    return a.courseNumber < b.courseNumber;
                });
                break;
            }

            case 2: {
                printCourseList(courses);
                break;
            }
            case 3: {
                std::string courseNumber;
                std::cout << "Enter the course number: ";
                std::cin >> courseNumber;
                printCourseInfo(courses, courseNumber);
                break;
            }
            case 4: {
                return 0;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                std::cin.clear();  // Clear the error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore remaining characters
            }
        }
    }
    return 0;
}

