#include <iostream>
#include<vector>
using namespace std;

int N, M, P, C, D, index;
struct Rudolf {
	int x, y;
};
struct Santa {
	int x, y, score;
	bool isDied;
	int isStun;
};
vector<Santa> santa(31);
Rudolf rudolf;
int santaMap[51][51];
// 상 우 하 좌
int dx[] = { -1,0,1,0, 1, 1, -1, -1 };
int dy[] = { 0,1,0,-1, 1, -1, 1, -1 };
bool checkDied(int x, int y) {
	return x > N || y > N || x <= 0 || y <= 0;
}
void DFS(int x, int y, int index, int dir) {
	if (checkDied(x, y)) {
		santa[index].isDied = true;
		return;
	}
	if (santaMap[x][y] == 0) {
		santaMap[x][y] = index;
		santa[index].x = x;
		santa[index].y = y;
		return;
	}
	DFS(x + dx[dir], y + dy[dir], santaMap[x][y], dir);
	santaMap[x][y] = index;
	santa[index].x = x;
	santa[index].y = y;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	// Input
	cin >> N >> M >> P >> C >> D;
	cin >> rudolf.x >> rudolf.y;
	for (int i = 0; i < P; ++i) {
		cin >> index;
		santa[index].isDied = false;
		santa[index].isStun = false;
		santa[index].score = 0;

		cin >> santa[index].x >> santa[index].y;
		santaMap[santa[index].x][santa[index].y] = index;
	}

	// Simulation
	for (int turn = 0; turn < M; ++turn) {
		// 루돌프 턴

		// 1. 가장 가까운 산타 계산
		int tempNum = 0;
		int tempCalc = 987654321;
		int calc = 0;
		for (int i = 1; i <= P; ++i) {
			if (santa[i].isDied) {
				continue;
			}
			calc = ((rudolf.x - santa[i].x) * (rudolf.x - santa[i].x) + (rudolf.y - santa[i].y) * (rudolf.y - santa[i].y));
			if (tempCalc > calc) {
				tempCalc = calc;
				tempNum = i;
			}

			// 같을 경우
			else if (tempCalc == calc) {
				// row 가 클 때 
				if (santa[tempNum].x < santa[i].x) {
					tempNum = i;
				}

				// row가 같고 col이 클 때
				else if (santa[tempNum].x == santa[i].x && santa[tempNum].y < santa[i].y) {
					tempNum = i;
				}
			}
		}
		// 2. 방향 계산
		int tempDir = 0;
		tempCalc = 987654321;
		for (int i = 0; i < 8; ++i) {
			int nx = rudolf.x + dx[i];
			int ny = rudolf.y + dy[i];
			calc = ((nx - santa[tempNum].x) * (nx - santa[tempNum].x) + (ny - santa[tempNum].y) * (ny - santa[tempNum].y));
			if (tempCalc > calc) {
				tempCalc = calc;
				tempDir = i;
			}
		}

		// 3. 공격
		rudolf.x = rudolf.x + dx[tempDir];
		rudolf.y = rudolf.y + dy[tempDir];
		if (tempCalc == 0) {
			santa[tempNum].score += C;
			santaMap[rudolf.x][rudolf.y] = 0;
			santa[tempNum].x += (dx[tempDir] * C);
			santa[tempNum].y += (dy[tempDir] * C);
			if (checkDied(santa[tempNum].x, santa[tempNum].y)) {
				santa[tempNum].isDied = true;
			}
			else {
				santa[tempNum].isStun = turn + 2;
				DFS(santa[tempNum].x, santa[tempNum].y, tempNum, tempDir);
			}
		}
		// 산타 턴
		for (int i = 1; i <= P; ++i) {

			// 죽거나 기절하면 무효
			if (santa[i].isDied || santa[i].isStun > turn) {
				continue;
			}
			tempCalc = (rudolf.x - santa[i].x) * (rudolf.x - santa[i].x) + (rudolf.y - santa[i].y) * (rudolf.y - santa[i].y);

			for (int dir = 0; dir < 4; ++dir) {
				int nx = santa[i].x + dx[dir];
				int ny = santa[i].y + dy[dir];
				if (checkDied(nx, ny) || santaMap[nx][ny] > 0) {
					continue;
				}
				calc = ((nx - rudolf.x) * (nx - rudolf.x) + (ny - rudolf.y) * (ny - rudolf.y));
				if (tempCalc > calc) {
					tempCalc = calc;
					tempDir = dir;
				}
			}

			if (tempCalc == ((rudolf.x - santa[i].x) * (rudolf.x - santa[i].x) + (rudolf.y - santa[i].y) * (rudolf.y - santa[i].y))) {
				continue;
			}

			// 루돌프랑 충돌
			if (tempCalc == 0) {
				santa[i].score += D;
				santa[i].isStun = turn + 2;
				switch (tempDir) {
				case 0:
					tempDir = 2;
					break;
				case 1:
					tempDir = 3;
					break;
				case 2:
					tempDir = 0;
					break;
				case 3:
					tempDir = 1;
					break;
				}
				if (checkDied(rudolf.x + (dx[tempDir] * D), rudolf.y + (dy[tempDir] * D))) {
					santa[i].isDied = true;
					santaMap[santa[i].x][santa[i].y] = 0;
				}
				else {
					santaMap[santa[i].x][santa[i].y] = 0;
					DFS(rudolf.x + (dx[tempDir] * D), rudolf.y + (dy[tempDir] * D), i, tempDir);
				}
			}
			else {
				santaMap[santa[i].x][santa[i].y] = 0;
				santa[i].x = santa[i].x + dx[tempDir];
				santa[i].y = santa[i].y + dy[tempDir];
				santaMap[santa[i].x][santa[i].y] = i;
			}
		}

		// 죽지 않은 산타 보너스 점수
		bool isCheck = false;
		for (int i = 1; i <= P; ++i) {
			if (!santa[i].isDied) {
				isCheck = true;
				++santa[i].score;
			}
		}

		// 모든 산타가 죽었으므로 시뮬레이션 종료
		if (!isCheck) {
			break;
		}
	}

	// Answer
	for (int i = 1; i <= P; ++i) {
		cout << santa[i].score << " ";
	}
}