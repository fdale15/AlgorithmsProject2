#pragma once
#include <regex>
#include <algorithm>
#include "CourseGraphGenerator.h"
#include "Utilities.h"

using namespace std;

CourseGraphGenerator::CourseGraphGenerator()
{
  _rawCourseData = Utilities::ReadFile("data.txt");
}


vector<Course> CourseGraphGenerator::getCourseList()
{
  auto result = vector<Course>();

  smatch matches;
  regex exp("[A-Z]{2,5} [0-9]{4}");

  for (auto line : _rawCourseData)
  {
    regex_search(line, matches, exp);

    if (matches.size() > 0)
    {
      Course c(matches[0]);
      result.push_back(c);
    }
  }

  return result;
}

vector<Course> CourseGraphGenerator::addPrereqs(vector<Course> courses)
{
  smatch matches;
  regex exp("[A-Z{2,5}\\ [0-9]{4}");

  for (auto line : _rawCourseData)
  {
    regex_search(line, matches, exp);

    if (matches.size() > 0)
    {
      for (auto match : matches)
      {
        cout << match << endl;
        if (match != matches[0])
          for_each(courses.begin(), courses.end(), [&](auto course){
              if (course.Name == match)
                course.PrereqFor.push_back(matches[0]);
              cout << match << " : " << course.Name << endl;
          });
      }
    }
  }

  return courses;
}

vector<Course> CourseGraphGenerator::GetCourseGraph()
{
  return addPrereqs(getCourseList());
}
