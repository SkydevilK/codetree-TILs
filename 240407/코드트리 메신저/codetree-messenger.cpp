#include <iostream>
#include<algorithm>
using namespace std;

int input, input2, N, Q, result;
struct Node {
	int parentIndex;
	int leftIndex;
	int rightIndex;
	int authority;
	bool isAlarm;
};

Node nodePool[100001];
void init() {
	for (int i = 1; i <= N; ++i) {
		cin >> input;
		nodePool[i].parentIndex = input;
		nodePool[i].isAlarm = true;
		if (nodePool[input].leftIndex == 0) {
			nodePool[input].leftIndex = i;
		}
		else {
			nodePool[input].rightIndex = i;
		}
	}
	for (int i = 1; i <= N; ++i) {
		cin >> input;
		nodePool[i].authority = input;
	}
}

void turnAlarm() {
	cin >> input;
	nodePool[input].isAlarm = !nodePool[input].isAlarm;
}

void changePower() {
	cin >> input >> input2;
	nodePool[input].authority = input2;
}

void changeParent() {
	cin >> input >> input2;
	if (nodePool[nodePool[input].parentIndex].leftIndex == input) {
		nodePool[nodePool[input].parentIndex].leftIndex = input2;
	}
	else {
		nodePool[nodePool[input].parentIndex].rightIndex = input2;
	}

	if (nodePool[nodePool[input2].parentIndex].leftIndex == input2) {
		nodePool[nodePool[input2].parentIndex].leftIndex = input;
	}
	else {
		nodePool[nodePool[input2].parentIndex].rightIndex = input;
	}

	swap(nodePool[input].parentIndex, nodePool[input2].parentIndex);
}
void DFS(int index, int depth) {
	if (!nodePool[index].isAlarm) {
		return;
	}
	if (nodePool[index].authority >= depth) {
		++result;
	}
	if (nodePool[index].leftIndex != 0) {
		DFS(nodePool[index].leftIndex, depth + 1);
	}
	if (nodePool[index].rightIndex != 0) {
		DFS(nodePool[index].rightIndex, depth + 1);
	}
}
void search() {
	cin >> input;
	result = 0;
	if (nodePool[input].leftIndex != 0) {
		DFS(nodePool[input].leftIndex, 1);
	}
	if (nodePool[input].rightIndex != 0) {
		DFS(nodePool[input].rightIndex, 1);
	}
	cout << result << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> N >> Q;
	for (int turn = 0; turn < Q; ++turn) {
		cin >> input;
		switch (input) {
		case 100:
			init();
			break;
		case 200:
			turnAlarm();
			break;
		case 300:
			changePower();
			break;
		case 400:
			changeParent();
			break;
		case 500:
			search();
			break;
		}

	}

	return 0;
}