#include <iostream>
#include <time.h>
#include <string>
#include <vector>		//STL Vector
#include <list>			//STL List
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	
#include <iterator>		//여러 종류의 반복자의 정의 담음.
#include <deque>		//STL deque 정의 헤더
#include <set>			//STL 연관컨테이너 set
#include <map>			//STL 연관컨테이너 map
#include <stack>		//STL 컨테이너 어댑터 stack
#include <queue>		////STL 컨테이너 어댑터 queue
#include <array>
#include <numeric>		//수치 관련 알고리즘 . STL이 아닌 C+라이브러리에 포함되어 있다.
#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;

/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
*/


class Solution {
public:
	list<int>* addTwoNumbers(list<int>* l1, list<int>* l2) 
	{
		list <int> temp;

		int _i = l1->size();

		for (int i = 0; i < _i; i++)
		{
			if (temp.size() != 0 && temp.front() == 20)
			{
				temp.pop_front();
			//	cout << l1->front() + l2->front() + 1 << endl;
				temp.push_front(l1->front() + l2->front() + 1);
			}
			else if (l1->front() + l2->front() >= 10)
			{
				temp.push_front((l1->front() + l2->front()) % 10);
				temp.push_front(20);
			}
			else
			{
				temp.push_front(l1->front() + l2->front());
			}

			l1->pop_front();
			l2->pop_front();

			
		}

		for (auto& i : temp)
		{
			cout << i <<" "<< endl;
		}


		return &temp;
	}

};

int main()
{
	Solution A;

	list<int> il1;
	list<int> il2;

	il1.push_back(2);
	il1.push_back(4);
	il1.push_back(3);

	il2.push_back(5);
	il2.push_back(6);
	il2.push_back(4);

	A.addTwoNumbers( &il1, &il2);
	return 0;
}