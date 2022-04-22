/**
 * Christopher Dewey
 * April 16, 2022
 * SNHU CS 300
 * Module Seven
 * Project Two
 *
 *      *********************************
 *      *    Course Class Definitions   *
 *      *********************************
 */

#include "Course.h"
#include <utility>

// Default course constructor
Course::Course() = default;

// Overloaded course constructor
Course::Course(string courseNumber, string name, vector<string> prerequisites){
    this->courseNumber = std::move(courseNumber);
    this->name = std::move(name);
    this->prerequisites = std::move(prerequisites);
}