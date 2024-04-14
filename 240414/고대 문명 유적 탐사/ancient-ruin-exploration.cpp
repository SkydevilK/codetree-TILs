#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int map[5][5];
int tempMap[5][5];
int tempMap2[5][5];
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,1,-1 };
int rotate(int sx, int sy, int rotateNum) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            tempMap[i][j] = map[i][j];
        }
    }

    for (int a = 0; a < rotateNum; ++a) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                tempMap2[j + sx][2 - i + sy] = tempMap[i + sx][j + sy];
            }
        }
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                tempMap[i + sx][j + sy] = tempMap2[i + sx][j + sy];
            }
        }
    }

    int result = 0;
    int temp;
    bool isVisit[5][5] = {};
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (isVisit[i][j]) {
                continue;
            }
            int cnt = 1;
            isVisit[i][j] = true;
            temp = tempMap[i][j];
            queue<pair<int, int>> q;
            q.push({ i, j });
            while (!q.empty()) {
                pair<int, int> cur = q.front(); q.pop();
                for (int d = 0; d < 4; ++d) {
                    int nx = cur.first + dx[d];
                    int ny = cur.second + dy[d];
                    if (nx < 0 || ny < 0 || nx >= 5 || ny >= 5 || tempMap[nx][ny] != temp || isVisit[nx][ny]) {
                        continue;
                    }
                    isVisit[nx][ny] = true;
                    q.push({ nx, ny });
                    ++cnt;
                }
            }
            if (cnt >= 3) {
                result += cnt;
            }
        }
    }
    return result;
}
int main() {
    int K, M;
    cin >> K >> M;
    queue<int> nextBlocks;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < M; ++i) {
        int temp;
        cin >> temp;
        nextBlocks.push(temp);
    }

    for (int turn = 0; turn < K; ++turn) {
        int result = 0;
        int maxResult = 0;
        int x, y, rotateNum;
        for (int a = 1; a <= 3; ++a) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int temp = rotate(j, i, a);
                    if (maxResult < temp) {
                        maxResult = temp;
                        x = j;
                        y = i;
                        rotateNum = a;
                    }
                }
            }
        }
        if (maxResult == 0) {
            break;
        }

        for (int a = 0; a < rotateNum; ++a) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    tempMap[j + x][2 - i + y] = map[i + x][j + y];
                }
            }
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    map[i + x][j + y] = tempMap[i + x][j + y];
                }
            }
        }
        int temp;
        bool isVisit[5][5] = {};
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (isVisit[i][j] || map[i][j] == 0) {
                    continue;
                }
                vector<pair<int, int>> paths;
                isVisit[i][j] = true;
                temp = map[i][j];
                queue<pair<int, int>> q;
                q.push({ i, j });
                paths.push_back({ i, j });
                while (!q.empty()) {
                    pair<int, int> cur = q.front(); q.pop();
                    for (int d = 0; d < 4; ++d) {
                        int nx = cur.first + dx[d];
                        int ny = cur.second + dy[d];
                        if (nx < 0 || ny < 0 || nx >= 5 || ny >= 5 || map[nx][ny] != temp || isVisit[nx][ny]) {
                            continue;
                        }
                        isVisit[nx][ny] = true;
                        q.push({ nx, ny });
                        paths.push_back({ nx, ny });
                    }
                }
                if (paths.size() >= 3) {
                    result += paths.size();
                    vector<pair<int, int>>::iterator iter = paths.begin();
                    while (iter != paths.end()) {
                        map[(*iter).first][(*iter).second] = 0;
                        ++iter;
                    }
                }
            }
        }
        for (int j = 0; j < 5; ++j) {
            for (int i = 4; i >= 0; --i) {
                if (map[i][j] == 0) {
                    map[i][j] = nextBlocks.front(); nextBlocks.pop();
                }
            }
        }

        bool isCheck = true;
        while (isCheck) {
            isCheck = false;
            memset(isVisit, 0, sizeof(isVisit));
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (isVisit[i][j] || map[i][j] == 0) {
                        continue;
                    }
                    vector<pair<int, int>> paths = {};
                    isVisit[i][j] = true;
                    temp = map[i][j];
                    queue<pair<int, int>> q;
                    q.push({ i, j });
                    paths.push_back({ i, j });
                    while (!q.empty()) {
                        pair<int, int> cur = q.front(); q.pop();
                        for (int d = 0; d < 4; ++d) {
                            int nx = cur.first + dx[d];
                            int ny = cur.second + dy[d];
                            if (nx < 0 || ny < 0 || nx >= 5 || ny >= 5 || map[nx][ny] != temp || isVisit[nx][ny]) {
                                continue;
                            }
                            isVisit[nx][ny] = true;
                            q.push({ nx, ny });
                            paths.push_back({ nx, ny });
                        }
                    }
                    if (paths.size() >= 3) {
                        isCheck = true;
                        result += paths.size();
                        vector<pair<int, int>>::iterator iter = paths.begin();
                        while (iter != paths.end()) {
                            map[(*iter).first][(*iter).second] = 0;
                            ++iter;
                        }
                    }
                }
            }
            for (int j = 0; j < 5; ++j) {
                for (int i = 4; i >= 0; --i) {
                    if (map[i][j] == 0) {
                        map[i][j] = nextBlocks.front(); nextBlocks.pop();
                    }
                }
            }
        }
        cout << result << " ";

    }

    return 0;
}