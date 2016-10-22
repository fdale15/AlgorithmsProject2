#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

namespace Utilities
{
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

	template <typename T>
	static void PrintVector(shared_ptr<vector<T>> vp, string prePrint = "", string postPrint = "")
	{
		auto copy = *(vp.get());

		for (const auto& item : copy)
		{
			cout << prePrint << item << postPrint << endl;
			//cout << item << endl;
		}
	}

	static vector<string> MatchAll(string line, regex exp)
	{
		auto result = vector<string>();
		smatch matches;

		auto startPoint = line.cbegin();
		while (startPoint != line.cend())
		{
			regex_search(startPoint, line.cend(), matches, exp);
			if (matches.size() > 0)
			{
				for (auto i : matches)
				{
					result.push_back(i.str());
					startPoint = i.second;
				}
			}
			else
			{
				break;
			}
		}

		return result;
	}
}
