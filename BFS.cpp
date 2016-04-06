const int maxN = 1000, maxM = 1000;
int arr[maxN][maxM], n,m,
    dx[] = {0, 0, -1, 1},
    dy[] = {1, -1, 0, 0};

//i, j - starting position in the array

void bfs(int i, int j) {
    queue < pii > q;
    q.push({i, j});
    arr[i][j] = 1;
    while (!q.empty()) {
        int x = q.front().F,
            y = q.front().S;
        q.pop();
        for (int l = 0; l<4; l++) {
            int xx = x + dx[l],
                yy = y + dy[l];
            if (xx<1||xx>n||yy<1||yy>m) continue; // OUT OF BOUNDS		
            if (arr[xx][yy] == 0) {   //0 - can move, other number - cell has already been used
                arr[xx][yy] = arr[x][y] + 1;
                q.push({xx, yy});
            } 
        }
    }
}