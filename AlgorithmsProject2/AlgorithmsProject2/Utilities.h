#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

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
    static void PrintVector(vector<T> v)
    {
      for (const auto& item : v)
      {
          cout << item << endl;
          //cout << item << endl;
      }
    }
}
