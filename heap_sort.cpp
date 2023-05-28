#include <iostream>
#include <vector>

using namespace std;

void swap(vector<int>& arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;    
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr, i, largest);
        heapify(arr, n, largest);
    }
}

void buildHeap(vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

void findMinMaxMarks(const vector<int>& marks) {
    int n = marks.size();

    cout << "Maximum Marks: " << marks[n-1] << endl;

    cout << "Minimum Marks: " << marks[0] << endl;
}

void heapSort(vector<int>& marks) {
    int n = marks.size();

    buildHeap(marks, n);

    for (int i = n - 1; i > 0; i--) {
        swap(marks, 0, i);
        heapify(marks, i, 0);
    }
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    vector<int> marks(n);

    cout << "Enter the marks obtained by students:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Student " << (i + 1) << ": ";
        cin >> marks[i];
    }

    heapSort(marks);

    cout << "Marks in descending order: ";
    for (int i = n-1; i >= 0; i--) {
        cout << marks[i] << " ";
    }
    cout << endl;

    findMinMaxMarks(marks);

    return 0;
}
