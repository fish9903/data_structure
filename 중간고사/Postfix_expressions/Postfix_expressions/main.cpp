#include "stackarr.cpp"
#include <string>

using namespace std;

int main() {
	Stack<int> post;
	char cmd;
	
	cout << "Enter Postfix expression" << endl;
	
	while (true) {
		cin >> cmd;
		if (cmd == 'q' || cmd == 'Q') {
			break;
		}
		else if (cmd != ' ')
		{
			if (cmd == '+') {
				int num = 0;
				num += post.pop();
				num += post.pop();
				post.push(num);
			}
			else if (cmd == '-') {
				int num1 = post.pop();
				int num2 = post.pop();
				int num = num2 - num1;
				post.push(num);
			}
			else if (cmd == '*') {
				int num = post.pop();
				num *= post.pop();
				post.push(num);
			}
			else {
				post.push(cmd - 48);
			}
		}
		//post.showStructure();
	}

	post.showStructure();

	return 0;
}