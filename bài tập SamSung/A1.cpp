#include <bits/stdc++.h>
using namespace std;

bool isEulerian(vector<int> &degree) {
    for (int i = 0; i < degree.size(); i++) {
        if (degree[i] % 2 != 0) {
            return false;
        }
    }
    return true;
}

bool isHamiltonian(int edge, vector<vector<bool>> &adjMatrix) {
    vector<int> path;
    vector<bool> visited(edge, false);
    int pos = 0;
    path.push_back(pos);
    visited[pos] = true;
    while (true) {
        bool found = false;
        for (int i = 0; i < edge; i++) {
            if (adjMatrix[pos][i] && !visited[i]) {
                found = true;
                path.push_back(i);
                visited[i] = true;
                pos = i;
                break;
            }
        }
        if (!found)
            break;
    }
    return path.size() == edge + 1;
}

int main() {
    int edge;
    cin >> edge;
    vector<int> degree(edge, 0);
    vector<vector<bool>> adjMatrix(edge, vector<bool>(edge, false));

    for (int i = 0; i < edge; i++) {
        int u, v;
        cin >> u >> v;
        degree[u]++;
        degree[v]++;
        adjMatrix[u][v] = adjMatrix[v][u] = true;
    }

    bool isEuler = isEulerian(degree);
    bool isHamilton = isHamiltonian(edge, adjMatrix);

    if (isEuler) {
        cout << "Eulerian ";
        if (isHamilton)
            cout << "and Hamiltonian" << endl;
        else
            cout << "but not Hamiltonian" << endl;
    } else {
        cout << "Not Eulerian" << endl;
    }

    return 0;
}
