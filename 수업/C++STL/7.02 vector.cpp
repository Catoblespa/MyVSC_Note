#include <iostream>
#include <vector>
using namespace std;


//stl vector
// 1. 동적 배열 기반 -> 연속된 메모리를 갖는다
// 2. 인덱스 접근(임의 접근) 가능 -> 탐색에 유리하다.
// 3. 포화상태에서 추가 삽입 시 재할당 , 복사 발생 -> 빈번한 추가 삽입에 대해 불리한 구조이다.

int main()
{
	// #1. vector의 선언

	//vector<int> vec1;
	//vector<float> vec2;
	//vector<클래스명> vec2;
	//vector<구조체명> vec2;
	//vector<열거체명> vec2;



	//#2 데이터 삽입
	vector<int> vec;

	

	//size : 현재 벡터가 저장하고있는 자료의 갯수
	//capacity :  현재 벡터가 저장 할 수 있는 최대 자료의 갯수.
	for (int i = 0; i < 30; i++)
	{
		//
		//capacity는 삽입시 공간이 부족할경우 현재 벡터 크기의 1.5배씩 증가한다 ->vector의 capacity 정책

		vec.push_back(i);
		cout <<"vec size     : "<< vec.size() << endl;
		cout <<"vec capacity : "<< vec.capacity() << endl;
		cout << "------------------" << endl;
	}

	// 데이터 출력
	//for (size_t i = 0; i < vec.size(); i++)
	//{
	//	cout << vec[i] << endl;
	//	cout << "------------------" << endl;
	//}
	//for (auto& i : vec)
	//{
	//	cout << i << endl;
	//}


	

	//#3 데이터 제거
	for (int i = 0; i < vec.size(); i++)
	{
		cout << "vec.back()   : " << vec.back() << endl;
		cout << "vec.pop_back " << endl;
		cout << "------------------" << endl;
		vec.pop_back();
	}



	//#4 empty함수

	if (vec.empty())
		cout << " 비어있음" << endl;
	else
		cout << "원소 있음" << endl;


	//# 6 모든 원소 제거

	vec.clear();
	cout << "     Clear    :" << endl;
	cout << "vec size     : " << vec.size() << endl;
	cout << "vec capacity : " << vec.capacity() << endl;
	cout << "------------------" << endl;

//*********************************************************
	//shrink_to_fit  함수  C++ 11부터 지원하는 함수
	//현재 capacity를 현재 size에 맞추는 함수.
	vec.shrink_to_fit();
	cout << "vec size     : " << vec.size() << endl;
	cout << "vec capacity : " << vec.capacity() << endl;
	cout << "------------------" << endl;

//*********************************************************


	// #6 두 컨테이너가 가진 것들을 교환하는 함수. 
	vector<int> vec1;
	vec1.push_back(10);
	vec1.push_back(20);
	vec1.push_back(30);

	vector<int> vec2;
	vec.push_back(30);
	vec.push_back(40);
	vec.push_back(50);
	vec1.swap(vec2);

	for (auto& i : vec2)
	{
		cout << i << endl;
	}

	//# front 와 back


	vector<int> vec3;

	vec3.push_back(10);
	vec3.push_back(20);
	vec3.push_back(30);

	//front는 원소중 가장 첫번째 원소의 레퍼런스 반환
	//back은 원소중 가장 마지막 원소의 레퍼런스 반환
	cout << "fornt of vec3 : " << vec3.front() <<endl;
	cout << "back  of vec3 : " << vec3.back() <<endl;


	vec3.front() = 500;
	vec3.back() = 100;

	for (auto& i : vec3)
	{
		cout << i << endl;
	}




	return 0;
}
