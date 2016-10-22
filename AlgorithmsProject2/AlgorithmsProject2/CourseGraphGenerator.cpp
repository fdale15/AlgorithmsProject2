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
shared_ptr<vector<Course>> CourseGraphGenerator::getCourseList()
{
	auto result = make_shared<vector<Course>>();

	//For each line, extract the name of the course.
	//This is the first match of the list provided to us.
	for (auto line : _rawCourseData)
	{
		auto matches = Utilities::MatchAll(line, CoursePattern);

		if (matches.size() > 0)
		{
			result->push_back(matches[0]);
		}
	}

	return result;
}

//Add prerequisites to a vector of courses.
void CourseGraphGenerator::addPrereqs(shared_ptr<vector<Course>> courses)
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
					//Loop through the courses listed in our vector.
					for_each(courses->begin(), courses->end(), [&](auto course)
					{
						//if the course (course) is equal to the prerequisite of the first course (matches[0]) in the line we just extracted,
						//this means this course (course) is a prerequisite of the first course (matches[0]).
						//We can then add matches[0] to the course.PrereqFor as the course is a prerequisite for the course at matches[0].
						if (course.Name == strMatched)
							course.PrereqFor->push_back(matches[0]);
					});
				}
			}
		}
	}
}

//Returns the fully populated graph of courses as an adjacency list.
shared_ptr<vector<Course>> CourseGraphGenerator::GetCourseGraph()
{
	//Gets the course list.
	auto courseList = getCourseList();
	//Adds the prerequisites.
	addPrereqs(courseList);
	
	return courseList;
}
