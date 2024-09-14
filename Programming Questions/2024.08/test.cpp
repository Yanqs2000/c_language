#include <iostream>
#include <vector>

using namespace std;

void paintBlack(vector<vector<bool>>& grid, int x, int y) {
    grid[x-1][y-1] = true;
}

void findLeftWhite(const vector<vector<bool>>& grid, int x, int y) {
    for (int j = y - 2; j >= 0; --j) {
        if (!grid[x-1][j]) {
            cout << x << " " << j + 1 << endl;
            return;
        }
    }
    cout << -1 << endl;
}

void findRightWhite(const vector<vector<bool>>& grid, int x, int y) {
    for (int j = y; j < grid[0].size(); ++j) {
        if (!grid[x-1][j]) {
            cout << x << " " << j + 1 << endl;
            return;
        }
    }
    cout << -1 << endl;
}

void findUpWhite(const vector<vector<bool>>& grid, int x, int y) {
    for (int i = x - 2; i >= 0; --i) {
        if (!grid[i][y-1]) {
            cout << i + 1 << " " << y << endl;
            return;
        }
    }
    cout << -1 << endl;
}

void findDownWhite(const vector<vector<bool>>& grid, int x, int y) {
    for (int i = x; i < grid.size(); ++i) {
        if (!grid[i][y-1]) {
            cout << i + 1 << " " << y << endl;
            return;
        }
    }
    cout << -1 << endl;
}

int main() {
    int m, n, k;
    cin >> m >> n >> k;
    vector<vector<bool>> grid(m, vector<bool>(n, false));

    for (int i = 0; i < k; ++i) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'c') {
            paintBlack(grid, x, y);
        } else if (op == 'l') {
            findLeftWhite(grid, x, y);
        } else if (op == 'r') {
            findRightWhite(grid, x, y);
        } else if (op == 'u') {
            findUpWhite(grid, x, y);
        } else if (op == 'd') {
            findDownWhite(grid, x, y);
        }
    }

    return 0;
}




