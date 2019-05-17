#include <iostream>
#include <string.h>
using namespace std;


class constClass
{
private:
	string m_cName;
	const int m_ispeed;	//상수 맴버 변수
public:
	//상수 맴버변수는 이렇게 ! 초기화 해야한다.
	constClass(int i, string name) : m_ispeed(i)
	{
		m_cName = name;
	}

	void view()
	{
		cout << " m_cName  :" << m_cName << endl;
		cout << " m_ispeed :" << m_ispeed << endl;
	}
};

class refClass
{
private:
	string m_cName;
	int& m_ispeed;	//상수 맴버 변수
public:
	//레퍼런스 변수는 이렇게 ! 초기화 해야한다.
	refClass(int& i, string name) : m_ispeed(i)
	{
		m_cName = name;
	}

	void view()
	{
		cout << " m_cName  :" << m_cName << endl;
		cout << " m_ispeed :" << m_ispeed << endl;
	}
};

class Position
{
public:
	int x, y;
	Position(int _x , int _y)
	{
		x = _x;
		y = _y;
	}

};

class Some
{
public:
	Position Pos;
	Some(int x, int y) :Pos(x, y)
	{

	}

	void View()
	{
		cout << "Pos.x : "<< Pos.x<< endl;
		cout << "Pos.y : "<< Pos.y<< endl;
	}

};

int main()
{
	constClass constC(10, "Soooome");
	constC.view();

	int temp = 20;
	refClass refC(temp, "whooooo");		//래퍼런스 변수이므로 반드시 대상체가 와야 한다.
	refC.view();


	Some someOne(10, 20);
	someOne.View();

	return 0;
}