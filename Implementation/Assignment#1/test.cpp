#include <stdio.h>
#include <string.h>
#include <ctime>
#define MAX 500000

void insertionSort(int array[], int n);
void mergeSort(int array[], int m, int n);
void merge(int array[], int m, int mid, int n);
void quickSort(int array[], int m, int n);
int partition(int array[], int m, int n);
void heapSort(int array[], int n);
void buildHeap (int array[], int n);
void heapify(int array[], int here, int n);

//예외인 전역 변수.
//불가피하게 사용.
int arrayM[MAX]; //Merge Sort에서 사용하는 추가 공간.
int com=0, swap=0; //compare, swap number.

//Main Function.
int main(int argc, char* argv[]) {
	clock_t start, end;
	double duration;
	int times = 0;
	
	//입력 재지정, input.txt.
	//Array에 저장.
	int array[MAX];	
	for (int i=0; i<MAX; i++) {
		scanf("%d", &array[i]);
	}

	//Insertion Sorting.
	if (strcmp(argv[1], "insertion") == 0) {	
		//Measure Time & insertionSort Algorithm.
		start = clock();
		insertionSort(array, MAX);
		end = clock();
		duration = (double)(end - start) / CLOCKS_PER_SEC;
		printf("Duration: %f s\nComparison: %d\nSwap: %d\n", duration, com, swap);
	}
	//Merge Sorting.
	else if (strcmp(argv[1], "merge") == 0) {
		start = clock();
		mergeSort(array, 0, MAX-1);
		end = clock();
		duration = (double)(end - start) / CLOCKS_PER_SEC;
		printf("Duration: %f s\nComparison: %d\nSwap: %d\n", duration, com, swap);
	}
	//Quick Sorting.
	else if (strcmp(argv[1], "quick") == 0) {
		start = clock();
		quickSort(array, 0, MAX - 1);
		end = clock();
		duration = (double)(end - start) / CLOCKS_PER_SEC;
		printf("Duration: %f s\nComparison: %d\nSwap: %d\n", duration, com, swap);	
	}
	//Heap Sorting.
	else if (strcmp(argv[1], "heap") == 0) {
		start = clock();
		heapSort(array, MAX);
		end = clock();
		duration = (double)(end - start) / CLOCKS_PER_SEC;
		printf("Duration: %f s\nComparison: %d\nSwap: %d\n", duration, com, swap);	
	}

	//출력 재지정, output.txt.
	for (int i=0; i<MAX; i++) {
		printf("%d ", array[i]);
	}
	
	return 0;
}

//Insertion Sort.
void insertionSort(int array[], int n) {
	int i, j, key;

	for (i = 1; i < n; i++) {
		key = array[i];
		j = i - 1;
		while (j >= 0 && array[j] > key) {
			array[j + 1] = array[j];
			j -= 1;
			com += 1;
			swap += 1;
		}
		array[j + 1] = key;
		swap += 1;
	}
}

//Merge Sort.
void mergeSort(int array[], int m, int n) { 
	if (m < n) {
		int mid = (m + n) / 2;
		mergeSort(array, m, mid);
		mergeSort(array, mid+1, n);
		merge(array, m, mid, n);
	}
}

void merge(int array[], int m, int mid, int n) {
	int i=m, j=mid+1, k=m;

	while (i <= mid && j <= n) {
		if (array[i] <= array[j]) {
			arrayM[k] = array[i];
			swap += 1;
			com += 1;
			i++;
		} else {
			arrayM[k] = array[j];
			swap += 1;
			com += 1;
			j++;
		}
		k++;
	}

	if (i > mid) {
		for (int l=j; l<=n; l++) {
			arrayM[k] = array[l];
			k++;
			//swap += 1;
		}
	} else {
		for (int l=i; l<=mid; l++) {
			arrayM[k] = array[l];
			k++;
			//swap += 1;
		}
	}
	
	//추가로 만들어 둔 arrayM을 대입한다.
	for (int l=m; l<=n; l++) {
		array[l] = arrayM[l];
	}
}

//Quick Sort.
void quickSort(int array[], int m, int n) {
	if (m <= n) {
		int pivot = partition(array, m, n);
		quickSort(array, m, pivot-1);
		quickSort(array, pivot+1, n);
	}
}

int partition(int array[], int m, int n) {
	int pivot, temp, low, high;

	low = m + 1;
	high = n;
	pivot = array[m];

	while (low <= high) {
		while (low <= n && pivot >= array[low]) {
			low++;
			com += 1;
		}
		while (high >= m+1 && pivot <= array[high]) {
			high--;
			com += 1;
		}
		if (low <= high) {
			temp = array[low];
			array[low] = array[high];
			array[high] = temp;
			swap += 1;
		}
	}
	
	temp = array[m];
	array[m] = array[high];
	array[high] = temp;
	swap += 1;

	return high;
}

//Heap Sort.
void heapSort(int array[], int n) {
	buildHeap(array, n);
        for (int i=n-1; i>=0; i--) {
        	int temp = array[i];
                array[i] = array[0];
                array[0] = temp;
		swap += 1;		

                heapify(array, 0, i);
	}
}

void buildHeap (int array[], int n) {
	for (int i=n/2-1; i>=0; i--) {
		heapify(array, i, n);
	}
}

void heapify(int array[], int here, int n) {
	int left = here * 2 + 1;
	int right = here * 2 + 2;
	int max = here;
	if (left < n && array[left] > array[max]) {
		max = left;
	}
	if (right < n && array[right] > array[max]) {
		max = right;
	}

	if (max != here) {
		int temp = array[here];
		array[here] = array[max];
		array[max] = temp;
		com += 1;
		swap += 1;
		heapify(array, max, n);
	}
}
