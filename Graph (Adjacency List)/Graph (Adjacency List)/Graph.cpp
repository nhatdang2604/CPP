#include "Graph.h"

Graph::~Graph(){
	if (this->vertex) delete[]vertex;
	if (this->minimumSpanningTree) delete minimumSpanningTree;
}

Graph::Graph(const int& numberOfVertex) {
	this->numberOfVertex = numberOfVertex;
	this->vertex = new Vertex[numberOfVertex];
}

void Graph::_addEdge(int src, int dst, int weight) {
	this->vertex[src].adjacencyEdge.push_back(make_pair(weight, dst));
}

void Graph::addEdge(int src, int dst, int weight) {
	_addEdge(src, dst, weight);
}

int Graph::_getNumberOfVertex() {
	return numberOfVertex;
}

int Graph::getNumberOfVertex() {
	return _getNumberOfVertex();
}

void Graph::_dijkstra(int src, int dst) {

	//Tao 1 priority queue cho pair<int, int>, dang min heap
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priorityQueue;

	//Dua 1 phan tu dummy vao priority queue
	priorityQueue.push(make_pair(0, src));

	//distance[i] la tong chi phi khi di tu src -> i
	int* distance = new int[this->numberOfVertex];

	//set toan bo distace[i] = INF
	memset(distance, INF, this->numberOfVertex * sizeof(int));

	//chi phi di tu src -> src bang 0
	distance[src] = 0;
	pair<int, int> u;

	//Thuc hien den khi priority queue rong
	while (!priorityQueue.empty()) {

		//Lay ra phan tu co trong so nho nhat, trong cac dinh da loang ra
		u = priorityQueue.top();
		priorityQueue.pop();

		//Duyet toan bo cac dinh v ke voi u
		for (pair<int, int> v : this->vertex[u.second].adjacencyEdge) {

			//Neu khoang cach tu src -> cac dinh v hien tai chua toi uu => tiep tuc cap nhat
			if (distance[v.second] > distance[u.second] + v.first) {
				distance[v.second] = distance[u.second] + v.first;

				//Sau khi cap nhat, dua cac gia tri da cap nhat vao priority queue
				priorityQueue.push(make_pair(distance[v.second], v.second));
			}
		}
	}

	//Neu khong ton tai duong di => thoat khoi chuong trinh
	if (distance[dst] >= INF) {
		cout << "Khong ton tai duong di tu " << char('A' + src) << " den " << char('A' + dst);
		delete[]distance;
		return;
	}

	//Neu co => tien hanh truy vet
	vector<int> path;
	int trace = dst;
	while (trace != src) {

		//Tim dinh i sao cho thoa man 2 dieu kien:
		//	1) Co mot cung noi tu i -> trace
		//	2) Ton tai duong di tu src -> i
		for (int i = 0; i < this->numberOfVertex; ++i) {

			// Trong so cua cung noi tu i.second -> trace
			int i_to_trace = -1;	

			//Kiem tra dieu kien 1)	=> Neu thoa man, luu trong so vao i_to_trace
			for (pair<int, int> j : this->vertex[i].adjacencyEdge) {
				if (j.second == trace) {
					i_to_trace = j.first;
					break;
				}
			}

			//Neu dieu kien 1 thoa man => Kiem tra dieu kien 2
			if (i_to_trace != -1) {

				//Neu dieu kien 2 thoa man => i chinh la 1 dinh trung gian
				//	=> Luu lai trace, update trace = i
				//		=> Tiep tuc thuc hien cho den khi trace = src
				if (distance[trace] == distance[i] + i_to_trace) {
					path.push_back(trace);
					trace = i;
					break;
				}
			}

		}
	}

	//In ra ket qua
	cout << "Duong di ngan nhat tu " << char('A' + src) << " toi " << char('A' + dst) << " la:\n";
	cout << char('A' + src);
	for (int i = path.size() - 1; i >= 0; --i) {
		cout << "->" << char('A' + path[i]);
	}
	cout << endl;
	cout << "Tong chi phi: " << distance[dst] << endl;

	//Giai phong mang distance
	delete[]distance;
}


void Graph::dijkstra(int src, int dst) {
	this->_dijkstra(src, dst);
}

void Graph::_display() {
	for (int i = 0; i < this->numberOfVertex; ++i) {
		cout << char('A' + i);
		for (pair<int, int> j : this->vertex[i].adjacencyEdge) {
			cout << " -> (" << j.first << ", " << char('A' + j.second) << ")";
		}
		cout << endl;
	}
}

void Graph::display() {
	this->_display();
}

Graph* Graph::_prim(const int& startVertex) {

	//release if there is already a minimum spanning tree
	if (this->minimumSpanningTree) {
		delete this->minimumSpanningTree;
		this->minimumSpanningTree = nullptr;
	}

	//check[i] = true if the i-th vertex has been in the minimum spanning tree
	bool* check = new bool[this->numberOfVertex];
	memset(check, false, this->numberOfVertex * sizeof(bool));
	
	//parent[u] = v => from vertex v to u
	int* parent = new int[this->numberOfVertex];
	memset(parent, -1, this->numberOfVertex * sizeof(int));

	//weight[u] = a => going from vertex parent[u] to u costs a
	int* weight = new int[this->numberOfVertex];
	memset(weight, INF, this->numberOfVertex * sizeof(int));

	//the return answer
	Graph* minimumSpanTree = new Graph(this->numberOfVertex);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priorityQueue;
	priorityQueue.push(make_pair(0, startVertex));
	
	//Init
	parent[startVertex] = startVertex;
	weight[startVertex] = 0;
	check[startVertex] = true;
	pair<int, int> chosenEdge;

	while (!priorityQueue.empty()) {
		chosenEdge = priorityQueue.top();
		priorityQueue.pop();
		check[chosenEdge.second] = true;

		for (pair<int, int> i : this->vertex[chosenEdge.second].adjacencyEdge) {
			if (!check[i.second] && weight[i.second] > i.first) {
				priorityQueue.push(i);
				weight[i.second] = i.first;
				parent[i.second] = chosenEdge.second;
			}
		}
	}
	for (int i = 1; i < this->numberOfVertex; ++i) {
		minimumSpanTree->addEdge(parent[i], i, weight[i]);
		minimumSpanTree->addEdge(i, parent[i], weight[i]);
	}

	delete[]parent;
	delete[]weight;
	delete[]check;
	return minimumSpanTree;
}

Graph* Graph::prim(const int& startVertex) {
	if (!this->minimumSpanningTree) this->minimumSpanningTree = this->_prim(startVertex);
	return minimumSpanningTree;
}