# AlgorithmsProject2
Graph theory problem. Quickest path through college.

|What needs done:| Progress|
|:----------------|:------------|
|[1. Represent the graph by using an adjacency list or matrix.](#1)|
|[2. Implement DFS algorithm for the adjacency list and Course struct.](#2)|
|[3. Modify DFS algorithm to record pre/post visits.](#3)|
|[4. Design algorithm to generate semester courses.](#5)|

<a id="1">
#Represent Graph as Data Structure.

Rather than reformat the data given to us into something that represents an adjacency list and create a protocol to parse said list, I decided to use regular expressions to generate the graph.

The data, after parsed with the regular expression "[A-Z]{2,4} [0-9]{4}", looks like this:
>MATH 1390 COLLEGE ALGEBRA  
>MATH 1591 Calculus I (MATH 1390)  
>MATH 2330 Discrete Mathematics (MATH 1591 and CSCI 1470)  
>MATH 3320 Linear Algebra (MATH 2330)  
>CSCI 1470 COMPUTER SCIENCE I (MATH 1390)  


>MATH 1390  
>MATH 1591, MATH 1390  
>MATH 2330, MATH 1591, CSCI 1470  
>MATH 3320, MATH 2330  
>CSCI 1470, MATH 1390  


In this form, the prerequisites are the second and onward elements of the first listed course.

To create a Directed Acyclic Graph from this.
  1. Loop through the lines, extract the first element, and add it to a list.
  2. Call the addPrereqs method passing in the list of courses, current course, and prerequisites for that course.
  
</a>
---
<a id="2">
#Implement DFS algorithm for adjacency list.

This step is very straighforward.  Someone just needs to implement the DFS algorithm in C++. Since we are using the adjacency list and a struct to represent nodes, there are a couple caveats.

1.  The adjacency list is of type 
```cpp
shared_ptr<unordered_map<string, Course>> 
```
so the method signatures should resemble
```cpp
DFS(shared_ptr<unordered_map<string, Course>> graph) 
```
and  
```cpp
Explore(shared_ptr<unordered_map<string, Course>> graph, Course node)
```

2. The nodes are Course structs
```cpp
struct Course 
{
  string Name;
  shared_ptr<vector<Course>> PrereqFor;
};
```

To cycle through the nodes in the DFS algorithm use iterators or a for-range loop like:
```cpp
//Note: you must dereference graph for this to work properly.
for (auto node : *graph)
{
}
```

To keep track of visits you can use another unordered_map like:
```cpp
auto visited = unordered_map<string, bool>();

for (auto node : *graph)
{
  //To visit.
  visited[node.first] = true;
}

//To check whether visited or not
for (auto nextCourse : node.PrereqFor)
{
  if (visited[nextCourse.Name])
    //Visited before.
  else
    //Not visited before.
}
```

I used an 
```cpp
unordered_map<string, bool>
```
to keep track of whether or not we had visited a node.

</a>
---
<a id="3">
#Modify DFS algorithm to get Topological Orderings

This part is very straightforward as well.  Since the last post-visit is of first intrest to us, we can use a stack to store the topological ordering.

```cpp
unordered_map<string, bool> _visits;
vector<string> _topologicalOrdering;

void DFS(shared_ptr<unordered_map<string, Course>> graph)
{
  for (auto node : *graph)
  {
    Explore(graph, node);
  }
}

void Explore(shared_ptr<unordered_map<string, Course>> graph, Course node)
{
  if (!_visits[node.Name])
  {
    _visits[node.Name] = true;
    
    for (auto childNode : *(node.PrereqsFor))
    {
      Explore(graph, childNode);
      
      //This would be the post-visit. We can add the course to our stack here.
      _topologicalOrdering.push_back(childNode.Name);
    }
  }
}
```
At the end, we have a ```cpp vector<string> ``` of classes in topological order.

</a>
---
<a id="5">
#Design Algorithm to Generate Semester Courses

This part was the trickiest part and depended on your designs to the above problems.

1. Cycle through the courses in topological order.
2. Determine whether or not you could enroll in the course.
  1.  If a course you were currently enrolled in was a prerequisite for a prospect course, you could not enroll.
  2.  If a course that you could not enroll in was as prerequisite for a prospect course, you could not enroll.
  3.  Otherwise, you were free to enroll in the course.
3. Remove enrolled courses from topological order, preserving order.
4. Repeat with remaining courses for the next semester.

</a>
---
