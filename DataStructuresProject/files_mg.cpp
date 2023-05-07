#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<vector>
#include<set>
#include "Student.h"
#include "Course.h"
#include"Course.cpp"
#include "files_mg.h"
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
void files_mg::save_course_data_into_files()
{
    // Create a file stream
    std::ofstream courseFile("course.txt");

    // Iterate over the key-value pairs in the map
    for (const auto& pair : GlobalDataa::courses) {
        const Course& c = pair.second;
        // Write the course data to the file
        courseFile << c.name << "," << c.code << "," << c.requirement_or_elective << ","
            << c.max_num_std << "," << c.hours << "," << c.instructor << ",";
        // Write the prerequisites to the file
        for (const auto& prereq : c.prerequisites) {
            courseFile << prereq << ";";
        }
        courseFile << "\n";
    }

    // Close the file stream
    courseFile.close();
}
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
void files_mg::save_std_data_into_files()
{
    // Create a file stream
    ofstream stdFile("student1.txt");

    // Iterate over the key-value pairs in the map
    for (const auto& pair : GlobalDataa::students) {
        const Student& s = pair.second;
        // Write the student data to the file
        stdFile << s.name << "," << s.email << "," << s.id << "," << s.password << ","
            << s.max_hours_allowed << "," << s.academic_year << "," << s.gpa << ",";
        // Write the finished courses to the file
        for (const auto& course : s.finished_courses) {
            stdFile << course << ";";
        }
        stdFile << ",";

        // Write the grade for finished courses to the file
        for (const auto& grade : s.gradesfor_finished_courses) {
            stdFile << grade << ";";
        }
        stdFile << ",";
        // Write the checkprereq to the file
        for (string x : s.checkprereq) {
            stdFile << x << ";";
        }
        stdFile << ",";
        // Write the in-progress courses to the file

        for (const auto& course : s.inprogress_courses) {
            stdFile << course << ";";
        }
        stdFile << "\n";
    }

    // Close the file stream
    stdFile.close();

}
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
void files_mg::load_coarse_data_from_files()
{
    //open the file 
    ifstream coursefile("course.txt");

    // read the data from file line by line 

    string line;
    while (getline(coursefile, line))
    {
        stringstream linestream(line);
        string name;
        int code;
        bool requirement_or_elective;
        int max_num_std;
        double hours;
        string instructor;
        vector<std::string> prerequisites;

        //parse the line and extract data 

        if (getline(linestream, name, ',') &&
            linestream >> code &&
            linestream.ignore() &&
            linestream >> requirement_or_elective &&
            linestream.ignore() &&
            linestream >> max_num_std &&
            linestream.ignore() &&
            linestream >> hours &&
            linestream.ignore() &&
            getline(linestream, instructor, ','))
        {
            string prereqs;
            getline(linestream, prereqs);
            stringstream prereqsstream(prereqs);
            string prereq;
            while (getline(prereqsstream, prereq, ';'))
            {
                prerequisites.push_back(prereq);
            }

        }
        // Create a new Course object and add it to the unordered_map
        GlobalDataa::courses.emplace(name, Course(name, code, requirement_or_elective, max_num_std, hours, instructor));
        GlobalDataa::courses[name].prerequisites = prerequisites;

    }

    // Close the input file stream
    coursefile.close();


}
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------

void files_mg::load_std_data_from_files()
{

    // Open the input file stream
    ifstream stdFile("students.txt");

    // Read the data from the file line by line
    std::string line;
    while (getline(stdFile, line)) {
        stringstream lineStream(line);
        string name;
        string email;
        int id;
        string password;
        int max_hours_allowed;
        set<string> finished_courses;
        set<double> gradefor_finished_courses;
        set<string> inprogress_courses;
        string academic_year;
        float gpa;

        if (getline(lineStream, name, ',') &&
            getline(lineStream, email, ',') &&
            lineStream >> id &&
            lineStream.ignore() &&
            std::getline(lineStream, password, ',') &&
            lineStream >> max_hours_allowed &&
            lineStream.ignore() &&
            std::getline(lineStream, academic_year, ',') &&
            lineStream >> gpa) {

            // Parse the finished courses
            string finished_courses_str;
            if (getline(lineStream, finished_courses_str, ',')) {
                stringstream finished_courses_stream(finished_courses_str);
                string course;
                while (getline(finished_courses_stream, course, ';')) {
                    finished_courses.insert(course);
                }
            }

            // Parse the grade for finished courses
            string gradefor_finished_courses_str;
            if (getline(lineStream, gradefor_finished_courses_str, ',')) {
                stringstream gradefor_finished_courses_stream(gradefor_finished_courses_str);
                string gradest;
                while (getline(gradefor_finished_courses_stream, gradest, ';')) {
                    double grade = stoi(gradest);
                    gradefor_finished_courses.insert(grade);
                }
            }

            // Parse the in-progress courses
            string inprogress_courses_str;
            if (getline(lineStream, inprogress_courses_str)) {
                stringstream inprogress_courses_stream(inprogress_courses_str);
                string course;
                while (std::getline(inprogress_courses_stream, course, ';')) {
                    inprogress_courses.insert(course);
                }
            }

            // Create the student object and add it to the map
            Student student(name, id, password, max_hours_allowed, finished_courses, gradefor_finished_courses, inprogress_courses, academic_year, gpa);
            GlobalDataa::students[id] = student;
        }
    }

    // Close the input file stream
    stdFile.close();

}