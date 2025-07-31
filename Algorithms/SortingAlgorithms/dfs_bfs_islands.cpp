// DFS and BFS implementation for a 2D grid (Number of Islands problem)
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// DFS helper
void dfs(vector<vector<char>>& grid, int i, int j) {
    int m = grid.size(), n = grid[0].size();
    if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] != '1') return;
    grid[i][j] = '2'; // Mark visited
    dfs(grid, i+1, j);
    dfs(grid, i-1, j);
    dfs(grid, i, j+1);
    dfs(grid, i, j-1);
}

int numIslandsDFS(vector<vector<char>> grid) {
    int count = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == '1') {
                dfs(grid, i, j);
                ++count;
            }
        }
    }
    return count;
}

// BFS helper
void bfs(vector<vector<char>>& grid, int i, int j) {
    int m = grid.size(), n = grid[0].size();
    queue<pair<int, int>> q;
    q.push({i, j});
    grid[i][j] = '2'; // Mark visited
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (auto& d : dirs) {
            int nx = x + d[0], ny = y + d[1];
            if (nx >= 0 && ny >= 0 && nx < m && ny < n && grid[nx][ny] == '1') {
                grid[nx][ny] = '2';
                q.push({nx, ny});
            }
        }
    }
}

int numIslandsBFS(vector<vector<char>> grid) {
    int count = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == '1') {
                bfs(grid, i, j);
                ++count;
            }
        }
    }
    return count;
}

int main() {
    vector<vector<char>> grid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << "Number of islands (DFS): " << numIslandsDFS(grid) << endl;
    // Reset grid for BFS
    grid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << "Number of islands (BFS): " << numIslandsBFS(grid) << endl;
    return 0;
}
