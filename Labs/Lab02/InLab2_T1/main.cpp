#include <iostream>
#include "Student.h"
#include "Teacher.h"
#include "Course.h"

int main() {
    Student s1("Ali");
    Student s2("Abser");

    Teacher t1("Sir Farooq");
    Teacher t2("Sir Shoaib");

    Course c1("Mathematics");
    Course c2("DS");

    s1.enrollInCourse("Mathematics");
    s2.enrollInCourse("DS");

    c1.addTeacher("Sir Farooq");
    c2.addTeacher("Sir Shoaib");

    c1.addStudent("Abser");
    c2.addStudent("Ali");

    s1.printCourses();
    s2.printCourses();
    
    t1.printCourses();
    t2.printCourses();
    
    c1.printDetails();
    c2.printDetails();

    return 0;
}
