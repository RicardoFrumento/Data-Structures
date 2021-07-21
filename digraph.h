#ifndef __DIGRAPH_H
#define __DIGRAPH_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

struct errorHandling : exception {}; //Struct to throw the error

enum cycleList {zero, first}; //Enumeartion to be used when checking if there are cycles

class DigraphMatrix
{
public:
  DigraphMatrix(const string& filename);
  vector<int> topologicalSort() const;
  int checkSort(int i, int index, vector<int> &s, vector<bool> &v) const;
  bool findCycle() const;
  bool checkCycle(int i, vector<cycleList> &v) const;
private:
  int n;
  int m;
  vector<vector<int>> adjMatrix;
};
#endif