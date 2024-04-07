#include <iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int input, input2, N, Q, result;
struct Node {
	int parentIndex;
	int leftIndex;
	int rightIndex;
	int authority;
	int note[21] = {};	// 0 부모 
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
		input2 = i;
		while (1)
		{
			if (input == 0 || input2 == 0)
			{
				break;
			}

			input2 = nodePool[input2].parentIndex;
			--input;
			++nodePool[input2].note[input];
		}
	}
}

void turnAlarm() {
	cin >> input;
	if (nodePool[input].isAlarm)
	{
		nodePool[input].isAlarm = false;

		int temparray[21];

		for (int i = 1; i <= 20; ++i)
		{
			temparray[i] = nodePool[input].note[i];
		}
		++temparray[nodePool[input].authority];
		int next = nodePool[input].parentIndex;
		int cnt = 19;
		while (1)
		{
			for (int i = 1; i <= cnt; ++i)
			{
				temparray[i - 1] = temparray[i];
				nodePool[next].note[i - 1] -= temparray[i - 1];
			}
			temparray[cnt + 1] = 0;
			if (!nodePool[next].isAlarm) break;
			if (next == 0) break;
			next = nodePool[next].parentIndex;
			--cnt;
		}

	}
	else
	{
		nodePool[input].isAlarm = true;
		int temparray[21];
		for (int i = 1; i <= 20; i++)
		{
			temparray[i] = nodePool[input].note[i];
		}
		++temparray[nodePool[input].authority];
		int next = nodePool[input].parentIndex;
		int cnt = 19;
		while (1)
		{
			for (int i = 1; i <= cnt; i++)
			{
				temparray[i - 1] = temparray[i];
				nodePool[next].note[i - 1] += temparray[i - 1];
			}
			temparray[cnt + 1] = 0;
			if (!nodePool[next].isAlarm) break;
			if (next == 0) break;
			next = nodePool[next].parentIndex;
			--cnt;
		}
	}
}

void changePower() {
	cin >> input >> input2;
	int prev = nodePool[input].authority;
	nodePool[input].authority = input2;
	if (!nodePool[input].isAlarm) return;
	if (input2 == prev)
	{
		return;
	}
	else if (input2 > prev)
	{
		int next = input;
		for (int i = 0; i < nodePool[next].authority; ++i)
		{

			next = nodePool[next].parentIndex;
			--nodePool[next].note[prev - 1 - i];
			++nodePool[next].note[input2 - 1 - i];
			if (!nodePool[next].isAlarm) return;
			if (next == 0) return;
		}
		for (int i = input2 - nodePool[next].authority - 1; i >= 0; --i)
		{
			next = nodePool[next].parentIndex;
			++nodePool[next].note[i];
			if (!nodePool[next].isAlarm) return;
			if (next == 0) return;
		}
	}
	else
	{
		int next = input;
		for (int i = 0; i < input2; ++i)
		{
			next = nodePool[next].parentIndex;
			--nodePool[next].note[prev - 1 - i];
			++nodePool[next].note[input2 - 1 - i];
			if (!nodePool[next].isAlarm) return;
			if (next == 0) return;
		}
		for (int i = nodePool[next].authority - input2 - 1; i >= 0; --i)
		{
			next = nodePool[next].parentIndex;
			--nodePool[next].note[i];
			if (!nodePool[next].isAlarm) return;
			if (next == 0) return;
		}
	}
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

	int tempA[21];
	int tempB[21];
	for (int i = 1; i <= 20; ++i)
	{
		tempA[i] = nodePool[input].note[i];
		tempB[i] = nodePool[input2].note[i];
	}
	++tempA[nodePool[input].authority];
	++tempB[nodePool[input2].authority];

	if (!nodePool[input].isAlarm)
	{
		memset(tempA, 0, sizeof(tempA));
	}

	if (!nodePool[input2].isAlarm)
	{
		memset(tempB, 0, sizeof(tempB));
	}

	int next = nodePool[input].parentIndex;
	while (1)
	{
		for (int i = 1; i <= 20; ++i)
		{
			tempA[i - 1] = tempA[i];
			tempB[i - 1] = tempB[i];
			nodePool[next].note[i - 1] += tempA[i - 1];
			nodePool[next].note[i - 1] -= tempB[i - 1];
		}
		if (!nodePool[next].isAlarm) break;
		tempA[20] = 0;
		tempB[20] = 0;
		if (next == 0) break;
		next = nodePool[next].parentIndex;
	}

	next = nodePool[input2].parentIndex;

	for (int i = 1; i <= 20; ++i)
	{
		tempA[i] = nodePool[input].note[i];
		tempB[i] = nodePool[input2].note[i];
	}
	++tempA[nodePool[input].authority];
	++tempB[nodePool[input2].authority];
	if (!nodePool[input].isAlarm)
	{
		memset(tempA, 0, sizeof(tempA));
	}

	if (!nodePool[input2].isAlarm)
	{
		memset(tempB, 0, sizeof(tempB));
	}

	while (1)
	{
		for (int i = 1; i <= 20; ++i)
		{
			tempA[i - 1] = tempA[i];
			tempB[i - 1] = tempB[i];
			nodePool[next].note[i - 1] -= tempA[i - 1];
			nodePool[next].note[i - 1] += tempB[i - 1];
		}

		if (!nodePool[next].isAlarm) break;
		tempA[20] = 0;
		tempB[20] = 0;
		if (next == 0) break;
		next = nodePool[next].parentIndex;
	}

}
void search() {
	cin >> input;
	int result = 0;
	for (int i = 0; i < 21; i++)
	{
		result += nodePool[input].note[i];
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