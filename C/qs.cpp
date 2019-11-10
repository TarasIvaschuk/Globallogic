#include <iostream> 
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;

//FUNCTION PROTOTYPES

void print(int *arr, int size);
int compare(const void* a, const void* b);
int* create_array(int size);
void quickSort_presentation(int *arr, int left, int right);
int time_elapsed(void (*sort)(int * arr, int left, int right), int *arr, int left, int right);
int time_elapsed(void (*sort)(void* arr, size_t num, size_t size, int (*compare)(const void*, const void*)),
void* arr, size_t num, size_t size, int (*compare)(const void*, const void*));
int partition(int* arr, int start, int end);
void quicksort_new(int* arr, int start, int end);
void quicksort_web(int arr[], int low, int high);
void swap(int* a, int* b);
int partition_new(int arr[], int low, int high);

//START

int main(void)
{

	int size = 0;
	int elapsed_nanoseconds = 0;

	cout << "Enter the size of array\n";
	cin >> size;
	int *arr = create_array(size);

	/*const int num = 10;
	int arr[num] = { 9,4,19,2,7,9,5,15,23,3 };*/
	/*cout << "---------------------------quickSort_presentation----------------------------\n";
	cout << "before sorting \n";
	print(arr, size);
	elapsed_nanoseconds = time_elapsed(quickSort_presentation, arr, 0, size-1);
	cout << "after sorting \n";
	print(arr, size);*/
	//cout << "elapsed time: " << elapsed_nanoseconds << " ns\n";
	cout << "---------------------------quickSort standard library----------------------------\n";
	cout << "before sorting \n";
	print(arr, size);
	qsort(arr, size, sizeof(int), compare);
	elapsed_nanoseconds = time_elapsed(qsort, arr, size, sizeof(int), compare);
	cout << "after sorting \n";
	print(arr, size);
	cout << "elapsed time: "<< elapsed_nanoseconds << " ns\n";
	cout << "---------------------------quickSort new----------------------------\n";
	cout << "before sorting \n";
	print(arr, size);
	//partition(arr, 0, size-1);
	quicksort_new(arr, 0, size - 1);
	elapsed_nanoseconds = time_elapsed(quicksort_new, arr, 0, size - 1);
	cout << "after sorting \n";
	print(arr, size);
	cout << "elapsed time: " << elapsed_nanoseconds << " ns\n";

	cout << "---------------------------quickSort web----------------------------\n";
	cout << "before sorting \n";
	print(arr, size);
	qsort(arr, size, sizeof(int), compare);
	elapsed_nanoseconds = time_elapsed(quicksort_web, arr, 0, size - 1);
	cout << "after sorting \n";
	print(arr, size);
	cout << "elapsed time: " << elapsed_nanoseconds << " ns\n";


	return 0;
}

//FUNCTION DEFINITIONS

int compare(const void* a, const void* b)
{
	const int* x = (int*)a;
	const int* y = (int*)b;
	if (*x > * y)
		return 1;
	else if (*x < *y)
		return -1;
	return 0;
}

void print(int *arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << '\n';
}

int* create_array(int size)
{
	int* arr = new int [size];
	for (int i = 0; i < size; i++)
	{
		arr[i]=rand() % size;
	}
	return arr;
}

void quickSort_presentation(int *arr, int left, int right)
{
	int i = left;
	int j = right;
	int tmp = 0;
	int pivot = arr[(left + right)/2];

	while (i <= j)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[i] > pivot)
			j--;

		// swap
		if (i <= j)
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}

		//recursion
		if (left < j)
			quickSort_presentation(arr, left, j);

		if (i < right)
			quickSort_presentation(arr, i, right);
	}

}

int time_elapsed(void (*sort)(void* arr, size_t num, size_t size, int (*compare)(const void*, const void*)),
	void* arr, size_t num, size_t size, int (*compare)(const void*, const void*))
{
	srand(time(NULL));

	auto start = chrono::system_clock::now();
	sort(arr, num, size, compare);
	auto end = chrono::system_clock::now();

	chrono::duration<double> elapsed = end-start;
	int elapsed_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
	return elapsed_nanoseconds;
}

int time_elapsed(void (*sort)(int *arr, int left, int right), int *arr, int left, int right)
{
	srand(time(NULL));

	auto start = chrono::system_clock::now();
	sort(arr, left, right);
	auto end = chrono::system_clock::now();

	chrono::duration<double> elapsed = end - start;
	int elapsed_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
	return elapsed_nanoseconds;
}	

int partition(int *arr, int start, int end)
{
	
	int mid = (start + end) / 2;								/*take the middle node to enable fastest partition  */
	int piv = arr[mid];

	while (start < end)
	{
		while (arr[start] <= piv && start < end)				// must check i<j once more to make sure if it makes sense sorting
		{
			if (start < mid)									//we do not want to skip the pivot node		
				start++;
			else
			{
				break;											// we are the pivot so end the loop
			}
		}

		while (arr[end] >= piv && start < end)					// must check i<j once more to make sure if it makes sense sorting
		{
			if (end > mid)										// twe move cursor only to the pivot node so not skipping it
			{
				end--;
			}
			else
			{
				break;											// we are the pivot so end the loop
			}	
		}

		if (start < end)										
		{
			swap(arr[start], arr[end]);
			if (start == mid)									// if we swap the pivot element that we reached from start in the next loop we move from the end
			{
				mid = end;
				continue;
			}
			if (end == mid)										// if we swap the pivot element that we reached from end in the next loop we move from the start
			{
				mid = start;
				continue;
			}
		}
	}

	return start;
}

void quicksort_new(int *arr, int start, int end)
{
	if (start < end)											// it is one node in array so don't sort array
	{
		int sorted_index = partition_new(arr, start, end);
		quicksort_new(arr, start, sorted_index - 1);
		quicksort_new(arr, sorted_index + 1, end); 
	}
}

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition_new(int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot  
	int i = (low - 1); // Index of smaller element  

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot  
		if (arr[j] < pivot)
		{
			i++; // increment index of smaller element  
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quicksort_web(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition_new(arr, low, high);

		// Separately sort elements before  
		// partition and after partition  
		quicksort_web(arr, low, pi - 1);
		quicksort_web(arr, pi + 1, high);
	}
}