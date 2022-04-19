#pragma once
#include <algorithm>
#include <iostream>
#include "cstdlib"
#include <stack>
#include <vector>
#include <fstream>
using namespace std;

class Graph
{
private:
	int size;
	vector<vector<int>> table;

public:
	Graph();

	Graph(int v, float p);

	bool isIsolated();

	bool connectivity();

	int diameter();
	int doubleBFS(int source);
};

