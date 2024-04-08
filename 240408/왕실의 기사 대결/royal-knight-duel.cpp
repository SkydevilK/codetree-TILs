#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct Knight {
	int r, c, h, w, k, damage;
};
int L, N, Q, k, i, d;
int map[41][41];
int knightMap[41][41];
vector<Knight> knights(31);
stack<int> s;
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };

bool checkMove(int index, int dir) {
	s.push(index);
	bool visit[41] = {};
	for (int r = 0; r < knights[index].h; ++r) {
		for (int c = 0; c < knights[index].w; ++c) {
			int nx = knights[index].r + dx[dir] + r;
			int ny = knights[index].c + dy[dir] + c;
			if (!(knightMap[nx][ny] == 0 || knightMap[nx][ny] == index)) {
				visit[knightMap[nx][ny]] = true;
			}
			if (map[nx][ny] == 2) {
				return false;
			}
			if (nx > L || ny > L || nx <= 0 || ny <= 0) {
				return false;
			}
		}
	}
	for (int i = 1; i <= N; ++i) {
		if (visit[i]) {
			if (!checkMove(i, dir)) {
				return false;
			}
		}
	}

	return true;
}
void move(int index, int dir) {
	for (int r = 0; r < knights[index].h; ++r) {
		for (int c = 0; c < knights[index].w; ++c) {
			knightMap[knights[index].r + r][knights[index].c + c] = 0;
		}
	}
	knights[index].r += dx[dir];
	knights[index].c += dy[dir];
	
	for (int r = 0; r < knights[index].h; ++r) {
		for (int c = 0; c < knights[index].w; ++c) {
			knightMap[knights[index].r + r][knights[index].c + c] = index;
			if (map[knights[index].r + r][knights[index].c + c] == 1 && index != i) {
				knights[index].k -= 1;
				++knights[index].damage;
			}
		}
	}
	if (knights[index].k < 0) {
		knights[index].k = 0;
		for (int r = 0; r < knights[index].h; ++r) {
			for (int c = 0; c < knights[index].w; ++c) {
				knightMap[knights[index].r + r][knights[index].c + c] = 0;
			}
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> L >> N >> Q;
	for (int i = 1; i <= L; ++i) {
		for (int j = 1; j <= L; ++j) {
			cin >> map[i][j];
		}
	}

	for (int i = 1; i <= N; ++i) {
		cin >> knights[i].r >> knights[i].c >> knights[i].h >> knights[i].w >> knights[i].k;
		for (int r = 0; r < knights[i].h; ++r) {
			for (int c = 0; c < knights[i].w; ++c) {
				knightMap[knights[i].r + r][knights[i].c + c] = i;
			}
		}
	}

	for (int turn = 0; turn < Q; ++turn) {
		cin >> i >> d;
		if (knights[i].k == 0) {
			continue;
		}
		s = {};
		if (checkMove(i, d)) {
			while (!s.empty()) {
				move(s.top(), d);
				s.pop();
			}
		}
	}
	int result = 0;
	for (int i = 1; i <= N; ++i) {
		if (knights[i].k > 0) {
			result += knights[i].damage;
		}
	}
	cout << result;
	return 0;
}