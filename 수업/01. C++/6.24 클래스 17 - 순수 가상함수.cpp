#include <iostream>
using namespace std;



class CFigure // 순수가상함수를 가지고있으면 '추상클래스'가 된다.
{
public :
	virtual ~CFigure()
	{
	}

public:
	virtual void Draw() = 0; //순수 가상함수
};


class Ctriangle : public CFigure
{
public:
	virtual ~Ctriangle()
	{
	}

public:
	//추상 클래스를 상속 받게 되면 순수 가상함수를 반드시 오버라이딩 해야한다!
	//오버라이딩하지 않으면 virtual void Draw() = 0; 을 그대로 물려 받으므로 이것도 추상클래스가 되어버린다.
	//즉 순수 가상함수는 자식 클래스에게 오버라이딩하도록 유도하는 문법이다.
	virtual void Draw()
	{
		cout << "삼각형" << endl;
	}
};

class CRectangle : public CFigure
{
public:
	virtual ~CRectangle()
	{
	}

public:
	//추상 클래스를 상속 받게 되면 순수 가상함수를 반드시 오버라이딩 해야한다!
	//오버라이딩하지 않으면 virtual void Draw() = 0; 을 그대로 물려 받으므로 이것도 추상클래스가 되어버린다.
	//즉 순수 가상함수는 자식 클래스에게 오버라이딩하도록 유도하는 문법이다.
	virtual void Draw()
	{
		cout << "사각형" << endl;
	}
};


int main()
{
	//순수 가상함수는 객체화 할수없다.
	//CFigure figure;

	//추상클래스는 객체화 할 수 없지만 포인터나 레퍼런스 타입으로는 사용 가능하다.
	CFigure* pFigure = new Ctriangle;

	pFigure->Draw();
	if(pFigure != nullptr)
		delete pFigure;


	pFigure = new CRectangle;
	pFigure->Draw();
	if (pFigure != nullptr)
		delete pFigure;
	return 0;
}