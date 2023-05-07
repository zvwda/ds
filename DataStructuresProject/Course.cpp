#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include"Course.h"
#include"GlobalDataa.h"

using namespace std;


Course::Course() {

}

Course::Course(string name, int code, bool requirement_or_elective, int max_num_std, double hours, string instructor) {
    this->name = name;
    this->code = code;
    this->requirement_or_elective = requirement_or_elective;
    this->max_num_std = max_num_std;
    this->hours = hours;
    this->instructor = instructor;
}



void Course::add_prerequisite(string prerequisite) {
    prerequisites.push_back(prerequisite);
}



void Course::print_prerequisites() {
    cout << "Prerequisites for " << name << ":" << endl;
    for (int i = 0; i < prerequisites.size(); i++) {
        cout << "- " << prerequisites[i] << endl;
    }
}


class Graph {
private:
public:

    unordered_map<string, vector<string>> adjacency_list;

    void add_course(Course course) {
        adjacency_list[course.name] = vector<string>();
        GlobalDataa::courses[course.name] = course;
    }


    void add_prerequisite(Course& course, string prerequisite) {
        adjacency_list[course.name].push_back(prerequisite);
        course.add_prerequisite(prerequisite);
    }

    void remove_course(Course course) {
        adjacency_list.erase(course.name);
        GlobalDataa::courses.erase(course.name);
        for (auto& pair : adjacency_list) {
            vector<string>& prerequisites = pair.second;
            prerequisites.erase(remove(prerequisites.begin(), prerequisites.end(), course.name), prerequisites.end());
        }
    }

    void print_graph() {
        for (auto& pair : adjacency_list) {
            string course_name = pair.first;
            vector<string>& prerequisites = pair.second;
            cout << course_name << " prerequisites:";
            for (int i = 0; i < prerequisites.size(); i++) {
                cout << " " << prerequisites[i];
            }
            cout << endl;
        }
    }
};

