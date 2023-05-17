#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
typedef pair<int, pair<int, int>> pairInt;


class MST
{
    int n, m;
    int adjmatrix[100][100];
    int id[100];
    bool visited[100];
    vector<pair<int, pair<int, int>>> p;

public:
    MST()
    {
        for (int i = 0; i < 100; i++)
            id[i] = i;
        n = m = 0;
        for (int i = 0; i < 100; i++)
            for (int j = 0; j < 100; j++)
                adjmatrix[i][j] = 0;
    }
    void input();
    void Prims();
    int root(int);
    void Union(int, int);
    void Krushkals();
};

void MST ::Union(int x, int y)
{
    id[root(x)] = id[root(y)];
}

int MST ::root(int x)
{
    if (id[x] == x)
        return x;
    else
        return root(id[x]);
}

void MST ::input()
{
    cout << "Enter no of nodes and edges : ";
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cout << "Enter the vertices having edges and its weight : ";
        int x, y, weight;
        cin >> x >> y >> weight;
        p.push_back(make_pair(weight, make_pair(x, y)));
        adjmatrix[x][y] = weight;
        adjmatrix[y][x] = weight;
    }
}

void MST ::Krushkals()
{
    long long krushkal_cost = 0;
    sort(p.begin(), p.end());
    cout << "Weight and edges selected :" << endl;
    for (int i = 0; i < n - 1; i++)
    {
        if (root(p[i].s.f) != root(p[i].s.s))
        {
            cout << "Weight :  " << p[i].f << " Nodes : " << p[i].s.f << " " << p[i].s.s << endl;
            krushkal_cost += p[i].f;
            Union(p[i].s.f, p[i].s.s);
        }
    }
    cout << "Cost by krushkal is : " << krushkal_cost << endl;
}

void MST ::Prims()
{
    memset(visited, false, sizeof(visited));
    visited[0] = true;
    int prims_cost = 0;
    int i, j;
    for (int k = 0; k < n - 1; k++)
    {
        int min = INT_MAX;
        int start, end;
        for (i = 0; i < n; i++)
        {
            if (visited[i] == false)
                continue;
            for (j = 0; j < n; j++)
            {
                if (adjmatrix[i][j] == 0 || visited[j] == true)
                    continue;
                if (adjmatrix[i][j] < min)
                {
                    start = i;
                    end = j;
                    min = adjmatrix[i][j];
                }
            }
        }
        cout << "WEIGHT :  " << adjmatrix[start][end] << " NODES : " << start << " " << end << endl;
        prims_cost += adjmatrix[start][end];
        visited[start] = true;
        visited[end] = true;
    }
    cout << "COST BY PRIMS : " << prims_cost << endl;
}

int main()
{
    int in;
    MST t;
    do
    {
        cout << "1. Enter graph input " << endl;
        cout << "2. Kruskal " << endl;
        cout << "3. Prims" << endl;
        cout << "4. Exit" << endl;
        cin >> in;
        switch (in)
        {
        case 1:
            t.input();
            break;
        case 2:
            t.Krushkals();
            break;
        case 3:
            t.Prims();
            break;
        default:
            return 0;
        }
    } while (in);
}
