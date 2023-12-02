#include <iostream>
#include <vector>

using namespace std;

bool is_connected(vector<vector<int>> &graph, int src) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> queue;

    visited[src] = true;
    queue.push_back(src);

    while (!queue.empty()) {
        int u = queue.front();
        queue.erase(queue.begin());

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] > 0 && !visited[v]) {
                visited[v] = true;
                queue.push_back(v);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

bool has_euler_cycle(vector<vector<int>> &graph) {
    int n = graph.size();
    vector<int> in_degree(n, 0);
    vector<int> out_degree(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out_degree[i] += graph[i][j];
            in_degree[j] += graph[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] != out_degree[i]) {
            return false;
        }
    }
    return is_connected(graph, 0);
}
