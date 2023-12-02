#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void DFS(int u, vector<vector<int>> &adjList, vector<bool> &visited) {
    stack<int> stk;
    stk.push(u);
    visited[u] = true;

    while (!stk.empty()) {
        int v = stk.top();
        stk.pop();

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                stk.push(neighbor);
            }
        }
    }
}

bool isVertexConnected(vector<vector<int>> &adjList) {
    int n = adjList.size();
    vector<bool> visited(n, false);
    DFS(0, adjList, visited);
    for (bool v : visited) {
        if (!v) {
            return false;
        }
    }

    return true;
}

int main() {
    vector<vector<int>> adjList = {{1, 3}, {0, 2, 4}, {1}, {0, 4}, {1, 3}};
    cout << "Do thi co lien thong dinh hay khong? " << (isVertexConnected(adjList) ? "Co" : "Khong") << endl;

    return 0;
}
