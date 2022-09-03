#pragma once
#ifndef _GRAPH_H_
#define _GRAPH_H_
#define INF 0x3f3f3f3f
#include <iostream>
#include <vector>
using namespace std;

struct Graph {
	int numberOfVertex;
	int **map;
};

int min(int, int);
void createGraph(Graph&, int);
void addEdge(Graph&, int, int, int);
void init(Graph&, int **&);
void FloydWarshall(Graph, int **&);
void trace(Graph, int, int, int **);
void release(Graph&, int**&);


#endif // !_GRAPH_H_
