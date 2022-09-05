#include <iostream>

using namespace std;

int fibonacci(int arr[],int n) {
	if (n <= 1) {
		return 1;
	}		
	else {
		if (arr[n] == 0) {
			arr[n] = fibonacci(arr, n - 1) + fibonacci(arr, n - 2);
			return arr[n];
		}
		else {
			return arr[n];
		}
	}
}

int hannoi(int num, char start, char dest, char via) {

	static int count = 0;

	if (num == 1) {
		cout << num << "원반을" << start << "에서" << dest << "로" << endl;
		count++;
	}		
	else {
		hannoi(num - 1, start, via, dest);
		cout << num << "원반을" << start << "에서" << dest << "로" << endl;
		count++;
		hannoi(num - 1, via, dest, start);
	}

	return count;
}

int main() {
	int n;
	cin >> n;

	/*int arr[100] = { 0, };

	cout << fibonacci(arr, n) << endl;*/

	cout << hannoi(n, 'A', 'B', 'C') << endl;

	return 0;
}