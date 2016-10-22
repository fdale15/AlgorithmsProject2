#pragma once
#include <regex>
#include <memory>
#include <algorithm>
#include "CourseGraphGenerator.h"
#include "Utilities.h"

using namespace std;

CourseGraphGenerator::CourseGraphGenerator()
{
	//Loads the course data.
	_rawCourseData = Utilities::ReadFile("data.txt");
}

//Returns a list of courses as a shared_ptr to a vector of courses.
shared_ptr<unordered_map<string, Course>> CourseGraphGenerator::getCourseList()
{
	auto result = make_shared<unordered_map<string, Course>>();

	//For each line, extract the name of the course.
	//This is the first match of the list provided to us.
	for (auto line : _rawCourseData)
	{
		auto matches = Utilities::MatchAll(line, CoursePattern);

		if (matches.size() > 0)
		{
			//We insert the course name into the map here.
			(*result)[matches[0]] = Course(matches[0]);
		}
	}

	return result;
}

//Add prerequisites to a vector of courses.
void CourseGraphGenerator::addPrereqs(shared_ptr<unordered_map<string, Course>> courses)
{
	//For each line extract all the course names.
	//The first is the name of the course, the following are prerequisites.
	for (auto line : _rawCourseData)
	{
		auto matches = Utilities::MatchAll(line, CoursePattern);

		if (matches.size() > 0)
		{
			//Loop through course names.
			for (auto strMatched : matches)
			{
				//If its the first, we don't care. We are interested in the prerequisites.
				//Its important we remember that the prerequisites are for the first course, however.
				if (strMatched != matches[0])
				{
					//This grabs the prerequisite course and adds the course it is a prerequisite for into its PrereqFor vector.
					courses->at(strMatched).PrereqFor->push_back(matches[0]);
				}
			}
		}
	}
}

//Returns the fully populated graph of courses as an adjacency list.
shared_ptr<unordered_map<string, Course>> CourseGraphGenerator::GetCourseGraph()
{
	//Gets the course list.
	auto courseList = getCourseList();
	//Adds the prerequisites.
	addPrereqs(courseList);
	
	return courseList;
}
