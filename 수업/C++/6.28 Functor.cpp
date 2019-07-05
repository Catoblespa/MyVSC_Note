#include <iostream>
using namespace std;



// ##1 함수객체 (Funcotr 함수자)
// ()함수호출 연산자를 오버로딩하여 마치 객체를 함수처럼 다룰 수 있다.

// 앞으로 함수포인터는 함수 객체로 대체된다


//1.일반함수가 가질 수 없는 맴버를 가질 수 있다.

//2.인라인이 가능하다
	// 함수 포인터는 함수가 메모리가 올라간 주소를 넘겨주는 것이므로 절대 인라인이 일어나지 않는다.
	// 함객체를 사용하면 기존 인라인을 못만들던 함수포인터 비해 빠를 수도 있다!
	
//3. 타입을 분명히 해야한다
	//함수포인터는 함수 형식으로 구분하기 때문에 인자 타입과 갯수만 맞으면 아무거나 막 넣을 수 있지만.
	//함수객체는 타입을 받기 때문에, 해당 타입이 맞는거만 넣을 수 있다. 밑의 bubble sort 함수의 경우
	// CSortRule 타입만 받을 수 있기때문에 신뢰성이 높다.

//4. 클래스가 가진 4대 속성을 모두 사용 할 수 있다.


class CAdd
{
public:
	//함수 호출 연산자 오버로딩은 매개변수 개수에 제한이 없다.
	int operator()(int a, int b)
	{
		return a + b;
	}
};

class CSortRule
{
public:
	virtual bool operator()(int a, int b)  const = 0;
};


//내림차순 펑터
class CGreater : public CSortRule
{
public:
	virtual bool operator()(int a, int b) const
	{
		return a > b;		//정렬 방향		
	}
};



//오름 차순 펑터
class Cless : public CSortRule
{
public :
	virtual bool operator()(int a, int b) const
	{
		return a < b;
	}
};


void BubbleSort(int ptr[], int lenght, const CSortRule& functor)
{
	for (int i = 0; i < lenght; i++)
	{
		for (int j = 0; j < lenght-1; j++)
		{
			if (functor(ptr[j+1], ptr[j]))
			{
				int iTemp = ptr[j];
				ptr[j] = ptr[j + 1];
				ptr[j + 1] = iTemp;
			}
		}
	}
}

int main()
{
	//CAdd functor;
	//cout << "10 + 20 = " << functor(10, 20) << endl;
	//Cless less;
	//CGreater greater;


	int arr[10] = { 3,2,1,6,5,4,9,8,7,10 };

	BubbleSort(arr, 10, CGreater());

	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}


	return 0;
}
