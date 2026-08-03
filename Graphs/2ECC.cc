#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 3e5;

int timer;  // Time of entry in node
int scc;    // Number of strongly connected components
int id[MAX_N];
int low[MAX_N];  // Lowest ID in node's subtree in DFS tree
vector<int> neighbors[MAX_N];
vector<int> two_edge_components[MAX_N];
stack<int> st;  // Keeps track of the path in our DFS

void dfs(int node, int parent = -1) {
	id[node] = low[node] = ++timer;
	st.push(node);
	bool multiple_edges = false;

	for (int child : neighbors[node]) {
		if (child == parent && !multiple_edges) {
			multiple_edges = true;
			continue;
		}
		if (!id[child]) {
			dfs(child, node);
			low[node] = min(low[node], low[child]);
		} else {
			low[node] = min(low[node], id[child]);
		}
	}

	if (low[node] == id[node]) {
		while (st.top() != node) {
			two_edge_components[scc].push_back(st.top());
			st.pop();
		}
		two_edge_components[scc++].push_back(st.top());
		st.pop();
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		neighbors[x].push_back(y);
		neighbors[y].push_back(x);
	}

	for (int node = 0; node < n; node++) {
		if (id[node] == 0) { dfs(node); }
	}

	cout << scc << '\n';
	for (int i = 0; i < scc; i++) {
		cout << two_edge_components[i].size() << ' ';
		for (int node : two_edge_components[i]) { cout << node << ' '; }
		cout << '\n';
	}
}
