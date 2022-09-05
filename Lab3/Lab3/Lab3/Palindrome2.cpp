// Palindrome
// 2018112072_조광호
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
		// pop에서 나온 것과 word의 해당 index의 값이 다르다면
		if (stack.pop() != word[i])
		{
			// pop에서 나온 것과 word의 해당 index의 값 둘중 하나를 삭제해야 회문이된다.
			// 앞쪽 index의 값을 삭제해서 회문이면 앞쪽index를 반환, 아니면 뒤쪽 index를 반환한다.
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
	char* word = new char[100]; // 최대 100글자

	cout << "Enter the word" << endl;

	cin >> word;

	//if (is_Palindrome(word))
	//	cout << "Yes" << endl;
	//else
	//	cout << "No" << endl;

	cout << delete_index(word) << endl;

	return 0;
}