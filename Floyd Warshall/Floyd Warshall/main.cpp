#include "Graph.h"

int main() {
	Graph graph;
	int **dp;
	createGraph(graph, 5);
	addEdge(graph, 0, 1, 1);
	addEdge(graph, 1, 0, 1);
	addEdge(graph, 1, 2, 2);
	addEdge(graph, 2, 1, 2);
	addEdge(graph, 2, 3, 3);
	addEdge(graph, 3, 2, 3);
	addEdge(graph, 3, 4, 4);
	addEdge(graph, 4, 3, 4);
	addEdge(graph, 1, 4, 1);
	addEdge(graph, 4, 1, 1);
	addEdge(graph, 0, 4, 7);
	addEdge(graph, 4, 0, 7);
	addEdge(graph, 2, 4, 4);
	addEdge(graph, 4, 2, 4);
	init(graph, dp);
	FloydWarshall(graph, dp);
	trace(graph, 0, 3, dp);
	release(graph, dp);
	system("PAUSE");
	return 0;
}