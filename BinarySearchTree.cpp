/**
 *
 *   ******************************************
 *   *   BinarySearchTree Class Definitions   *
 *   ******************************************
 */

#include <iostream>
#include "BinarySearchTree.h"

/**
 * Insert Course Public Method
 * Calls private version
 * @param course
 */
void BinarySearchTree::insertCourse(const Course& course) {
    // If root is empty, add course to root
    if (root == nullptr){
        root = new Node(course);
    } else {
        // Else, call private version
        insertCourse(root, course);
    }
}

/**
 * Private - Insert Course
 * Uses recursion
 * @param node
 * @param course
 */
void BinarySearchTree::insertCourse(BinarySearchTree::Node *node, const Course& course) {
    // If the node's courseNumber is alphanumerically greater than the course to add, traverse to left child
    if (node->course.courseNumber > course.courseNumber) {
        // If left child is empty, insert new node with course here
        if (node->left == nullptr) {
            node->left = new Node(course);

            // Print Add Confirmation - Uncomment for testing
            // cout << "Added " << course.courseNumber << endl;

            // Insert complete, exit method
            return;

        } else {
            // Else, left child is not empty. Recursive call to traverse left
            insertCourse(node->left, course);
        }
    // Else, the node's courseNumber is alphanumerically less than the course to add, traverse to right child
    } else {
        // If right child is empty, insert new node with course here
        if (node->right == nullptr) {
            node->right = new Node(course);

            // Print Add Confirmation - Uncomment for testing
            // cout << "Added " << course.courseNumber << endl;

            // Insert complete, exit method
            return;
        } else {
            // Else, right child is not empty. Recursive call to traverse right
            insertCourse(node->right, course);
        }
    }
}


/**
 * Public - Print Course List
 * Calls private version
 */
void BinarySearchTree::printCourseList() {
    printCourseList(root);
}

/**
 * Private - Print Course List
 * Uses recursion
 * @param node
 */
void BinarySearchTree::printCourseList(BinarySearchTree::Node *node) {
    // If current node contains a course
    if (node != nullptr) {
        // Recursive call to traverse left
        printCourseList(node->left);

        // Print the courseNumber
        cout << node->course.courseNumber << endl;

        // Recursive call to traverse right
        printCourseList(node->right);
    }
}


/**
 * Public - Print Courses with Prerequisites
 * Calls private version
 */
void BinarySearchTree::printCourses() {
    printCourses(root);
}

/**
 * Private Print Courses with Prerequisites
 * Uses recursion
 * @param node
 */
void BinarySearchTree::printCourses(BinarySearchTree::Node *node) {
    // If current node contains a course
    if (node != nullptr) {
        // Recursive call to traverse left
        printCourses(node->left);

        // Print courseNumber and name
        cout << node->course.courseNumber << " - " << node->course.name;

        // If the current node's course has prerequisites,
        if(!node->course.prerequisites.empty()) {
            // Print pipe delimiter and header
            cout << "  |  Prerequisites:";

            // Print each prerequisite followed by a space
            for(const string& prerequisite : node->course.prerequisites) {
                cout << " " << prerequisite;
            }
        }
        // Add space in console for easier reading
        cout << endl;

        // Recursive call to traverse right
        printCourses(node->right);
    }
}


/**
 * Print One Course with Prerequisites
 * Uses a while loop in lieu of recursion
 * @param searchId
 */
void BinarySearchTree::printCourse(const string& searchId) {
    // Create a node called current, set to root
    // Assignment changes in while loop below
    Node* current = root;

    // While the current node contains a course
    while (current != nullptr){
        // If current node's courseNumber matches
        if (current->course.courseNumber == searchId) {
            // Print the course's courseNumber and name
            cout << current->course.courseNumber << " - " << current->course.name;

            // If the course has prerequisites
            if (!current->course.prerequisites.empty()){
                // Print pipe delimiter and header
                cout << "  |  Prerequisites:";

                // Print each prerequisite followed by a space
                for(const string& prerequisite : current->course.prerequisites) {
                    cout << " " << prerequisite;
                }
            }
            // Add space to console for easier viewing
            cout << endl;

            // Return to exit method
            return;

        // Current node's courseNumber does not match
        } else {
            // If the current node's courseNumber is alphanumerically greater, traverse left
            if (current->course.courseNumber > searchId) {
                current = current->left;

            // Else, traverse right
            } else {
                current = current->right;
            }
        }
    }

    // No course was found. Print message.
    cout << "[ERROR] " << searchId << " not found in course list!" << endl;
}
