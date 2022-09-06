#include "stack.cpp"

bool isPalndrome(char* word) {
	Stack<char> stack(100);

	for (int i = 0; word[i] != NULL; i++) {
		stack.push(word[i]);
	}

	// 회문 판별 필요

	stack.showStack();

	return true;
}

int main() {
	char* word = new char[100];

	cout << "Enter the word >> ";
	cin >> word;

	isPalndrome(word);
}