#include "digraph.h"

/*Function call: Digraph graph(file_name);
Parameters: a string holding the file that contians the graph info (number of vertices, edges and what vertices form the edge)
Description: Constructor for the DigraphMatrix class, it first opens the file and processess the information, line by line*/
DigraphMatrix::DigraphMatrix(const string& filename)
{
    ifstream in(filename); //Opens the file
    string line; //Declares a string to hold the information in one line
    istringstream iss; //Declares a istringstream object to process the current line of information
    int u; //Declares an integer to hold the first vertix in the current edge
    int v; //Declares an integer to hold the second vectix in the current edge

    if (!in.is_open()) //Checks if the file opened correctly
    {
        cout << "File not opened correctly!" << endl; //Prints an error message

    }

    getline(in, line); //Retrieves the first line in the file
    iss.str(line); //Assigns it to the istringstream object
    iss >> n >> m; //Fisrt line holds the number of vertices and edges, here they are assigned to the member variables
    iss.clear(); //Clears the istrinstream object

    adjMatrix = vector<vector<int>>(n, vector<int>(n)); //Sets the member variable to the correct size

    while (getline(in, line)) //While there are lines to be read, keeps getting the next line
    {
        iss.str(line); //Assigns it to the istringstream object
        iss >> u >> v; //Every subsequent line after the first holds two vertices that form an edge
        iss.clear(); //Clears the istringstream object
        adjMatrix[u][v] = 1; //Changes the value of the position uxv to 1
    }

    in.close(); //Closes the file
    
}

/*Function call: graph.topologicalSort();
Description: Sorts the graph in topological orger and checks if there are cycles*/
vector<int> DigraphMatrix::topologicalSort() const
{
    vector<bool> visited = vector<bool>(n); //Declares and sets the size of a vector to hold the information if the vertix has been visited
    vector<int> sorted = vector<int>(n); //Declares and sets the size of a vector to hold the position of the vertices after sorting
    bool cycle = false; //Declares and initializes a boolean variable to hold if there are cycles
    int index = n-1; //As the exploration direction is bacwards in relation to a topological sort, declare and define a index that starts at the end
    errorHandling cycleFound; //Creates an struct object to throw the error

    for (int i = 0; i < n; i++) //loops through all the elements in the visited vector
    {
        visited[i] = false; //Sets every element to false
    }

    for (int i = 0; i < n; i++) //loops through all the elements
    {
        if (visited[i] == 0) index = checkSort(i, index, sorted, visited); //Checks if the vertix has been visited, if it is not, call the checkSort function
    }

    cycle = findCycle (); //Calls the function findCycle and sets the return value to cycle variable

    if (!cycle) //Checks if the cycle variable is true or false
    {
        return sorted; //If there is no cycle, return the vector
    }
    else 
    {
        throw cycleFound; //If there is a cycle, trhow an error message
    }
};

/*Function call: graph.checkSort(curr, index, sorted, visited);
Parameters: The current vertix being checkes, the current index to be added to sorted, the sorted vector, and the visited vector
Description: Finds out recursevely the order for the elements to be added in the sorted vector*/
int DigraphMatrix::checkSort(int curr, int index, vector<int> &s, vector<bool> &v) const
{
    if (v[curr] == true) return index; //Checks if the current vector has beeing visited, if it was return withou changing the index

    v[curr] = true; //Sets the current vector as visited

    for (int i = 0; i < n; i++) //Loops through all the elements
    {
        if (adjMatrix[curr][i] == 1 && v[i] == false) //Checks if the current vertix and the other vertices have an edge and if the other vertices are not visited
        {
            index = checkSort(i, index, s, v); //If both are ture, calls the function checkSort on the new vertix and updates the index variable to the return value
        }
    }

    s[index--] = curr; //Sets the current vertix to the sorted vector and decrements index
    return index; //returns index
}

/*Function call: boolean = findCycle();
Description: Tries to find a cycle in the current graph*/
bool DigraphMatrix::findCycle() const
{
    vector<cycleList> vec = vector<cycleList> (n); //Declares an auxiliar vector of an enum with two states and sets its size

    for (int i = 0; i < n; i++) //Loops through the whole vector
    {
        vec[i] = zero; //Sets all elements to the zero (meaning no vertix has been visited or is in the current path)
    }

    for (int j = 0; j < n; j++) //Loops again through the whole vector
    {
        if (vec[j] == zero) //Cehcks if it is the first time the j element has been visited
        {
            if (!checkCycle(j, vec)) //Calls an auxiliar funtion to recursively run trough the path created
            {
                return true; //Return true if there are cycles
            }
        } 
    }

    return false; //returns false if no cycle was found
}

/*Function call: boolean = checkCycle(curr, vector);
Description: Cehcks if there is a cycle in the current path*/
bool DigraphMatrix::checkCycle(int curr, vector<cycleList> &v) const
{
    v[curr] = first; //Sets the current vertix as visited once

    for (int i = 0; i < n; i++) //Loops through the whole vector
    {
        if (adjMatrix[curr][i] == 1) //Cehcks if there is an edge betwen the current vertix and the loop vertices
        {
            if (v[i] == first) //Cehcks if the loop vertix has been visited once
            {
                return true; //If it has, returns true as this would be the second time the vertix is visited
            }

            if (v[i] == zero && checkCycle(i, v)) //Checks if the the loop vertix has not been visited and the return value on the loop vertix
            {
                return true; //Returns true if the the next steps of the path lead to one previously visited vector as this means a cycle is found
            }
        }
    }
    return false; //Returns false if none of the above are true}
}