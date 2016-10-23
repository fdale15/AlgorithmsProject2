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
shared_ptr<map<string, Course>> CourseGraphGenerator::getCourseList()
{
	auto result = make_shared<map<string, Course>>();

	//Keep up with the prereqs not found.  They may be added later in the list.
	auto prereqsNotFound = vector<tuple<string, vector<string>>>();

	//For each line, extract the name of the course.
	//This is the first match of the list provided to us.
	for (auto line : _rawCourseData)
	{
		auto matches = Utilities::MatchAll(line, CoursePattern);

		if (matches.size() > 0)
		{
			//We insert the course name into the map here.
			(*result)[matches[0]] = Course(matches[0]);

			if (matches.size() > 1)
			{
					addPrereqs(result, matches[0], vector<string>(matches.begin() + 1, matches.end()));
			}
		}
	}

	//Try to add the prereqsNotFound again.  They may have been added after the first attempt.
	for (auto prereq : prereqsNotFound)
	{
		//Discard the ones not found this time.
		addPrereqs(result, get<0>(prereq), get<1>(prereq));
	}

	return result;
}

//Add prerequisites to a vector of courses.
//Returns the prerequisites that could not be attached.
tuple<string, vector<string>> CourseGraphGenerator::addPrereqs(shared_ptr<map<string, Course>> courses, string course, vector<string> prereqs)
{
		//Keeps track if a prereq has not been stored.
		auto prereqNotFound = vector<string>();

		if (prereqs.size() > 0)
		{
			//Loop through prereq names.
			for (auto prereqCourse : prereqs)
			{
					//If the prereq already exists, add the course to the prereq's PrereqFor vector.
					if (courses->find(prereqCourse) != courses->end())
							(*courses)[prereqCourse].PrereqFor->push_back(course);
					else
							prereqNotFound.push_back(prereqCourse);
			}
		}

		return tuple<string, vector<string>>(course, prereqNotFound);
}

//Returns the fully populated graph of courses as an adjacency list.
shared_ptr<map<string, Course>> CourseGraphGenerator::GetCourseGraph()
{
	//Gets the course list.
	auto courseList = getCourseList();
	//Adds the prerequisites.
	//addPrereqs(courseList);

	return courseList;
}
