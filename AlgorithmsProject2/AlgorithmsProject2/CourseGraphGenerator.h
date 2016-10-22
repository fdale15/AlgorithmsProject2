#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "Utilities.h"

using namespace std;

struct Course
{
	string Name;
	shared_ptr<vector<string>> PrereqFor;

	Course()
	{
		Name = "";
		PrereqFor = make_shared<vector<string>>();
	}

	Course(string name)
	{
		Name = name;
		PrereqFor = make_shared<vector<string>>();
	}

	friend ostream& operator<<(ostream& stream, const Course& c)
	{
		stream << "Name: " << c.Name << endl;
		if (c.PrereqFor->size() > 0)
		{
			stream << "Prerequisite for:" << endl;
			Utilities::PrintVector(c.PrereqFor, "\t*");
		}
		stream << "------------------------" << endl;
		
		return stream;
	}
};

class CourseGraphGenerator
{
	vector<string> _rawCourseData;

	shared_ptr<vector<Course>> getCourseList();
	void addPrereqs(shared_ptr<vector<Course>> courses);

public:

	CourseGraphGenerator();
	shared_ptr<vector<Course>> GetCourseGraph();
};
