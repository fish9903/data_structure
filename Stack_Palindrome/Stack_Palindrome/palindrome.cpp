#include "stack.cpp"

bool isPalndrome(char* word) {
	Stack<char> stack(100);

	for (int i = 0; word[i] != NULL; i++) {
		stack.push(word[i]);
	}

	// ȸ�� �Ǻ� �ʿ�

	stack.showStack();

	return true;
}

int main() {
	char* word = new char[100];

	cout << "Enter the word >> ";
	cin >> word;

	isPalndrome(word);
}