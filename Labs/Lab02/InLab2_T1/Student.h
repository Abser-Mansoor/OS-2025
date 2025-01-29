#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
    std::string name;
    std::string courses[5]; // Array to store up to 5 courses

    Student(const std::string& name);
    void enrollInCourse(const std::string& courseName);
    void printCourses() const;
};

#endif
