#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, M, K;

struct Tower {
	int x, y;
	int power;
	int attackTurn = 0;
};
Tower map[10][10];
struct Path {
	int x, y;
	vector<pair<int, int>> path;
};
// 우/하/좌/상
int dx[] = {0,1,0,-1, 1, 1, -1, -1};
int dy[] = {1,0,-1,0, 1, -1, 1, -1};
bool compareWeak(Tower& t1, Tower& t2) {
	if (t1.power == t2.power) {
		if (t1.attackTurn == t2.attackTurn) {
			if (t1.x + t1.y == t2.x + t2.y) {
				return t1.y > t2.y;
			}
			else {
				return (t1.x + t1.y) > (t2.x + t2.y);
			}
		}
		else {
			return t1.attackTurn > t2.attackTurn;
		}
	}
	else {
		return t1.power < t2.power;
	}
}

bool compareStrong(Tower& t1, Tower& t2) {
	if (t1.power == t2.power) {
		if (t1.attackTurn == t2.attackTurn) {
			if (t1.x + t1.y == t2.x + t2.y) {
				return t1.y < t2.y;
			}
			else {
				return (t1.x + t1.y) < (t2.x + t2.y);
			}
		}
		else {
			return t1.attackTurn < t2.attackTurn;
		}
	}
	else {
		return t1.power > t2.power;
	}
}
vector<Tower> v1;
vector<Tower> v2;
bool isVisit[10][10];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	std::cout.tie(nullptr);
	// 입력
	cin >> N >> M >> K;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> map[i][j].power;
			map[i][j].x = i;
			map[i][j].y = j;
			map[i][j].attackTurn = 0;
		}
	}

	for (int turn = 1; turn <= K; ++turn) {
		v1 = {};
		v2 = {};
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				if (map[i][j].power > 0) {
					v1.push_back(map[i][j]);
					v2.push_back(map[i][j]);
				}
			}
		}
		if (v1.size() <= 1) {
			break;
		}
		// 공격자 선정
		// 공격자의 공격
		sort(v1.begin(), v1.end(), compareWeak);

		// 방어자 선정
		sort(v2.begin(), v2.end(), compareStrong);
		map[v1[0].x][v1[0].y].power += (N + M);
		map[v1[0].x][v1[0].y].attackTurn = turn;
		bool isRazer = false;
		vector<pair<int, int>> findPath = {};
		// 레이저 공격
		queue<Path> q;
		memset(isVisit, 0, sizeof(isVisit));
		isVisit[v1[0].x][v1[0].y] = true;
		q.push({ v1[0].x, v1[0].y});
		while (!q.empty()) {
			Path cur = q.front(); q.pop();
			for (int dir = 0; dir < 4; ++dir) {
				int nx = cur.x + dx[dir];
				int ny = cur.y + dy[dir];
				if (nx == N) {
					nx = 0;
				}
				if (ny == N) {
					ny = 0;
				}
				if (nx == -1) {
					nx = N - 1;
				}
				if (ny == -1) {
					ny = N - 1;
				}
				if (isVisit[nx][ny] || (map[nx][ny].power == 0)) {
					continue;
				}
				if (nx == v2[0].x && ny == v2[0].y) {
					isRazer = true;
					findPath = cur.path;
					findPath.push_back({ nx, ny });
					q = {};
					break;
				}
				Path next;
				next.x = nx;
				next.y = ny;
				next.path = cur.path;
				next.path.push_back({ nx, ny });
				isVisit[nx][ny] = true;
				q.push(next);
			}
		}
		memset(isVisit, 0, sizeof(isVisit));
		if (isRazer) {
			for (int i = 0; i < findPath.size() - 1; ++i) {
				isVisit[findPath[i].first][findPath[i].second] = true;
				map[findPath[i].first][findPath[i].second].power -= (map[v1[0].x][v1[0].y].power / 2);
				if (map[findPath[i].first][findPath[i].second].power < 0) {
					map[findPath[i].first][findPath[i].second].power = 0;
				}
			}
			map[findPath[findPath.size() - 1].first][findPath[findPath.size() - 1].second].power -= (map[v1[0].x][v1[0].y].power);
			isVisit[findPath[findPath.size() - 1].first][findPath[findPath.size() - 1].second] = true;
			if (map[findPath[findPath.size() - 1].first][findPath[findPath.size() - 1].second].power < 0) {
				map[findPath[findPath.size() - 1].first][findPath[findPath.size() - 1].second].power = 0;
			}
		}
		// 포탄 공격
		if (!isRazer) {
			int cx = v2[0].x;
			int cy = v2[0].y;
			map[cx][cy].power -= map[v1[0].x][v1[0].y].power;
			isVisit[cx][cy] = true;
			if (map[cx][cy].power < 0) {
				map[cx][cy].power = 0;
			}
			for (int dir = 0; dir < 8; ++dir) {
				int nx = cx + dx[dir];
				int ny = cy + dy[dir];
				if (nx == N) {
					nx = 0;
				}
				if (ny == N) {
					ny = 0;
				}
				if (nx == -1) {
					nx = N - 1;
				}
				if (ny == -1) {
					ny = N - 1;
				}
				if (isVisit[nx][ny] || (map[nx][ny].power == 0)) {
					continue;
				}
				map[nx][ny].power -= (map[v1[0].x][v1[0].y].power / 2);
				if (map[nx][ny].power < 0) {
					map[nx][ny].power = 0;
				}
				isVisit[nx][ny] = true;
			}
		}
		isVisit[v1[0].x][v1[0].y] = true;

		// 정비
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				if (map[i][j].power > 0 && !isVisit[i][j]) {
					++map[i][j].power;
				}
			}
		}
	}
	// 출력
	int result = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (result < map[i][j].power) {
				result = map[i][j].power;
			}
		}
	}
	cout << result;
	return 0;
}