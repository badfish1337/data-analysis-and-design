/**
 * Christopher Dewey
 * April 16, 2022
 * SNHU CS 300
 * Module Seven
 * Project Two
 *
 *      *********************
 *      *   Course Header   *
 *      *********************
 */

#ifndef PROJECTTWO_COURSE_H
#define PROJECTTWO_COURSE_H

#include <string>
#include <vector>
using namespace std;

class Course {
public:
    string courseNumber;
    string name;
    vector<string> prerequisites;

    Course();
    Course(string courseNumber, string name, vector<string> prerequisites);


};


#endif //PROJECTTWO_COURSE_H
