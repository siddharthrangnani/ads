#include<bits/stdc++.h>
using namespace std;

int SIZE = 6;
int TOS = 3;

template <typename T>
vector<T> getCopy(vector<T> arr){
    vector<T> cp(SIZE + 3);
    for(int i=0;i<TOS;++i){
        cp[i] = arr[i];
    }
    return cp;
}

template <typename T>
void undo(vector<T>& arr,vector<T>& cp){
    arr = getCopy(cp);
	cp[TOS - 2] = 0;
	TOS -= 2;
}

template <typename T>
void printArr(vector<T> arr){
    for(int i=0;i<arr.size();++i){
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
}

template <typename T>
void push(vector<T>& arr,vector<T>& dummy,T element){

    if(arr.size()>= SIZE || dummy.size()>= SIZE){
        cout<<"\nele: "<<element;
        dummy = getCopy(arr);
        SIZE = SIZE + 3;
        swap(arr,dummy);
        cout<<"\narr size: "<<arr.size();
        cout<<"\ndummy size: "<<dummy.size();
        cout<<"\n";
    }
    arr[TOS] = element;
    TOS++;
}

template <typename T>
T pop(vector<T>& arr){
    int element = arr[TOS - 1];
	arr[TOS - 1] = 0;
	TOS--;
	return element;
}

int main(){

    vector<int> org = {1,2,3};
    vector<int> cp = getCopy(org);

    cout << org.size() << endl;
	cout << cp.size() << endl;

	TOS = org.size();

	for (int i = 10; i < 20; i++) {
		push(org, cp, i);
	}

	cout<<"Before undo : \n";
	printArr(org);
	printArr(cp);

	undo(org, cp);

    cout<<"After undo : \n";
	printArr(org);
	printArr(cp);

    return 0;
}

