#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

//��ⲻ������ Ax + By = C ��������

const int MAXN = 100001;

int A, B, C, d, x, y;

void Exgcd(int a, int b, int &d, int &x, int &y) {
	if(!b) d = a, x = 1, y = 0;
	else Exgcd(b, a % b, d, y, x), y -= x * (a / b);
}

int main() {
	scanf("%d %d %d", &A, &B, &C);
	Exgcd(A, B, d, x, y);
	if(C % d) puts("No solution");
	else {
		x = x * C / d, y = y * C / d;
		A /= d, B /= d;
		x += 2 * B, y -= 2 * A;//�������������� x += m * B ͬʱ y -= m * A ע���ʱ B /= d, A /= d;
		printf("%d %d\n", x, y);
	}
	return 0;
}
