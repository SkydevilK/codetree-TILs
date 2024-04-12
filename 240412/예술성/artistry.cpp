#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cstring>
using namespace std;

int N;
int myMap[30][30];
int tempMap[30][30] = {};
int groupMap[30][30];
int result = 0;
bool isVisit[30][30];
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,1,-1 };
struct Group {
	int index;
	int number;
	vector<pair<int, int>> memberPos;
	map<pair<int, int>, int> near;
};
vector<Group> group;

void rotate(int sx, int sy, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			tempMap[sx + j][sy + size - i - 1] = myMap[sx + i][sy + j];
		}
	}
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			myMap[sx + i][sy + j] = tempMap[sx + i][sy + j];
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> myMap[i][j];
		}
	}

	for (int loop = 0; loop < 4; ++loop) {
		group = {};
		group.push_back({});
		// 그룹핑
		memset(isVisit, 0, sizeof(isVisit));
		memset(groupMap, 0, sizeof(groupMap));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				if (!isVisit[i][j]) {
					isVisit[i][j] = true;
					Group temp;
					temp.index = group.size();
					temp.number = myMap[i][j];
					temp.memberPos.push_back({ i, j });
					groupMap[i][j] = temp.index;
					queue<pair<int, int>> q;
					q.push({ i, j });
					while (!q.empty()) {
						pair<int, int> cur = q.front(); q.pop();
						for (int dir = 0; dir < 4; ++dir) {
							int nx = cur.first + dx[dir];
							int ny = cur.second + dy[dir];
							if (nx < 0 || ny < 0 || nx >= N || ny >= N || isVisit[nx][ny]) {
								continue;
							}
							if (myMap[nx][ny] != temp.number) {
								temp.near[{ nx, ny }] = temp.near[{ nx, ny }] + 1;
								continue;
							}
							isVisit[nx][ny] = true;
							temp.memberPos.push_back({ nx, ny });
							groupMap[nx][ny] = temp.index;
							q.push({ nx, ny });
						}
					}
					group.push_back(temp);
				}
			}
		}

		// 계산
		map<pair<int, int>, int> m;
		for (int i = 1; i < group.size(); ++i) {
			int a = group[i].index;
			map<pair<int, int>, int>::iterator iter = group[i].near.begin();
			while (iter != group[i].near.end()) {
				int b = groupMap[(*iter).first.first][(*iter).first.second];
				if (a < b) {
					m[{a, b}] = m[{a, b}] + (*iter).second;
				}
				else {
					m[{b, a}] = m[{b, a}] + (*iter).second;
				}
				++iter;
			}
		}
		map<pair<int, int>, int>::iterator iter = m.begin();
		while (iter != m.end()) {
			int a = (*iter).first.first;
			int b = (*iter).first.second;
			result += ((group[a].memberPos.size() + group[b].memberPos.size()) * group[a].number * group[b].number * (*iter).second);
			++iter;
		}

		// 회전
		rotate(0, 0, N / 2);
		rotate(N / 2 + 1, 0, N / 2);
		rotate(0, N / 2 + 1, N / 2);
		rotate(N / 2 + 1, N / 2 + 1, N / 2);
		// 십자가 회전
		for (int i = 0; i < N; ++i) {
			tempMap[N - i - 1][N / 2] = myMap[N / 2][i];
			tempMap[N / 2][i] = myMap[i][N / 2];
		}
		for (int i = 0; i < N; ++i) {
			myMap[N / 2][i] = tempMap[N / 2][i];
			myMap[i][N / 2] = tempMap[i][N / 2];
		}
	}
	cout << result << endl;
}