#include <bits/stdc++.h>
using namespace std;

int SIZE = 5;
int TOS = 5;

template <typename T>
vector<T> getCopy(vector<T> array) {
	vector<T> copy(SIZE + 5);
	for (int i = 0; i < TOS; i++) {
		copy[i] = array[i];
	}
	return copy;
}

template <typename T>
void print(vector<T> &array) {
	for (int i = 0; i < array.size(); i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

template <typename T>
void push(vector<T> &array, vector<T> &copy, T element) {
	if (copy.size() >= SIZE || array.size() >= SIZE) {
		copy = getCopy(array);
		SIZE = SIZE + 5;
        cout<<"size: "<<SIZE<<"\n";
		swap(array, copy);
	}

	array[TOS] = element;
	TOS++;
}

template <typename T>
void undo(vector<T> &array, vector<T> &copy) {
	array = getCopy(copy);
	copy[TOS - 2] = 0;
	TOS -= 2;
}

template <typename T>
T pop(vector<T> &array) {
	int element = array[TOS - 1];

	array[TOS - 1] = 0;
	TOS--;

	return element;
}

int main() {
	vector<int> original = {1, 2, 3, 4, 5};
	vector<int> shadow = getCopy(original);

	cout << original.size() << endl;
	cout << shadow.size() << endl;

	TOS = original.size();

	for (int i = 17; i < 27; i++) {
		push(original, shadow, i);
	}

	undo(original, shadow);

	print(original);
	print(shadow);

	return 0;
}
