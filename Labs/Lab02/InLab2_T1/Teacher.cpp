#include "Teacher.h"
#include <iostream>

Teacher::Teacher(const std::string& name) : name(name) {}

void Teacher::teachCourse(const std::string& courseName) {
    for (int i = 0; i < 5; ++i) {
        if (courses[i] == "") {
            courses[i] = courseName;
            break;
        }
    }
}

void Teacher::printCourses() const {
    std::cout << name << " teaches the following courses: ";
    for (int i = 0; i < 5; ++i) {
        if (courses[i] != "") {
            std::cout << courses[i] << " ";
        }
    }
    std::cout << std::endl;
}
