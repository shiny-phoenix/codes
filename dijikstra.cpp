#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

int main() {
    cout<<"no. of vertices, edges, starting vertex :";
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<pair<int, int>>> adj(n+1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<int> dist(n+1, INF);
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int w = neighbor.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest path from source " << s << " to all other vertices:\n";
    for (int i = 0; i < n; i++) {
        cout << i << ": " << dist[i] << "\n";
    }

    vector<vector<int>> dp(n+1, vector<int>(n+1, INF));
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
    }

    for (int u = 0; u < n; u++) {
        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int w = neighbor.second;

            dp[u][v] = w;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }

    cout << "\nAll pairs shortest path:\n";
    for (int i = 0; i < n; i++) {
        cout<<i<<" : ";
        for (int j = 0; j < n; j++) {
            if (dp[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << dp[i][j] << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}
