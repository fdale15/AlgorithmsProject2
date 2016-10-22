# AlgorithmsProject2
Graph theory problem. Quickest path through college.

|What needs done:| Progress|
|:----------------|:------------|
|[1. Represent the graph by using an adjacency list or matrix.](#1)|FINISHED|
|[2. Implement DFS algorithm for the adjacency list and Course struct.](#2)||
|[3. Modify DFS algorithm to record pre/post visits.](#3)||
|[4. Implement topological ordering algorithm.](#4)||
|[5. Design algorithm to generate semester courses.](#5)|FINISHED|
|[6. Implement algorithm to generate semester courses.](#6)||

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
  2. Loop through the lines again, and, for each element after the first, add the first element to the prerequisite courses lists.
  
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
</a>
---
<a id="3">
#Modify DFS algorithm to Record Pre/Post Visits

This part is very straightforward as well.  I would probably use a tuple<int, int> or create a simple struct and store that in an unordered map like so:

```cpp
struct Visit
{
  int PreVisit;
  int PostVisit;
};

int count = 0;
unordered_map<string, Visit> DFS(shared_ptr<unordered_map<string, Course>> graph)
{
  auto visits = unordered_map<string, Visit>();
  
  for (auto node : *graph)
  {
    auto visit = Visit();

    //do visit.PreVisit = ++count and visit.PostVisit = ++count at appropriate point.
    //do DFS.
    
    //This will add the visit to the visits.
    visits[node.First] = visit;
  }
  return visits;
}
```
</a>
---
<a id="4">
#Implement Topological Ordering Algorithm

Essentially, all you need to do is sort the visits in order of descending post-visits.

If you stored the visits like I mentioned in [Section 3](#3) then it may be a little harder to do it intuitively.  I would suggest extracting all the post visits and sorting the numbers.  Then loop through the visits again and pull out the names of the courses in the correct order.
</a>
---
<a id="5">
</a>
---
<a id="6">
</a>
