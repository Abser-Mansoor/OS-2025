#include "Student.h"
#include <iostream>

Student::Student(const std::string& name) : name(name) {}

void Student::enrollInCourse(const std::string& courseName) {
    for (int i = 0; i < 5; ++i) {
        if (courses[i] == "") {
            courses[i] = courseName;
            break;
        }
    }
}

void Student::printCourses() const {
    std::cout << name << " is enrolled in the following courses: ";
    for (int i = 0; i < 5; ++i) {
        if (courses[i] != "") {
            std::cout << courses[i] << " ";
        }
    }
    std::cout << std::endl;
}
