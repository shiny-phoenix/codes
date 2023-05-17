#include "bits/stdc++.h"
#define MAX 10
using namespace std;

class Graph
{
    int n, connected;
    int **adjMatrix;
    bool *visited;

public:
    Graph(int size = 10)
    {
        n = size;
        connected = 0;
        adjMatrix = new int *[n];
        visited = new bool[n];
        for (int i = 0; i < n; i++)
        {
            adjMatrix[i] = new int[n];
            visited[i] = false;
            for (int j = 0; j < n; j++)
                adjMatrix[i][j] = 0;
        }
    }

    void addEdge(int u, int v, int wt = 0);
    void removeEdge(int u, int v);
    void display();
    void clear_visited();
    void dfs(int vertex);
    void bfs(int vertex);
    bool is_connected();
};

/*
void make_set(int v, vector<int> &parent)
{
    parent[v] = v;
}
int find_set(int v, vector<int> &parent)
{
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v], parent);
}
void union_set(int a, int b, vector<int> &parent)
{
    a = find_set(a, parent);
    b = find_set(b, parent);
    if (a != b)
        parent[b] = a;
}
*/

void Graph ::addEdge(int u, int v, int wt)
{
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
}
void Graph ::removeEdge(int u, int v)
{
    adjMatrix[u][v] = 0;
    adjMatrix[v][u] = 0;
}

void Graph ::display()
{
    cout << "   Adjacency Matrix\n";
    cout << "    ";
    for (int i = 0; i < n; i++)
        cout << i << " ";
    cout << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << i << " : ";
        for (int j = 0; j < n; j++)
            cout << adjMatrix[i][j] << " ";
        cout << "\n";
    }
}

void Graph ::clear_visited()
{
    for (int i = 0; i < n; i++)
        visited[i] = false;
    return;
}

void Graph ::dfs(int vertex)
{
    visited[vertex] = true;
    connected++;
    cout << vertex << " ";
    for (int i = 0; i < n; i++)
        if (adjMatrix[vertex][i] == 1 and visited[i] == false)
            dfs(i);
    return;
}

void Graph ::bfs(int vertex)
{
    queue<int> q;
    q.push(vertex);
    visited[vertex] = true;

    while (!q.empty())
    {
        int curr_vertex = q.front();
        q.pop();
        cout << curr_vertex << " ";
        for (int i = 0; i < n; i++)
            if (adjMatrix[curr_vertex][i] == 1 and visited[i] == false)
                visited[i] = true, q.push(i);
    }
    return;
}

bool Graph ::is_connected()
{
    clear_visited();
    connected = 0;
    dfs(0);
    if (connected == n)
        return true;
    int count = 1;
    for (int i = 1; i < n; i++)
        if (visited[i] == false)
            dfs(i), count++;
    cout << "Total Connected components : " << count << "\n";
    return false;
}

int main()
{

    int n;
    cout << "Enter the number of nodes : ";
    cin >> n;
    Graph graph(n);

    while (true)
    {
        int choice;
        cout << "\n    1. Add Edge\n    2. Delete Edge\n"
             << "    3. Display Graph\n    4. DFS\n     5. BFS\n     6. Check if the Graph is Connected\n     7. Enter the Edges\n     8. Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int u, v;
            cout << "     Enter first node : ";
            cin >> u;
            cout << "     Enter second node : ";
            cin >> v;
            graph.addEdge(u, v);
            break;
        }
        case 2:
        {
            int u, v;
            cout << "     Enter first node : ";
            cin >> u;
            cout << "     Enter second node : ";
            cin >> v;
            graph.removeEdge(u, v);
            break;
        }
        case 3:
        {
            graph.display();
            break;
        }

        case 4:
        {
            int vertex;
            cout << "Enter the root vertex : ";
            cin >> vertex;
            graph.clear_visited();
            graph.dfs(vertex);
            cout << "\n";
            break;
        }
        case 5:
        {
            int vertex;
            cout << "Enter the root vertex : ";
            cin >> vertex;
            graph.clear_visited();
            graph.bfs(vertex);
            cout << "\n";
            break;
        }
        case 6:
        {
            if (graph.is_connected())
                cout << "The graph is Connected!\n";
            else
                cout << "The graph is NOT Connected!\n";
            break;
        }
        case 7:
            int k;
            cout << "Number of Edges : ";
            cin >> k;
            while (k--)
            {
                int u, v, wt;
                cin >> u >> v >> wt;
                graph.addEdge(u, v, wt);
            }
            break;

        default:
            break;
        }
    }
}