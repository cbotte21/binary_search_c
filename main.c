#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Prototypes
int getArr(int** arr_p);
void printArr(int* arr, int size);
void copyArr(int* new, int* old, int indexes);

int binarySearch(int* arr, int size, int min, int max, int num);

void clearKeyboardBuffer(void);

int main(int argc, const char* argv[]) {
	//Predeclarations
	int* arr = NULL;
	int num, size, index;
	clock_t start, finish;

	//Populate array
	size = getArr(&arr);

	//Print array (debugging)
	printArr(arr, size);

	clearKeyboardBuffer();
	printf("Enter number to find:\n");
	scanf(" %d", &num);	

	//Binary search and check failure
	start = clock();
	index = binarySearch(arr, size, 0, size-1, num);
	finish = clock();
	printf("Time spend: %lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
	if (index == -1) {
		exit(1);
	}

	printf("Number %d found at index %d.\n", num, index);
	free(arr);
	return 0;
}

int getArr(int** arr_p) {
	int i, num;
	int* arr = NULL;

	for (i = 0, printf("[NUM 1]:\n"); scanf(" %d", &num) == 1; i++, printf("[NUM %d]:\n", i+1)) {
		clearKeyboardBuffer();
		arr = *arr_p;
		if (i == 0) {
			arr = (int*)malloc(sizeof(int));
			arr[i] = num;
			*arr_p = arr;
		} else if (num <= arr[i-1]) {
			printf("Every number must be larger than the last!\n");
			--i;
			continue;
		} else {
			int* tmp = (int*)malloc(sizeof(int) * i+1);
			if (arr == NULL || tmp == NULL) {
				printf("Failed to allocate memory!\n");
				exit(1);
			}
			copyArr(tmp, arr, i);
			tmp[i] = num;
			free(arr);
			*arr_p = tmp;
		}
	}
	return i;
}

void printArr(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void printArrZoom(int* arr, int min, int max);

void copyArr(int* new, int* old, int indexes) {
	for (int i = 0; i < indexes; i++) {
		new[i] = old[i];
	}
}

void clearKeyboardBuffer(void) {
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

//Recursive binary search (DEFAULT VALUES: min = 0; max = size - 1)
int binarySearch(int* arr, int size, int min, int max, int num) {
	printf("Min: %d, Max: %d\n", min, max);
	//printArrZoom(arr, min, max);
	size = max - min + 1;
	if (min == max) return min; //One value left
	if (size % 2 == 0) { //Even
		int check1 = min + ((size-1) / 2);
		int check2 = check1 + 1;
		printf("c1: %d, c2: %d\n", arr[check1], arr[check2]);
		if (num == arr[check1]) return check1;
		if (num == arr[check2]) return check2;
		if (num < arr[check2]) {
			printf("a\n");
			return binarySearch(arr, check2, min, check1-1, num); 
		}
		if (num > arr[check1]) {
			printf("b\n");
			return binarySearch(arr, check2, check2+1, max, num);
		}
	} 
	//Odd
	int check = min + ((size-1) / 2);
	printf("c: %d\n", arr[check]);
	if (num == arr[check]) return check;
	if (num < arr[check]) {
		printf("c\n");
		return binarySearch(arr, check, min, check-1, num);
	}
	if (num > arr[check]) {
		printf("d\n");
		return binarySearch(arr, check, check+1, max, num);
	}

	//Failed to classify case return -1
	printf("Failed to execute binary search!\n");
	return -1;
}

void printArrZoom(int* arr, int min, int max) {
	for (int i = min; min <= max; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}
