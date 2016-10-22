#pragma once
#include <regex>
#include <memory>
#include <algorithm>
#include "CourseGraphGenerator.h"
#include "Utilities.h"

using namespace std;

CourseGraphGenerator::CourseGraphGenerator()
{
	_rawCourseData = Utilities::ReadFile("data.txt");
}


shared_ptr<vector<Course>> CourseGraphGenerator::getCourseList()
{
	auto result = make_shared<vector<Course>>();

	regex exp("[A-Z]{2,5} [0-9]{4}");

	for (auto line : _rawCourseData)
	{
		auto matches = Utilities::MatchAll(line, exp);

		if (matches.size() > 0)
		{
			result->push_back(matches[0]);
		}
	}

	return result;
}

void CourseGraphGenerator::addPrereqs(shared_ptr<vector<Course>> courses)
{
	regex exp("[A-Z]{2,5} [0-9]{4}");

	for (auto line : _rawCourseData)
	{
		auto matches = Utilities::MatchAll(line, exp);

		if (matches.size() > 0)
		{
			for (auto strMatched : matches)
			{
				if (strMatched != matches[0])
					for_each(courses->begin(), courses->end(), [&](auto course)
					         {
						         if (course.Name == strMatched)
							         course.PrereqFor->push_back(matches[0]);
					         });
			}
		}
	}
}

shared_ptr<vector<Course>> CourseGraphGenerator::GetCourseGraph()
{
	auto courseList = getCourseList();
	addPrereqs(courseList);
	return courseList;
}
