#pragma once
#include "Student.h"
#include<string>

using namespace std;


class Admin
{
    string name;
    string password;
public:

    Admin(string name, string password);

    void add_student(string name, int id, string password, int max_hours, int academic_year);
    void add_new_course(Course c);
    void Enter_course_prerequisite(Course c, string nameofprereq);
    void addcoursegrade(Student x);
    void editCourseData(Course c);
    void viewListOfStudCourses(Student x);
    void View_List_of_all_students_in_a_specific_course(Course c);
    bool adminLogin(string input_name, string input_password);

    virtual ~Admin();

};