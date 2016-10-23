#pragma once
#include <vector>
#include <map>
#include <tuple>
#include <iostream>
#include <memory>
#include "Utilities.h"

using namespace std;

//This represents a node in our graph.
struct Course
{
	string Name;
	//Points to each course it is a prerequisite for.
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

	//Simply allows us to output a course to the console.
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

//Generates a graph as an adjacency list.
class CourseGraphGenerator
{
	//Pattern to match course names like CSCI 3330.
	const string CoursePattern = "[A-Z]{2,5} [0-9]{4}";
	vector<string> _rawCourseData;

	//Returns a list of courses as a shared_ptr to a map of courses with the course.Name as the key.
	shared_ptr<map<string, Course>> getCourseList();
	//Add prerequisites to a map of courses.
	tuple<string, vector<string>> addPrereqs(shared_ptr<map<string, Course>> courses, string course, vector<string> prereqs);

public:

	CourseGraphGenerator();
	//Returns the fully populated graph of courses as an adjacency list.
	shared_ptr<map<string, Course>> GetCourseGraph();
};
