#include <bits/stdc++.h>
#include <vector>
#include <queue>

using namespace std;

const int ROWS = 6;
const int COLS = 6;

// Structure to represent a cell in the grid
struct Cell {
    int row;
    int col;
};

// Function to check if the given cell is within the bounds of the grid
bool isValidCell(int row, int col) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

// Function to find the shortest path from start to end using BFS
vector<Cell> findShortestPath(vector<vector<int>>& grid, Cell start, Cell end) {
    vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));
    vector<vector<Cell>> parent(ROWS, vector<Cell>(COLS, {-1, -1}));

    queue<Cell> q;
    q.push(start);
    visited[start.row][start.col] = true;

    int dx[] = {-1, 0, 1, 0}; 
    int dy[] = {0, 1, 0, -1}; 

    while (!q.empty()) {
        Cell current = q.front();
        q.pop();

        if (current.row == end.row && current.col == end.col) {
         
            vector<Cell> path;
            Cell cell = end;
            while (cell.row != -1 && cell.col != -1) {
                path.push_back(cell);
                cell = parent[cell.row][cell.col];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 4; i++) {
            int newRow = current.row + dx[i];
            int newCol = current.col + dy[i];

            if (isValidCell(newRow, newCol) && !visited[newRow][newCol] && grid[newRow][newCol] == 0) {
                q.push({newRow, newCol});
                visited[newRow][newCol] = true;
                parent[newRow][newCol] = current;
            }
        }
    }

    // No path found
    return vector<Cell>();
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 1, 0,0},
        {0, 1, 0, 1, 0,1},
        {0, 1, 0, 0, 0,1},
        {0, 1, 1, 1, 0,1},
        {0, 0, 1, 0, 0,1},
        {0, 0, 0, 1, 0,0},
     
        
    };

    Cell start = {3,2};  // Starting cell
    Cell end = {ROWS - 1, COLS - 1};  // Destination cell

    // Find the shortest path using BFS
    vector<Cell> path = findShortestPath(grid, start, end);

    cout<<".............Tower Defense Game..........."<<endl<<endl;
    // Mark the path on the grid
    for (Cell cell : path) {
        grid[cell.row][cell.col] = 42;  
    }
    cout<<"The player's location is "<<start.row<<","<<start.col<<endl;
    cout<<"The enemy's location is "<<end.row<<","<<end.col<<endl;
    if(path.size()==0)cout<<"The player is safe from enemy "<<endl;
    else cout << "The enemy has a path to the player's tower " << endl;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if(row==start.row and col==start.col)cout<<"\033[32mP\033[0m"<<" ";
            else if(row==end.row and col==end.col)cout<<"\033[31mE\033[0m"<<" ";
            else if(grid[row][col]==42)cout<<"\033[36m*\033[0m"<<" ";
            else cout << grid[row][col] << " ";
        }
        cout << endl;
    }
    cout<<endl<<endl;
    return 0;
}