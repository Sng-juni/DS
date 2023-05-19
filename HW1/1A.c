#include <stdio.h>
#include <stdlib.h>

int N, X;
int arr[6];
int sum;

void CheckAndPrint(int idx) {
	if (idx != N - 1 ||  sum != X) {
		return;
	}
	for (int i = 0; i < N; i++) {
		printf("%d", arr[i]);
	}
	printf("\n");
}

int main() {
	scanf("%d\n%d", &N, &X);
	for (arr[0] = 0; arr[0] < 4 && &arr[0] <= &arr[N - 1]; arr[0]++ ) {
		sum += arr[0];
		for (arr[1] = 0; arr[1] < 4 && &arr[1] <= &arr[N - 1]; arr[1]++) {
			sum += arr[1];
			for (arr[2] = 0; arr[2] < 4 && &arr[2] <= &arr[N - 1]; arr[2]++) {
				sum += arr[2];
				for (arr[3] = 0; arr[3] < 4 && &arr[3] <= &arr[N - 1]; arr[3]++) {
					sum += arr[3]; 
					for (arr[4] = 0; arr[4] < 4 && &arr[4] <= &arr[N - 1]; arr[4]++) {
						sum += arr[4];
						for (arr[5] = 0; arr[5] <4 && &arr[5] <= &arr[N - 1]; arr[5]++) {
							sum += arr[5];
							CheckAndPrint(5);
							sum -= arr[5];
						}
						CheckAndPrint(4);
						sum -= arr[4];
					}
					CheckAndPrint(3);
					sum -= arr[3];
				}
				CheckAndPrint(2);
				sum -= arr[2];
			}
			CheckAndPrint(1);
			sum -= arr[1];
		}
		CheckAndPrint(0);
		sum -= arr[0];
	}

	return 0;
}
