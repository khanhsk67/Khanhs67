#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Dijkstra {
public:
    int V;
    vector<vector<pair<int, int>>> adjList;
    vector<int> sources;

    Dijkstra(int vertices, const vector<int>& src) : V(vertices), adjList(V), sources(src) {
        // Tạo đỉnh phụ và các cạnh có trọng số 0 nối tới mỗi đỉnh nguồn
        int auxiliaryVertex = V;
        for (int source : sources) {
            addEdge(auxiliaryVertex, source, 0);
        }
        V++;
    }

    void addEdge(int u, int v, int w) {
        adjList[u].emplace_back(v, w);
    }

    vector<int> shortestPathsFromSource(int source) {
        vector<int> shortestPaths(V, numeric_limits<int>::max());
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        shortestPaths[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const auto& edge : adjList[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (shortestPaths[u] != numeric_limits<int>::max() &&
                    shortestPaths[u] + weight < shortestPaths[v]) {
                    shortestPaths[v] = shortestPaths[u] + weight;
                    pq.push({shortestPaths[v], v});
                }
            }
        }

        return shortestPaths;
    }

    vector<vector<int>> getShortestPaths() {
        vector<vector<int>> paths;
        for (int source : sources) {
            paths.push_back(shortestPathsFromSource(source));
        }
        return paths;
    }
};

int main() {
    int ver = 5;
    vector<int> b = {0, 2}; // Đỉnh nguồn

    Dijkstra a(ver, b);

    a.addEdge(0, 1, 10);
    a.addEdge(0, 3, 5);
    a.addEdge(1, 2, 1);
    a.addEdge(2, 3, 2);
    a.addEdge(3, 1, 3);
    a.addEdge(3, 4, 2);
    a.addEdge(4, 0, 7);

    vector<vector<int>> shortestPaths = a.getShortestPaths();

    for (int i = 0; i < shortestPaths.size(); ++i) {
        cout << "Shortest paths from source " << b[i] << " to all vertices:\n";
        for (int j = 0; j < shortestPaths[i].size(); ++j) {
            cout << "Source " << b[i] << " to Vertex " << j << ": " << shortestPaths[i][j] << "\n";
        }
        cout << "\n";
    }

    return 0;
}
