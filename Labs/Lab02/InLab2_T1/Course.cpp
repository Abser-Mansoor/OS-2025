#include "Course.h"
#include <iostream>

Course::Course(const std::string& name) : name(name) {}

void Course::addStudent(const std::string& studentName) {
    for (int i = 0; i < 5; ++i) {
        if (students[i] == "") {
            students[i] = studentName;
            break;
        }
    }
}

void Course::addTeacher(const std::string& teacherName) {
    for (int i = 0; i < 5; ++i) {
        if (teachers[i] == "") {
            teachers[i] = teacherName;
            break;
        }
    }
}

void Course::printDetails() const {
    std::cout << "Course: " << name << std::endl;
    std::cout << "Students enrolled: ";
    for (int i = 0; i < 5; ++i) {
        if (students[i] != "") {
            std::cout << students[i] << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "Teachers: ";
    for (int i = 0; i < 5; ++i) {
        if (teachers[i] != "") {
            std::cout << teachers[i] << " ";
        }
    }
    std::cout << std::endl;
}
