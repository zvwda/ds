#pragma once
#include "admin.h"
#include "Admin.h"
#include<iostream>
#include<list>
#include<vector>
#include "course.h"
#include"Course.cpp"
#include"Student.h"
#include"Student.cpp"
class GlobalDataa
{
public:
	static unordered_map<string, Course> courses;
	static unordered_map<int, Student> students;

};

