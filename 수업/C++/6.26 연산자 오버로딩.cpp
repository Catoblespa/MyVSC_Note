#include <iostream>
using namespace std;


/*
컴파일러가 자동으로 만들어주는 맴버함수
디폴트 생성자
디폴트 복사 생성자
디폴트 소멸자
**디폴트 대입 연산자**
*/


class CPoint
{
private:
	int m_iX;
	int m_iY;

public:
	CPoint() = default;

	CPoint(int x, int y)
	{
		m_iX = x;
		m_iY = y;
	}
	
	void Print()
	{
		cout << m_iX <<","<< m_iY << endl;
	}
public:

	CPoint&	operator +(const CPoint& op)const
	{
		int x = this->m_iX + op.m_iX;
		int y = this->m_iY + op.m_iY;
		return CPoint(x,y);
	}
	CPoint&	operator +(const int& num) const
	{
		int x = this->m_iX + num;
		int y = this->m_iY + num;
		return CPoint(x, y);
	}
	CPoint&	operator -(const int& num)const
	{
		int x = this->m_iX - num;
		int y = this->m_iY - num;
		return CPoint(x, y);
	}
	CPoint&	operator +=(const int& num)		//값을 변경하니까 const 붙히면 안됨.
	{

		this->m_iX += num;
		this->m_iY += num;
		return *this;
	}


	//대인연산자 컴파일러가 Default 대입연산자를 정의해준다!
	//아래는 디폴트 대입연산자 원형
	// 얕은 복사될 수도 있음! 주의!
	CPoint& operator= (const CPoint& obj)		//값을 변경하니까 const 붙히면 안됨.
	{
		m_iX = obj.m_iX;
		m_iY = obj.m_iY;
		cout << "대입연산자 호출!" << endl;
		return *this;
	}

		//축약 연산자 오버로딩
	//대입 연산을 내포하고 있기 때문에 반환과 인자는 대입연산자와 동일
	CPoint& operator +=(const CPoint& cp)		//값을 변경하니까 const 붙히면 안됨.
	{
		this->m_iX += cp.m_iX;
		this->m_iY += cp.m_iX;
		return *this;
	}


	
	//증감연산자 오버로딩
	//전위 연산자
	CPoint& operator++()
	{
		++m_iX;
		++m_iY;
		return *this;
	}
	//후위 연산자			
	//후위 연산자의 특징은  this의 사본을 반환한다!
	//인자에 int를 쓰는 이유는 전위연산자와 후위연산자를 구분하기 위한 표현이다.
	//객체에 대한 후위연산은 전위연산에 비해 더 느리다! 
	CPoint operator++(int)
	{
		CPoint tem(m_iX, m_iY);
		++m_iX;
		++m_iY;
		return tem;
	}
};

// 전역 연산자 오버로딩
// 전역으로 연산자를 오버로딩 하려면 인자중 하나는 객체이어야 한다.   
// 클래스 포인터는 포인터니까 안됨!
//=, [], () 연산자들은 전역으로 정의 할 수 없다.
CPoint operator+(int iMove, const CPoint& pos)
{
	return pos + iMove;
}
int main()
{
	CPoint pos1(500, 500);
	CPoint pos2(500, 500);
	CPoint pos3 = pos1 + pos2;
	pos3.Print();
	pos3 = pos3 + 1;
	pos3.Print();
	pos3 = 20 + pos3;
	pos3.Print();

	pos3 += 300;



	cout << "-----------" << endl;


	int a = 10;
	int b = 0;
	++(b = 10);			//대입연산의 반환은 왼쪽 피연산의 원형을 반환한다.
	cout << b << endl;	//그래서 11나옴 ㅎ

	CPoint pos4 = pos3;			//Default 복사 생성자 호출!
	pos4 = pos1;				//Default 디폴트 대입연산자 호출!
	pos3.Print();


	cout << "-------------------------" << endl;
	cout << "전위 , 후위 증감연산자 비교" << endl;
	CPoint _pos1(100, 100);
	CPoint _pos2 = ++pos1;
	pos2.Print();


	cout << "---------------" << endl;

	CPoint _pos3(100, 100);
	CPoint _pos4 = _pos3++;
	_pos4.Print();
	return 0;
}