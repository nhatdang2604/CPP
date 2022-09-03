#include <stdio.h>

int main() {
	int a = 0, b = 1, c = 2, n = 3;
	float f[100][3];
	errno_t err;
	FILE *stream, *stream2;
	err = fopen_s(&stream, "input.in", "r");
	if (!stream) {
		printf("Khong ton tai file input\n");
		return 0;
	}
	else {
		fscanf_s(stream, "%d", &n);
		for (int i = 0; i < n; ++i) {
			fscanf_s(stream, "%f%f%f", &f[i][0], &f[i][1], &f[i][2]);
		}
		fclose(stream);
	}
	err = fopen_s(&stream2, "output.out", "w");
	if (!stream) {
		printf("Khong mo duoc!\n");
		return 0;
	}
	else {
		for (int i = 0; i < n; ++i) {
			fprintf_s(stream2, "%.2f %.2f %.2f\n", f[i][0], f[i][1], f[i][2]);
		}
		fclose(stream2);
	}
	return 0;
}
