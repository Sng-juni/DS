#include <stdio.h>
#include <stdlib.h>

int N, X, sum;
int result[6];

int isPalindrome(int arr[]) {
	int res = 1;
	for (int i = 0; i < N / 2; i++) {
		if (arr[i] != arr[N - 1 - i]) {
			res = 0;
		}
	}
	if (res == 0) {
		return 0;
	}
	else {
		return 1;
	}
}

void Get_4ary(int depth, int sum) {
	if (depth < 0 ) return;
	if (depth == 0 && sum == X && isPalindrome(result)) {
		for (int i = 0; i < N; i++) {
			printf("%d", result[i]);
		}
		printf("\n");
		return;
	}
	for (int i = 0; i < 4; i++) {
		result[N - depth] = i;
		Get_4ary(depth - 1, sum + i);
	}
}


int main(){
	scanf("%d\n%d", &N, &X);
	Get_4ary(N, 0);
	return 0;
}
