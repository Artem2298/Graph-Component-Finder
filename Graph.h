#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <fstream>
#include <stdio.h>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;
#pragma once

class Edge {
private:
    int from;
    int to;
public:
    Edge();
    Edge(int from, int to);
    int GetFrom();
    int GetTo();
    void SetFrom(int from);
    void SetTo(int to);
    int LoadData(int numberOfNodes, vector<Edge>& edges);
};

class Graph
{
private:
    vector<vector<int>> adjacencyList;
    vector<bool> visited;
    unordered_map<int, vector<int>> gate;
public:
    Graph(vector<Edge>& edges, int numberOfNodes);
    void FindBigComponent(int numberOfNodes, vector<int>& BigComp, vector<int>& BigCompHelp);
    void DFS(int index, vector<int>& BigCompHelp);
    vector<int> BFS(int elem, int numberOfNodes);
    void Centralita(vector<int> dist, int elem, int numberOfNodes, int citatel);
    int MoovDoTabulce(vector<int> BigComp);
};

