#include <iostream>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <random>
#include <typeinfo>

using namespace std;
using namespace chrono;

void quickSort(int* array, int low, int high)
{
	int i = low;
	int j = high;
	int pivot = array[(i + j) / 2];
	int temp;

	while (i <= j)
	{
		while (array[i] < pivot)
			i++;
		while (array[j] > pivot)
			j--;
		if (i <= j)
		{
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i++;
			j--;
		}
	}
	if (j > low)
		quickSort(array, low, j);
	if (i < high)
		quickSort(array, i, high);
}
int linearSearch(int* arr, int size, int key)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == key)
			return 0;
	}
	return -1;
}
int binarySearch(int* arr, int l, int r, int x)
{
	if (r >= l) {
		int middle = l + (r - l) / 2;
		if (arr[middle] == x)
			return 0;
		if (arr[middle] > x)
			return binarySearch(arr, l, middle - 1, x);
		return binarySearch(arr, middle + 1, r, x);
	}
	return -1;

}

int interpolSearch(int* arr, int size, int key)
{
	int left = 0;
	int right = size - 1;
	int tmp = -1;
	while (left <= right && key >= arr[left] && key <= arr[right])
	{
		int middle = left + (((double)(right - left) / (arr[right] - arr[left])) * (key - arr[left]));
		if (arr[middle] == key)
			return 0;
		if (arr[middle] < key)
			left = middle + 1;
		else
			right = middle - 1;
	}
	return -1;
}

int main()
{
	cout << "Enter number to search: ";
	int key;
	cin >> key;
	srand(time(NULL));
	int* arr0;
	const int minNumber = 0;
	const int maxNumber = 100000;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(minNumber, maxNumber);
	typedef ratio<1l, 1000000000000l> pico;
	typedef duration<long long, pico> picoseconds;
	auto start = high_resolution_clock::now();
	auto end = high_resolution_clock::now();
	auto elapsedSeconds = duration_cast<picoseconds>(end - start).count();
	int index;
	const int min = 50000;
	const int max = 1000000;
	const int step = 50000;
	for (int i = min; i <= max; i += step)
	{
		arr0 = new int[i];
		for (int j = 0; j < i; j++)
		{
			arr0[j] = distribution(generator);
		}
		start = high_resolution_clock::now();
		index = linearSearch(arr0, i, key);
		end = high_resolution_clock::now();
		elapsedSeconds = duration_cast<picoseconds>(end - start).count();
		if (index == 0)
			cout << "Linear search: " << key << " in " << i << " elements found. Time:  " << elapsedSeconds << "  picoseconds" << endl;
		else
			cout << "Element didn't find. Time: " << elapsedSeconds << " picoseconds" << endl << endl;
		quickSort(arr0, 0, i - 1);
		start = high_resolution_clock::now();
		index = binarySearch(arr0, 0, i - 1, key);
		end = high_resolution_clock::now();
		elapsedSeconds = duration_cast<picoseconds>(end - start).count();
		if (index == 0)
			cout << "Binary search: " << key << " in " << i << " elements found. Time: " << elapsedSeconds << " picoseconds" << endl ;
		else
			cout << "Element didn't find. Time: " << elapsedSeconds << " picoseconds" << endl << endl;
		start = high_resolution_clock::now();
		index = interpolSearch(arr0, i, key);
		end = high_resolution_clock::now();
		elapsedSeconds = duration_cast<picoseconds>(end - start).count();
		if (index == 0)
			cout << "Interpolation search: " << key << " in " << i << " elements found. Time: " << elapsedSeconds << " picoseconds" << endl;
		else
			cout << "Element didn't find. Time: " << elapsedSeconds << " picoseconds" << endl << endl;
		delete[] arr0;
	}
	return 0;
}