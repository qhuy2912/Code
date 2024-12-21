#include<bits/stdc++.h>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Node {
    int x, y, g, h; 
    Node(int _x, int _y, int _g, int _h) : x(_x), y(_y), g(_g), h(_h) {}
};

struct SoSanh {
    bool operator()(const Node& a, const Node& b) const {
        return (a.g + a.h) > (b.g + b.h);
    }
};

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}


bool HopLe(int x, int y, const vector<vector<int> >& grid, bool visited[][100]) {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] == 0 && !visited[x][y];
}


bool ThuatToan(vector<vector<int> >& grid, int startX, int startY, int goalX, int goalY) {
    priority_queue<Node, vector<Node>, SoSanh> openSet; 
    stack<Node> DFSstack;                               
    bool visited[100][100];                             
    memset(visited, 0, sizeof(visited));

    openSet.push(Node(startX, startY, 0, heuristic(startX, startY, goalX, goalY)));

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        int x = current.x;
        int y = current.y;

        if (x == goalX && y == goalY) {
            cout << "Tim thay muc tieu tai (" << goalX << ", " << goalY << ") voi chi phi " << current.g << endl;
            return true;
        }

        if (visited[x][y]) continue;
        visited[x][y] = true;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (HopLe(nx, ny, grid, visited)) {
                int g = current.g + 1;
                int h = heuristic(nx, ny, goalX, goalY);
                DFSstack.push(Node(nx, ny, g, h)); 
                openSet.push(Node(nx, ny, g, h));
            }
        }

        while (!DFSstack.empty()) {
            Node dfsNode = DFSstack.top();
            DFSstack.pop();

            if (HopLe(dfsNode.x, dfsNode.y, grid, visited)) {
openSet.push(Node(dfsNode.x, dfsNode.y, dfsNode.g, dfsNode.h));
            }
        }
    }

    cout << "Khong tim thay duong di den muc tieu." << endl;
    return false;
}

int main() {
    int rows, cols;
    cout << "Nhap so hang va so cot cua luoi: ";
    cin >> rows >> cols;

    vector<vector<int> > grid(rows, vector<int>(cols));
    cout << "Nhap luoi (0 = duong di, 1 = vat can): " << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> grid[i][j];
        }
    }

    int startX, startY, goalX, goalY;
    cout << "Nhap toa do diem bat dau (x, y): ";
    cin >> startX >> startY;
    cout << "Nhap toa do diem muc tieu (x, y): ";
    cin >> goalX >> goalY;

    if (ThuatToan(grid, startX, startY, goalX, goalY)) {
        cout << "Duong di ngan nhat da duoc tim thay!" << endl;
    } else {
        cout << "Khong tim thay duong di!" << endl;
    }

    return 0;
}

