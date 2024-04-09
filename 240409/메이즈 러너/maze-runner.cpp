#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M, K;
struct Player {
	bool isExit = false;
	int x = 0, y = 0;
};
struct Info {
	int dist;
	int num;
};
int exitX, exitY;
Player player[11];
int map[11][11];

const int dx[] = { 1,-1,0,0 };
const int dy[] = { 0,0,1,-1 };

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int result = 0;
	int cnt = 0;
	cin >> N >> M >> K;
	cnt = M;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			cin >> map[i][j];
		}
	}
	for (int i = 1; i <= M; ++i) {
		cin >> player[i].x >> player[i].y;
		map[player[i].x][player[i].y] = 100 + i;
	}
	cin >> exitX >> exitY;
	map[exitX][exitY] = 100;
	for (int time = 0; time < K; ++time) {
		// 이동
		for (int i = 1; i <= M; ++i) {
			if (player[i].isExit) {
				continue;
			}
			int dist = abs(exitX - player[i].x) + abs(exitY - player[i].y);
			int dir = -1;
			for (int j = 0; j < 4; ++j) {
				int nx = player[i].x + dx[j];
				int ny = player[i].y + dy[j];
				if (nx <= 0 || ny <= 0 || nx > N || ny > N || (map[nx][ny] > 0 && map[nx][ny]< 100)) {
					continue;
				}
				int temp = abs(exitX - nx) + abs(exitY - ny);
				if (dist > temp) {
					dist = temp;
					dir = j;
				}
			}
			if (dir != -1) {
				map[player[i].x][player[i].y] = 0;
				player[i].x += dx[dir];
				player[i].y += dy[dir];
				++result;
				if (player[i].x == exitX && player[i].y == exitY) {
					player[i].isExit = true;
					--cnt;
				}
				else {
					map[player[i].x][player[i].y] = 100 + i;
				}
			}
		}
		// 생존자 검색
		if (cnt == 0) {
			break;
		}
		// 검색
		int x = 0, y = 0, size = 0;
		bool findExit = false;
		bool findPlayer = false;
		for (int len = 2; len <= N; ++len) {
			for (int i = 1; i + len <= N; ++i) {
				for (int j = 1; j + len <= N; ++j) {
					findExit = false;
					findPlayer = false;
					for (int k = 0; k < len; ++k) {
						for (int l = 0; l < len; ++l) {
							int nx = i + k;
							int ny = j + l;
							if (nx <= 0 || ny <= 0 || nx > N || ny > N) {
								continue;
							}
							if (map[nx][ny] > 100) {
								findPlayer = true;
							}
							if (map[nx][ny] == 100) {
								findExit = true;
							}
						}
					}
					if (findExit && findPlayer) {
						x = i;
						y = j;
						size = len;
						break;
					}
				}
				if (findExit && findPlayer) {
					break;
				}
			}
			if (findExit && findPlayer) {
				break;
			}
		}
		// 회전
		int tempMap[11][11];
		memset(tempMap, 0, sizeof(tempMap));
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				tempMap[j + x][size - 1 - i + y] = map[i + x][j + y];
			}
		}
		for (int i = x; i < x + size; ++i) {
			for (int j = y; j < y + size; ++j) {
				map[i][j] = tempMap[i][j];
				if (map[i][j] > 0 && map[i][j] < 100) {
					--map[i][j];
				}
				if (map[i][j] > 100) {
					player[map[i][j] - 100].x = i;
					player[map[i][j] - 100].y = j;
				}
				if (map[i][j] == 100) {
					exitX = i;
					exitY = j;
				}
			}
		}
	}
	cout << result << "\n";
	cout << exitX << " " << exitY;
	return 0;
}