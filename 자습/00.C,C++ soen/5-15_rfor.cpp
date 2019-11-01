
#include <iostream>

using namespace std;

int main()
{
	int arr[100];

	cout << sizeof(arr)/sizeof(arr[0]) << endl;
	
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		arr[i] = i;
	}
    //arr의 요소중 arr[0]로 시작해서 끝 요소인 arr[99]가 number에 순서대로 담긴다.
	for (auto& number : arr)
	{
		cout << number << endl;
	}

	return 0;
}