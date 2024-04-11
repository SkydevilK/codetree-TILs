#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, M;

// 0 빈칸 1 베이스캠프 2 이동 불가 3 선점 베이스캠프
int map[16][16];

int dx[] = { -1,0,0,1 };
int dy[] = { 0,-1,1,0 };
bool isVisit[16][16] = {};
struct Customer {
	int x, y;
	bool isMove = false;
};
struct Path {
	int x, y;
	vector < pair<int, int>> path;
	int cnt = 0;
};
vector<pair<int, int>> stores(31);

vector<pair<int, int>> eraseMap;

vector<Customer> customer(31);
int x, y;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			cin >> map[i][j];
		}
	}
	for (int i = 1; i <= M; ++i) {
		cin >> stores[i].first >> stores[i].second;
	}
	int turn = 0;
	int count = M;
	while (1) {
		turn++;
		// 이동
		for (int i = 1; i <= M; ++i) {
			if (!customer[i].isMove)
				continue;
			queue<Path> q;
			q.push({ customer[i].x, customer[i].y });
			memset(isVisit, 0, sizeof(isVisit));
			isVisit[customer[i].x][customer[i].y] = true;
			while (!q.empty()) {
				Path cur = q.front(); q.pop();
				for (int dir = 0; dir < 4; ++dir) {
					int nx = cur.x + dx[dir];
					int ny = cur.y + dy[dir];
					if (nx <= 0 || ny <= 0 || nx > N || ny > N || map[nx][ny] == 2 || isVisit[nx][ny]) {
						continue;
					}
					if (nx == stores[i].first && ny == stores[i].second) {
						if (cur.path.size() == 0) {
							--count;
							eraseMap.push_back({ nx, ny });
							customer[i].isMove = false;
						}
						else {
							customer[i].x = cur.path[0].first;
							customer[i].y = cur.path[0].second;
						}
						q = {};
						break;
					}
					isVisit[nx][ny] = true;
					Path next;
					next.x = nx;
					next.y = ny;
					next.path = cur.path;
					next.path.push_back({ nx, ny });
					q.push(next);
				}
			}
		}
		// 도착
		if (count == 0) {
			cout << turn << "\n";
			break;
		}
		// 베이스 캠프 지정
		if (turn <= M) {
			queue<Path> q;
			q.push({ stores[turn].first, stores[turn].second });
			memset(isVisit, 0, sizeof(isVisit));
			isVisit[stores[turn].first][stores[turn].second] = true;
			int tempTurn = 987654231;
			while (!q.empty()) {
				Path cur = q.front(); q.pop();
				for (int dir = 0; dir < 4; ++dir) {
					int nx = cur.x + dx[dir];
					int ny = cur.y + dy[dir];
					if (nx <= 0 || ny <= 0 || nx > N || ny > N || map[nx][ny] >= 2 || isVisit[nx][ny]) {
						continue;
					}
					if (map[nx][ny] == 1) {
						if (cur.cnt < tempTurn) {
							tempTurn = cur.cnt;
							customer[turn].x = nx;
							customer[turn].y = ny;
							customer[turn].isMove = true;
						}
						else if (cur.cnt == tempTurn) {
							if (nx < customer[turn].x) {
								customer[turn].x = nx;
								customer[turn].y = ny;
							}
							else if (nx == customer[turn].x) {
								if (ny < customer[turn].y) {
									customer[turn].x = nx;
									customer[turn].y = ny;
								}
							}
						}
					}
					isVisit[nx][ny] = true;
					Path next;
					next.x = nx;
					next.y = ny;
					next.cnt = cur.cnt + 1;
					q.push(next);
				}
			}
			eraseMap.push_back({ customer[turn].x, customer[turn].y});
			map[customer[turn].x][customer[turn].y] = 3;
		}
		vector<pair<int, int>>::iterator iter = eraseMap.begin();
		while (iter != eraseMap.end()) {
			bool isCheck = false;
			for (int i = 1; i <= M; ++i) {
				if (!customer[i].isMove) {
					continue;
				}
				if (customer[i].x == (*iter).first && customer[i].y == (*iter).second) {
					isCheck = true;
					break;
				}
			}
			if (!isCheck) {
				map[(*iter).first][(*iter).second] = 2;
				iter = eraseMap.erase(iter);
			}
			else {
				++iter;
			}
		}
	}
}