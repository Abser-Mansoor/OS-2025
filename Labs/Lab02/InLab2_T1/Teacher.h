#ifndef TEACHER_H
#define TEACHER_H

#include <string>

class Teacher {
public:
    std::string name;
    std::string courses[5]; // Array to store up to 5 courses

    Teacher(const std::string& name);
    void teachCourse(const std::string& courseName);
    void printCourses() const;
};

#endif
