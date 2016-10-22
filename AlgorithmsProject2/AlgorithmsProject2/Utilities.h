#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

namespace Utilities
{
	//Reads a file from provided filename and returns it as a vector of strings.
	static vector<string> ReadFile(string fileName)
	{
		auto result = vector<string>();

		ifstream file(fileName);

		if (!file.fail())
		{
			while (!file.eof())
			{
				string s = "";
				getline(file, s);
				result.push_back(s);
			}
		}

		return result;
	}

	//Prints a vector of objects from the provided pointer.
	//PrePrint allows you to optionally print something ahead of the object.
	//PostPrint allows you to optionally print something after the object.
	template <typename T>
	static void PrintVector(shared_ptr<vector<T>> vp, string prePrint = "", string postPrint = "")
	{
		auto copy = *(vp.get());

		for (const auto& item : copy)
		{
			cout << prePrint << item << postPrint << endl;
		}
	}

	//Accepts a string and a regular expression.  
	//Returns all occurences of the pattern in a vector of strings.
	static vector<string> MatchAll(string line, regex exp)
	{
		auto result = vector<string>();
		smatch matches;

		//Starts at the beginning of the string.
		auto startPoint = line.cbegin();
		//Continues looping until there is no more left to check.
		while (startPoint != line.cend())
		{
			regex_search(startPoint, line.cend(), matches, exp);
			//If it matches anything, it checks the matches.
			if (matches.size() > 0)
			{
				for (auto i : matches)
				{
					//Each match is pushed onto the result vector.
					result.push_back(i.str());
					//The startPoint is updated to where the end of the match was.
					startPoint = i.second;
				}
			}
			//If it doesn't match anything, it breaks from the loop.
			else
			{
				break;
			}
		}

		return result;
	}
}
