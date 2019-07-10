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
Given an array of integers, return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1]
*/


vector<int> twoSum(vector<int>& nums, int target) {
	vector<int> temp;

	int iA=-1, iB=-1;
	for (int i = 0; i < nums.size(); i++)
	{
		for (int j = i+1; j < nums.size(); j++)
		{
			if (target == nums[i] + nums[j])
			{
				iA = i;
				iB = j;
				//cout << iA << ", " << iB << endl;
				break;
			}
		}
	}
	if (-1 == iA)
	{
		cout << "찾을 수 없음" << endl;
	}
	temp.push_back(nums[iA]);
	temp.push_back(nums[iB]);
	return temp;
}

int main()
{
	vector<int> vi;
	vi.push_back(2);
	vi.push_back(7);
	vi.push_back(11);
	vi.push_back(15);

	vector<int> sum = twoSum(vi, 9);

	cout << sum[0] << "+" << sum[1] << ":" << sum[0] + sum[1] << endl;
	return 0;
}