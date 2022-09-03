#include "Graph.h"

int main() {
	
	/*
	//Test 1 (Test for Dijkstra)
	Graph graph1(5);
	graph1.addEdge(0, 1, 10);
	graph1.addEdge(1, 2, 1);
	graph1.addEdge(2, 3, 6);
	graph1.addEdge(3, 2, 4);
	graph1.addEdge(4, 3, 2);
	graph1.addEdge(3, 0, 7);
	graph1.addEdge(0, 4, 5);
	graph1.addEdge(1, 4, 2);
	graph1.addEdge(4, 1, 3);
	graph1.addEdge(4, 2, 9);
	graph1.dijkstra(0, 2);
	*/

	/*
	//Test 2 (Test for Dijkstra)
	Graph graph2(8);
	graph2.addEdge(3, 1, 5);
	graph2.addEdge(2, 1, 1);
	graph2.addEdge(0, 3, 2);
	graph2.addEdge(5, 3, 2);
	graph2.addEdge(6, 4, 8);
	graph2.addEdge(1, 5, 3);
	graph2.addEdge(2, 5, 5);
	graph2.addEdge(1, 6, 7);
	graph2.addEdge(5, 6, 4);
	graph2.addEdge(7, 6, 2);
	graph2.addEdge(3, 7, 8);
	graph2.addEdge(4, 7, 9);
	graph2.dijkstra(0, 4);
	*/

	
	//Test 3 (Test for Prim)
	Graph graph3(7);
	graph3.addEdge(0, 1, 9);
	graph3.addEdge(1, 0, 9);
	graph3.addEdge(0, 3, 3);
	graph3.addEdge(3, 0, 3);
	graph3.addEdge(0, 6, 6);
	graph3.addEdge(6, 0, 6);
	graph3.addEdge(1, 2, 8);
	graph3.addEdge(2, 1, 8);
	graph3.addEdge(1, 3, 4);
	graph3.addEdge(3, 1, 4);
	graph3.addEdge(2, 3, 1);
	graph3.addEdge(3, 2, 1);
	graph3.addEdge(2, 4, 5);
	graph3.addEdge(4, 2, 5);
	graph3.addEdge(3, 4, 8);
	graph3.addEdge(4, 3, 8);
	graph3.addEdge(3, 6, 2);
	graph3.addEdge(6, 3, 2);
	graph3.addEdge(4, 5, 17);
	graph3.addEdge(5, 4, 17);
	graph3.addEdge(4, 6, 4);
	graph3.addEdge(6, 4, 4);
	graph3.addEdge(5, 6, 12);
	graph3.addEdge(6, 5, 12);
	graph3.prim(0)->display();

	system("PAUSE");
	return 0;
}