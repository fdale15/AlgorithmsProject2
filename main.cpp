#include "CourseGraphGenerator.h"
#include "Utilities.h"

using namespace std;

int main()
{
    CourseGraphGenerator cgg;

    //Utilities::PrintVector(cgg.GetCourseGraph());

    cgg.addPrereqs(cgg.getCourseList());
}
