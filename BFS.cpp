#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

const int MAXN = 100005;

vector<int> adj[MAXN];
bool visited[MAXN];

void bfs(int u) {
    queue<int> q;
    q.push(u);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (!visited[v]) {
            visited[v] = true;

            // Process node v
            cout << v << " ";

            // Add unvisited neighbors to the queue
            #pragma omp parallel for
            for (int i = 0; i < adj[v].size(); i++) {
                int w = adj[v][i];
                if (!visited[w]) {
                    q.push(w);
                }
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    #pragma omp parallel for
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            bfs(i);
        }
    }

    return 0;
}
