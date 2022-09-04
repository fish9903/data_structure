// Palindrome
// 2018112072_����ȣ
#include "stackarr.cpp"

template<class DT>
bool is_Palindrome(DT* word)
{
	int size = 0;
	for (int i = 0; word[i] != '\0'; i++)
	{
		size++;
	}

	if (size == 1)
		return true;

	Stack<DT> stack(size);

	for (int i = 0; i < size; i++)
	{
		stack.push(word[i]);
	}

	for (int i = 0; i < size; i++)
	{
		if (stack.pop() != word[i])
			return false;
	}
	return true;
}

template<class DT>
int delete_index(DT* word)
{
	int size = 0;
	for (int i = 0; word[i] != '\0'; i++)
	{
		size++;
	}

	if (size == 1)
		return true;

	Stack<DT> stack(size);

	for (int i = 0; i < size; i++)
	{
		stack.push(word[i]);
	}

	for (int i = 0; i < size; i++)
	{
		// pop���� ���� �Ͱ� word�� �ش� index�� ���� �ٸ��ٸ�
		if (stack.pop() != word[i])
		{
			// pop���� ���� �Ͱ� word�� �ش� index�� �� ���� �ϳ��� �����ؾ� ȸ���̵ȴ�.
			// ���� index�� ���� �����ؼ� ȸ���̸� ����index�� ��ȯ, �ƴϸ� ���� index�� ��ȯ�Ѵ�.
			for (int j = i; j < size - 1; j++)
			{
				word[j] = word[j + 1];
			}
			word[size - 1] = '\0';

			if (is_Palindrome(word))
				return i;
			else
				return size - 1 - i;
		}
	}

	return -1;
}

int main()
{
	char* word = new char[100]; // �ִ� 100����

	cout << "Enter the word" << endl;

	cin >> word;

	//if (is_Palindrome(word))
	//	cout << "Yes" << endl;
	//else
	//	cout << "No" << endl;

	cout << delete_index(word) << endl;

	return 0;
}