#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>

using namespace std;

// Class containing Quick, Merge, Radix, Selection sorting algorithms
template<class T>
class Algorithm {
private:
	int maxSize = 100; // Max number of items
	int length = 0; // Current count of item in array
	T* arr = new T[maxSize];
public:

	void selectionSort(bool isAsc) {
		for (int i = 0; i < length; ++i) {
			int index = i; // key
			int j = i + 1; // to the right
			while (j < length) { // Search the remaining part of the array for the lowest/greatest
				if (isAsc) { // For Ascending
					if (arr[j] < arr[index]) {
						index = j;
					}
				}
				else { // For Descending
					if ((arr[j]) > (arr[index])) {
						index = j;
					}
				}

				j++;
			}

			// Swap
			T temp = arr[index];
			arr[index] = arr[i];
			arr[i] = temp;
		}
	}

	void quickSort(bool isAsc, int low, int high) {
		if (low < high) { // Base Case when high <= low
			int key = quickSortPartition(isAsc, low, high); // key element index
			quickSort(isAsc, low, key - 1); // to left of key 
			quickSort(isAsc, key + 1, high); // to right of key
		}
	}

	int quickSortPartition(bool isAsc, int p, int q) {
		int i = p - 1;
		for (int j = p; j <= q - 1; j++) {
			if (isAsc) { // For Ascending
				if (arr[j] < arr[q]) {
					i++;

					// Swap
					T temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
			else { // For Descending
				if (arr[j] > arr[q]) {
					i++;

					// Swap
					T temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}

		// Swap
		T temp = arr[i + 1];
		arr[i + 1] = arr[q];
		arr[q] = temp;

		return i + 1;
	}

	void mergeSort(bool isAsc, int start, int end) {
		if (start < end) { // Base Case when high <= low
			int mid = ((end - start) / 2) + start; // Center index
			mergeSort(isAsc, start, mid); // to left of mid index (inclusive)
			mergeSort(isAsc, mid + 1, end); // to right of mid index (exclusive) 
			mergeSortMerge(isAsc, start, mid, end); // merge the two separated parts based on start, mid and end index
		}
	}

	void mergeSortMerge(bool isAsc, int start, int mid, int end) {
		int sizeOfLeft = mid - start + 1; // Size of the left part of the array
		int sizeOfRight = end - mid; // Size of the right part of the array
		T* left = new T[sizeOfLeft + 1]; // 1 size greater than the normal left size
		T* right = new T[sizeOfRight + 1]; // 1 size greater than the normal right size

		// Initialize left size of the array
		for (int i = 0; i < sizeOfLeft; i++) {
			left[i] = arr[start + i];
		}

		// Initialize right side of the array
		for (int i = 0; i < sizeOfRight; i++) {
			right[i] = arr[mid + 1 + i];
		}

		// Add sentinal values
		if (strcmp(typeid(T).name(), "long") == 0) {
			left[sizeOfLeft] = LONG_MAX;
			right[sizeOfRight] = LONG_MAX;
		}
		else if (strcmp(typeid(T).name(), "float") == 0) {
			left[sizeOfLeft] = numeric_limits<float>::max();
			right[sizeOfRight] = numeric_limits<float>::max();
		}

		// Merge with respective counters for both side
		int i = 0, j = 0;
		for (int k = start; k <= end; k++) {
			if (isAsc) { // For Ascending
				if (left[i] <= right[j]) {
					arr[k] = left[i++];
				}
				else {
					arr[k] = right[j++];
				}
			}
			else { // For Descending
				if (left[i] >= right[j]) {
					arr[k] = left[i++];
				}
				else {
					arr[k] = right[j++];
				}
			}

		}
	}

	void radixSort() {
		// AYESHA PLISS IMPLEMENT THIS
	}

	// Add to end of array
	void add() {
		if (length <= maxSize) { // Boundary check
			T inp;
			cout << length << " / 100 value(s) in collection" << endl;
			cout << "Enter Value: ";
			cin >> inp;

			arr[length++] = inp;

			cout << length << " / 100 value(s) in collection" << endl;
		}
	}

	void display() {
		cout << endl << "Final Array: ";

		for (int i = 0; i < length; ++i) {
			cout << arr[i];

			if (i != (length - 1)) {
				cout << ", ";
			}
		}

		cout << endl;
	}

	// Get current count of elements in array
	int getlength() {
		return length;
	}
};

template<class T>
void showChooseAlgoMenu(Algorithm<T>* alg, bool isAsc) {
	system("cls");
	cout << "Choose one or more Sorting algorithms you wish to check," << endl;
	cout << "1) Quick Sort" << endl;
	cout << "2) Merge Sort" << endl;
	cout << "3) Radix Sort" << endl;
	cout << "4) Selection Sort" << endl;
	cout << "Press anything else to exit..." << endl;

	vector<int> algoChoices;

	int algoInp;
	char chooseMoreInp;

	cout << endl << "Enter Input: ";
	cin >> algoInp;

	if (algoInp == 1 || algoInp == 2 || algoInp == 3 || algoInp == 4) {
		algoChoices.insert(algoChoices.end(), algoInp);
	}
	else {
		exit(0);
	}

	cout << "Choose more? (y/n): ";
	cin >> chooseMoreInp;

	while (chooseMoreInp == 'y') {
		cout << endl << "Enter Input: ";
		cin >> algoInp;

		if (algoInp == 1 || algoInp == 2 || algoInp == 3 || algoInp == 4) {
			algoChoices.insert(algoChoices.end(), algoInp);
		}
		else {
			exit(0);
		}

		cout << "Choose more? (y/n): ";
		cin >> chooseMoreInp;
	}

	cout << endl;

	string sortNames[4] = { "Quick", "Merge", "Radix", "Selection" };

	for (int i = 0, n = algoChoices.size(); i < n; i++) {
		int choice = algoChoices.at(i);
		cout << sortNames[choice - 1] << " Sort: ";

		clock_t startTime = clock();

		if (choice == 1) { // Quick sort
			if (isAsc) {
				alg->quickSort(isAsc, 0, alg->getlength() - 1);
			}
			else {
				alg->quickSort(isAsc, 0, alg->getlength());
			}
		}
		else if (choice == 2) { // Merge sort
			alg->mergeSort(isAsc, 0, alg->getlength() - 1);
		}
		else if (choice == 3) { // Radix sort

		}
		else { // Selection sort
			alg->selectionSort(isAsc);
		}

		clock_t endTime = clock();

		cout << ((endTime - startTime) / (double)CLOCKS_PER_SEC) << " second(s)" << endl;
	}

	alg->display();
};

template<class T>
void showOrderMenu(Algorithm<T>* alg) {
	system("cls");
	cout << "Select the order for sorting," << endl;
	cout << "1) Ascending" << endl;
	cout << "2) Descending" << endl;
	cout << "Press anything else to exit..." << endl;

	int orderInp;
	cout << endl << "Enter Input: ";
	cin >> orderInp;

	switch (orderInp) {
	case 1:
		showChooseAlgoMenu<T>(alg, true);
		break;
	case 2:
		showChooseAlgoMenu<T>(alg, false);
		break;
	default:
		exit(0);
	}

}

template<class T>
void showAddElementsMenu(Algorithm<T>* alg) {
	system("cls");
	cout << "Select from the available options," << endl;
	cout << "1) Add Element" << endl;
	cout << "Press anything else to exit..." << endl;

	int addInp;
	cout << endl << "Enter Input: ";
	cin >> addInp;

	if (addInp == 1) {
		char continueInp;
		while (true) {
			system("cls");
			alg->add();

			cout << endl << "Add more? (y/n): ";
			cin >> continueInp;

			if (continueInp != 'y') {
				break;
			}

		}

		showOrderMenu<T>(alg);
	}
	else {
		exit(0);
	}
}

void showMainMenu() {
	system("cls");
	cout << "Sorting Algorithms Time Complexity Checker" << endl;
	cout << "Select array elements data type," << endl;
	cout << "1) long" << endl;
	cout << "2) float" << endl;
	cout << "3) string" << endl;
	cout << "Press anything else to exit..." << endl;

	int typeInp;
	cout << endl << "Enter Input: ";
	cin >> typeInp;

	if (typeInp == 1) {
		Algorithm<long>* alg = new Algorithm<long>();
		showAddElementsMenu<long>(alg);
	}
	else if (typeInp == 2) {
		Algorithm<float>* alg = new Algorithm<float>();
		showAddElementsMenu<float>(alg);
	}
	else if (typeInp == 3) {
		Algorithm<string>* alg = new Algorithm<string>();
		showAddElementsMenu<string>(alg);
	}
	else {
		exit(0);
	}
};

int main() {

	showMainMenu();

	cout << endl;

	system("pause");
	return 0;
};