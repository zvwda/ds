#pragma once
#include<iostream>
#include<vector>
#include<set>
#include"Course.h"
using namespace std;
class Student {


public:
    string name;
    string email;
    int id;
    string password;
    int max_hours_allowed;
    set<string>finished_courses;
    set<double> gradesfor_finished_courses;
    set<string>inprogress_courses;
    vector<string>checkprereq;
    string academic_year;
    float gpa;
    int studCount = 0;
    Student();
    Student(string name, int id, string password, int max_hours_allowed, set<string>finished_courses, set<double> gradesfor_finished_courses, set<string>inprogress_courses, string academic_year, float gpa);
    bool login(int input_id, string input_password);
    void View_List_of_all_available_courses(Student s);
    void filter_courses(Student s);
    void viewDetailsOfSpecificCourse(Course c);
    void edit_data(Student s);
    void viewAllCourses(Student s);
    void registerCourse(Student s, Course c);
};