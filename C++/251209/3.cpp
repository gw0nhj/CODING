//동적 할당 new, delete 연습

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main() {
    int arr_size;
    cout << "Write size of Array: ";
    cin >> arr_size;
    
    int *arr = new int[arr_size];
    for(int i = 0; i < arr_size; i++) {
        cin >> arr[i];
    }

    for(int i = 0; i < arr_size; i++) {
        cout << arr[i] << " ";
    }

    delete[] arr;

    return 0;
}