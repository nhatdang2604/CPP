#include "Graph.h"

int min(int a, int b) {
	return (a < b) ? a : b;
}

void createGraph(Graph& graph, int numberOfVertex) {
	graph.numberOfVertex = numberOfVertex;
	graph.map = new int*[numberOfVertex];
	for (int i = 0; i < graph.numberOfVertex; ++i) {
		graph.map[i] = new int[numberOfVertex];
		memset(graph.map[i], INF, graph.numberOfVertex * sizeof(int));
		graph.map[i][i] = 0;
	}
}

void addEdge(Graph& graph, int src, int dst, int weight) {
	graph.map[src][dst] = weight;
}

void release(Graph& graph, int**&dp) {
	for (int i = 0; i < graph.numberOfVertex; ++i) {
		delete[]graph.map[i];
		delete[]dp[i];
	}
	delete[]graph.map;
	delete[]dp;
}

void init(Graph& graph, int **&dp) {
	dp = new int*[graph.numberOfVertex];
	for (int i = 0; i < graph.numberOfVertex; ++i) {
		dp[i] = new int[graph.numberOfVertex];
		memcpy(dp[i], graph.map[i], graph.numberOfVertex * sizeof(int));
	}
}

void FloydWarshall(Graph graph, int **&dp) {
	for (int k = 0; k < graph.numberOfVertex; ++k) {
		for (int i = 0; i < graph.numberOfVertex; ++i) {
			for (int j = 0; j < graph.numberOfVertex; ++j) {
				dp[i][j] = min(dp[i][k] + dp[k][j], dp[i][j]);
			}
		}
	}
}

void trace(Graph graph, int src, int dst, int **dp) {
	if (dp[src][dst] >= INF) {
		cout << "Khong ton tai duong di tu dinh " << src << " toi " << dst << " !\n";
		return;
	}
	vector<int> trace;
	int next = dst;
	while (next != src) {
		trace.push_back(next);
		for (int i = 0; i < graph.numberOfVertex; ++i) {
			if (dp[src][next] == dp[src][i] + graph.map[i][next]) {
				next = i;
				break;
			}
		}
	}
	cout << "Duong di tu dinh " << src << " toi " << dst << " la:\n";
	cout << src;
	for (int i = trace.size() - 1; i >= 0; --i) {
		cout << " -> " << trace[i];
	}
	cout << endl;
}

