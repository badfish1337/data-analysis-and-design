/**
 * Christopher Dewey
 * April 16, 2022
 * SNHU CS 300
 * Module Seven
 * Project Two
 *
 *      ******************
 *      *  Main Program  *
 *      ******************
 *
 */


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <string>
#include <limits>
#include "Course.h"
#include "BinarySearchTree.h"
using namespace std;

/**
 *  Global Definitions & Signatures
 */
static void loadCourseData(const string& path);
static string selectCourse();
static string selectFilePath();
static inline string format(string str);
const string PATH = R"(C:\Users\chris\Desktop\ProjectTwo\ABCUCatalog.txt)";
BinarySearchTree BST{};


/**
 *  Main
 *  Contains Menu and initialization
 */
int main() {

    // Run Main Menu
    bool run = true;
    while(run) {
        // Print Main Menu
        cout << "\nMain Menu:" << endl;
        cout << "\t[1] - Load Course Data\n" <<
             "\t[2] - Print Course List\n" <<
             "\t[3] - Print Courses with Prerequisites\n" <<
             "\t[4] - Print One Course with Prerequisites\n" <<
             "\t[Q] - Quit" << endl;
        cout << "Please make a selection:";

        // Process Selection
        string selection;
        getline(cin, selection);

        // Remove whitespace and convert to uppercase
        selection = format(selection);

        // Add space to console for easier viewing
        cout << endl;

        // Run Selection
        switch (selection.at(0)) {
            // Load Course Data
            case '1':
                loadCourseData(selectFilePath());
                break;

            // Print Course List
            case '2':
                BST.printCourseList();
                break;

            // Print Courses with Prerequisites
            case '3':
                BST.printCourses();
                break;

            // Print One Course with Prerequisites
            case '4':

                BST.printCourse(selectCourse());
                break;

            // Quit
            case 'Q':
                cout << "Thank you for using ABCU's Course Catalog!\nGood bye!" << endl;
                // Stop while loop; end program
                run = false;
                break;

                // Error handling
            default:
                cout << "[ERROR] Invalid entry. Please try again." << endl;
        }
    }
    return 0;
}

// Allow user to choose between default file path or entering a custom one
static string selectFilePath(){
    // Print submenu
    cout << "How do you want to load courses?" << endl;
    cout << "[1] - Enter a file path\n"
         << "[2] - Use default path" << endl;
    cout << "Please make a selection:" << endl;

    // Get selection
    string selection;
    getline(cin, selection);

    // Process selection - Any choice other than '1' results in default course data loaded
    if (selection.at(0) == '1') {
        cout << "Please enter the file path for course data:";

        // Get and return file path
        string filePath;
        cin >> filePath;
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        return filePath;
    } else {
        // Return default file path
        return PATH;
    }
}

// Read from file, parse lines, and extract information for insertion into Binary Search Tree data structure
void loadCourseData(const string& path) {

    // Vectors to temporarily hold course data from file
    vector<vector<string>> courseData;
    vector<string> courseList;

    // Count number of courses successfully loaded
    int numInserted = 0;

    // Create filestream and connect to path
    ifstream inFile(path);

    // Check for errors
    if (!inFile.good()) {
        cout << "[ERROR] File could not be read. Aborted Loading Courses!" << endl;
        return;
    }

    // Read from file and populate temporary vectors
    while (!inFile.eof()) {

        // Hold course components
        vector<string> tempCourse;
        string currentLine;
        getline(inFile, currentLine);

        // Create string stream to read currentLine
        stringstream lineStream(currentLine);


        // Until end of line
        while (lineStream.good()) {
            // Get course component (string) from line, stop at comma
            string tempString;
            getline(lineStream, tempString, ',');


            if (tempString.size() > 1) {
                // Add component to tempCourse
                tempCourse.push_back(tempString);
            }
        }

        // If tempCourse contains data
        if (!tempCourse.empty()) {
            // Courses must have a courseNumber and name
            // Validate contents and formatting
            if (tempCourse.size() < 2) {
                cout << "[ERROR] Invalid Course Format! Aborted Loading Courses!" << endl;
                return;
            }

            // Add courseNumber to courseList and all course data to courseData
            courseData.push_back(tempCourse);
            courseList.push_back(tempCourse.at(0));
        }
    }

    // Check for validity and add prerequisites
    for (vector<string> current : courseData) {
        // Create a vector to store prerequisites exclusive of other course data
        vector<string> prerequisites;

        // If prerequisites exist
        if (current.size() > 2) {
            // Iterate through prerequisites (skip courseNumber and name)
            for (size_t i = 2; i < current.size(); i++) {

                // Validate prerequisites
                string currentPrerequisite = current.at(i);
                bool isInCourseList = false;
                // For each prerequisite, if the course is offered, set isInCourseList (flag) to true
                for (const string& courseNumber : courseList) {
                    if (courseNumber == currentPrerequisite){
                        isInCourseList = true;
                    }
                }

                // Return error if a prerequisite is not offered at the university
                if (!isInCourseList) {
                    cout << "\n[ERROR] Course prerequisites not in course list!" << endl;
                    return;
                }

                // Add prerequisite
                prerequisites.push_back(current.at(i));
            }
        }

        // Create a new valid course with formatted data
        Course newCourse(current.at(0), current.at(1), prerequisites);
        // Insert course into the binary search tree
        BST.insertCourse(newCourse);

        // Increment numInserted
        numInserted++;
    }

    // Print success message
    cout << "[SUCCESS] Loaded " << numInserted << " courses." << endl;
}

// Allow user to select a course (used in BinarySearchTree::printCourse method)
static string selectCourse(){

    // Request and return a courseNumber
    cout << "Please enter a course:";
    string searchId;
    getline(cin, searchId);

    // Format entry to remove whitespace and convert to uppercase
    searchId = format(searchId);
    return searchId;
}

/**
 * Remove whitespace characters and convert to uppercase
 * @param str
 * @return formatted string
 */
static inline string format(string str) {
    string newString = str;

    // Regex to remove spaces from newString
    newString.erase(remove_if(newString.begin(), newString.end(), ::isspace), newString.end());

    // Lambda to convert to char array, iterate, and convert newString to uppercase
    for_each(newString.begin(), newString.end(), [](char &c) {
        c = ::toupper(c);
    });

    return newString;
}

