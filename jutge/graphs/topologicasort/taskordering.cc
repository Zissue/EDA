#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <map>

using namespace std;

using Vertex = int;
using Graph = vector<vector<Vertex>>;
using IV = vector<int>;
using SV = vector<string>;

int n, m;

void readGraph(Graph &G, map<string,int> &indices) {
	string x, y;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		G[indices[x]].push_back(indices[y]);
	}
}

list<Vertex> Topological_Sort(const Graph &G, const map<string,int> &indices, const map<int,string> &words) {

	int n = int(G.size());
	IV degree(n, 0);

	for (auto& adj: G)
		for (Vertex s: adj) 
			++degree[s];

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
	for (Vertex u = 0; u < n; u++) {
		if (degree[u] == 0) pq.push(u);
	}

	list<Vertex> L;
	while (not pq.empty()) {
		Vertex u = pq.top();		pq.pop();
		L.push_back(u);
		for (Vertex v: G[u]) {
			if (--degree[v] == 0) pq.push(v);
		}
	}

	return L;
}

void tempIndex(map<string,int> &indices) {
	string s;
	for (int i = 0; i < n; i++) {
	 	cin >> s;
	 	indices.insert({s, i});
	}
}

void updateIndex(map<string,int> &indices, map<int,string> &words) {
	int index = 0;
	for (auto &p: indices) {
		p.second = index;
		words.insert({index++, p.first});
	}
}

int main () {

	while (cin >> n) {

		map<string,int> indices; 		// Every word has a corresponding index from 0 to n-1
		map<int,string> words;

		tempIndex(indices);
		updateIndex(indices, words);

		cin >> m;

		Graph G(n);
		readGraph(G, indices);

		list<Vertex> TS = Topological_Sort(G, indices, words);

		if (TS.size() == n) {
			for (Vertex v: TS) {
				cout << words[v];
			}
		}
		else cout << "NO VALID ORDERING";
		cout << endl;
	}
}