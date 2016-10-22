#pragma once
#include <vector>
#include <iostream>
#include "Utilities.h"

using namespace std;

struct Course
{
  string Name;
  vector<string> PrereqFor;

  Course()
  {
      Name = "";
      PrereqFor = vector<string>();
  }
  Course(string name)
  {
    Name = name;
    PrereqFor = vector<string>();
  }

  friend ostream& operator<<(ostream& stream, const Course& c)
  {
    stream << "Name: " << c.Name << endl;
    stream << "Prerequisites:" << endl;
    Utilities::PrintVector(c.PrereqFor);
    stream << "------------------------" << endl;

    return stream;
  }
};

class CourseGraphGenerator
{
  vector<string> _rawCourseData;

public:

  vector<Course> getCourseList();
  vector<Course> addPrereqs(vector<Course> courses);

  CourseGraphGenerator();
  vector<Course> GetCourseGraph();
};
