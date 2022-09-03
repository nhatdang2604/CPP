#pragma once
#ifndef  _GRAPH_H_
#define _GRAPH_H_

#include<functional>
#include<queue>
#include<vector>
#include<utility>
#include<iostream>
using namespace std;

#define INF 0x3f3f3f3f

struct Vertex {
	vector<pair <int, int>> adjacencyEdge;
};

class Graph {
public:
	Graph(const int&);
	~Graph();

	int getNumberOfVertex();
	void addEdge(int src, int dst, int weight);
	void dijkstra(int src, int dst);
	void display();

	//Only use for 2-direction graph
	Graph* prim(const int& startVertex = 0);
private:
	int numberOfVertex;
	Vertex *vertex;
	Graph* minimumSpanningTree = nullptr;

	int _getNumberOfVertex();
	void _addEdge(int src, int dst, int weight);
	void _dijkstra(int src, int dst);
	void _display();
	Graph* _prim(const int&);
};




#endif // ! _GRAPH_H_
