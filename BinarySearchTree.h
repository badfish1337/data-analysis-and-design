/**
 * Christopher Dewey
 * April 16, 2022
 * SNHU CS 300
 * Module Seven
 * Project Two
 *
 *      ******************************
 *      *   BinarySearchTree Header  *
 *      ******************************
 */

#ifndef PROJECTTWO_BINARYSEARCHTREE_H
#define PROJECTTWO_BINARYSEARCHTREE_H

#include <utility>
#include "Course.h"


class BinarySearchTree {

public:
    // Define Node structure/contents to enable traversal
    struct Node {
        Course course;
        Node* left;
        Node* right;

        // Default Node constructor
        Node() {
            left = nullptr;
            right = nullptr;
        }

        // Overloaded Node constructor (Builds upon default constructor)
        explicit Node(Course course) : Node() {
            this->course = std::move(course);
        }
    };

    Node* root;

    // Public Method signatures
    void insertCourse(const Course& course);
    void printCourseList();
    void printCourses();
    void printCourse(const string& searchId);

private:
    // Private method signatures
    static void insertCourse(Node* node, const Course& course);
    void printCourseList(Node* node);
    void printCourses(Node* node);

};


#endif //PROJECTTWO_BINARYSEARCHTREE_H
