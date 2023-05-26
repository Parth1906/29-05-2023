#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

vector<int> adj[100001]; // adjacency list to represent tree
int visited[100001]; // array to keep track of visited nodes

void dfs(int u) {
    stack<int> stk;
    stk.push(u);
    while (!stk.empty()) {
        int v = stk.top();
        stk.pop();
        if (!visited[v]) {
            visited[v] = 1;
            #pragma omp parallel for
            for (int i = 0; i < adj[v].size(); i++) {
                int w = adj[v][i];
                if (!visited[w]) {
                    stk.push(w);
                }
            }
        }
    }
}

int main() {
    int n, m, root;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;
    cout << "Enter the edges: " << endl;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout << "Enter the root node: ";
    cin >> root;
    #pragma omp parallel for
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }
    dfs(root);
    cout << "Visited nodes: ";
    for (int i = 1; i <= n; i++) {
        if (visited[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}