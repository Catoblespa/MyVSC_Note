#include <iostream>
#include <typeinfo>
using namespace std;


/*
	템플릿을 활용해서 배열길이를 알수없는 걸 인자로 받기!!
*/



//클래스 템플릿
template<typename T>
class CPoint
{
	T m_X;
	T m_Y;
};

template <typename T, int size = 5>	//템플릿 안에 디폴트값 넣어줄수 있다.
class CArray
{
private:
	T m_Array[size];		//템플릿이라서 가능하다! 아직 코드가 만들어지기 전이니까! 
							//size에 들어갈 값이 확정되면 그때 코드 생성된다!
};




template <typename T>
class CAdd
{
public:
	T operator()(T a, T b)
	{
		return a + b;
	}
};


//##1 클래스 템플릿 특수화
template<>
class CAdd <char*>
{
	char* operator()( char* a,  char* b)
	{
		int iTotal = strlen(a) + strlen(b);

		char* pName = new char[iTotal + 1];

		strcpy_s(pName, iTotal + 1, a);
		strcat_s(pName, iTotal + 1, b);

		return pName;
	}

};




int main()
{

	//템플릿 클래스
	CPoint<int> intPos;		//이 때 int에 대한 코드가 생성 (컴파일 시점)
	CPoint<float> floatPos;	//이 때 float에 대한 코드가 생성 (컴파일 시점)


	CArray<int> array1;			//int타입 5크기 배열을 갖게 된다
	CArray<float, 10> array2;	//float 타입 10크기 배열을 갖게 된다.


	CAdd<int> funcotr1;
	cout << funcotr1(10,20	) << endl;


	CAdd<char*> functor2;
	cout << functor2("Hello", "Whorld" )<< endl;

	return 0;
}