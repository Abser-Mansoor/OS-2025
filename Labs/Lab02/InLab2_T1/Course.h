#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
public:
    std::string name;
    std::string students[5]; // Array to store up to 5 students
    std::string teachers[5]; // Array to store up to 5 teachers

    Course(const std::string& name);
    void addStudent(const std::string& studentName);
    void addTeacher(const std::string& teacherName);
    void printDetails() const;
};

#endif
