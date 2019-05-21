#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>

using namespace std;


class Graphic
{
public:
	//virtual을 사용하지 않으면 Graphic *는 모두 Graphic::Draw()을 호출한다앗!!
	// void Draw() { puts("그래픽 오브젝트입니다."); }
	virtual void Draw() { puts("그래픽 오브젝트입니다."); }
};



class Line : public Graphic
{
public:
	void Draw() { puts("선을 긋습니다."); }
};



class Circle : public Graphic
{
public:
	void Draw() { puts("동그라미 그렸다 치고."); }
};


class Rect : public Graphic
{
public:
	void Draw() { puts("요건 사각형입니다."); }
};


//만약 Triangle 클래스가 Graphic의 자식 클래스로 늘어나더라도 동적으로 추가 되는 ar[]배열의 리스트 들에 대해 ->Draw() 하는 함수가 있을경우,
// 그 함수를 수정할 필요가 없어 진다.
class Triangle : public Graphic
{
public:
	void Draw() { puts("나는 새로 추가된 삼각형이다."); }

};


// 이 예제는 객체의 집합을 관리하기 위해 크기 10의 Graphic *형 배열을 선언하고 이 배열에 Graphic 파생 클래스의 객체 포인터를 저장했다. 
//부모형의 포인터가 자식 객체를 가리킬 수 있으므로 최상위 클래스인 Graphic의 포인터 배열을 선언하면 모든 그래픽 객체의 집합을 관리할 수 있다.

//이때 Graphic *는 모든 자식 클래스를 대표하는 대표 타입이며 이 타입의 배열은 모든 자식 객체들의 번지를 저장할 수 있다. 
// 실제 프로그램이라면 이 배열의 크기는 동적으로 관리될 것이고 배열내의 객체들을 편집하는 기능을 제공해야 할 것이다. 
//예제의 ar 배열 초기식은 사용자가 이런 객체들을 만들어 놓은 상황을 가정하기 위한 것이다.

int main()
{
	//이 예제에서는 ar[]베열을 직접 초기화 했지만, 실제로는 동적배열이고, 언제 어느 타입이 담길지 모른다고 가정하자.
	Graphic* ar[10] = {
		 new Graphic(),new Rect(),new Circle(),new Rect(),new Line(),
		 new Line(),new Rect(),new Line(),new Graphic(),new Circle() };
	
	int i;

	for (i = 0; i < 10; i++)
		ar[i]->Draw();

	for (i = 0; i < 10; i++)
		delete ar[i];
	//만약 동적 결합을 하는 가상 함수라는 장치가 없다면 똑같은 호출로 다양한 도형을 그릴 수가 없다.
	//각 객체에 스스로의 타입을 판별할 수 있는 별도의 열거형 멤버를 추가하고 이 멤버로부터 타입을 판별하여 자신을 그릴 멤버 함수를 결정하는 다중 분기를 해야 할 것이다.
	/*for (i = 0; i < 10; i++)					//이렇게 말이다.
	{											//뿐만 아니라 도형의 종류가 늘어나면, switch 문의 case도 늘려줘야한다.
												// 그리되면 수정에 대해 코드를 관리하기 매우 어려워진다.
		switch (ar[i].Type)										
		{
		case GR_GRAPHIC:
			((Graphic*)ar[i])->Draw();
			break;

		case GR_LINE:
			((Line*)ar[i])->Draw();
			break;

		case GR_CIRCLE:
			((Circle*)ar[i])->Draw();
			break;
		case GR_RECT:
			((Rect*)ar[i])->Draw();
			break;
		}
	}*/
	// 이에 비해 가상 함수는 호출 객체에 따라 선택되는 동적 결합 능력이 있으므로
	//ar[i]->Draw() 호출만 하면 Graphic 파생 클래스에 대해서는 모두 정확하게 동작할 뿐만 아니라
	//미래에 새로운 클래스가 추가되더라도 이 코드는 더 이상 고칠 필요가 없어진다. 과연 그런지 삼각형 도형을 추가해 보자.

	return 0;

}