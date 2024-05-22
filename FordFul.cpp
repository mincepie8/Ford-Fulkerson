#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

const int INF = 1e6;
int timer = 1;
struct Edge{
	int flow;
	int cap;
};
class Graph {
public:
	vector<vector<Edge>> graph;
	vector<int> visited;
	vector<int> edges;
	int s, t, max_flow = 0;
	Graph(int v_num) {
		graph.resize(v_num, vector<Edge>(v_num));
		visited.resize(v_num);
		edges.resize(v_num * v_num);
		fill(visited.begin(), visited.end(), 0);
	}
	void fill_graph() {
		ifstream in;
		in.open("test.txt");
		int a, b, cap;
		while (in >> a && in >> b && in >> cap) {
			a--;
			b--;
			graph[a][b] = { 0, cap };
			graph[b][a] = { 0, 0 };
		}
	}
	int dfs(int u, int cmin) {
		if (u == t) {
			return cmin;
		}
		visited[u] = timer;
		for (int v = 0; v < graph[u].size(); v++) {
			if (graph[u][v].cap - graph[u][v].flow == 0) {
				continue;
			}
			if (visited[v] == timer) {
				continue;
			}
			int delta = dfs(v, min(cmin, graph[u][v].cap - graph[u][v].flow));
			if (delta > 0) {
				graph[u][v].flow += delta;
				graph[v][u].flow -= delta;
				max_flow += delta;
				return delta;
			}
		}
		return 0;
	}

};
int main() {
	int v_num;
	cout << "Enter the num of vertex: ";
	cin >> v_num;
	Graph A(v_num);
	A.fill_graph();
	cout << "Enter the source: ";
	cin >> A.s;
	A.s--;
	cout << "Enter the sink: ";
	cin >> A.t;
	A.t--;
	while (A.dfs(A.s, INF)) {
		timer++;
	}
	int result = 0;
	for (int v = 0; v < A.graph.size(); v++) {
		result += A.graph[A.s][v].flow;
	}
	cout << result;
	return 0;
}
