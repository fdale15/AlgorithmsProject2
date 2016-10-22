#include "CourseGraphGenerator.h"
#include <regex>
#include "Utilities.h"

using namespace std;

int main()
{
	CourseGraphGenerator cgg;

	auto graph = cgg.GetCourseGraph();

	Utilities::PrintVector(graph);

	int i;
	cin >> i;
}
