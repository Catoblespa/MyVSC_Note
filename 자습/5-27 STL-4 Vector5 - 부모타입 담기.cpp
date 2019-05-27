#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>		
#include <iterator>		//여러 종류의 반복자의 정의 담음.

using namespace std;

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}


class Graphic
{
public:
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



void del(Graphic* g) { delete g; }

/*
vector의 활용
*/


int main()
{

	vector<int> vi;
	dump("최초", vi);
	for (int i = 1; i <= 8; i++) vi.push_back(i); dump("8개 추가", vi);
	vi.insert(vi.begin() + 3, 10); dump("3번째 자리에 10 삽입", vi);
	vi.insert(vi.begin() + 3, 11); dump("3번째 자리에 11 삽입", vi);
	vi.insert(vi.begin() + 3, 12); dump("3번째 자리에 12 삽입", vi);
	vi.erase(vi.begin() + 7); dump("7번째 요소 삭제", vi);

	/*
	같은 타입의 자료 집합을 관리해야 한다면 대부분의 경우 벡터가 탁월한 선택이 될 것이다. 
	그렇다고 해서 벡터가 반드시 같은 타입만 다룰 수 있는 것은 아니며 호환되는 타입의 집합을 다룰 수도 있다. 
	
	그래픽 오브젝트의 집합을 다루고 싶다면 최상위 클래스의 포인터를 저장하는 벡터를 선언하면 된다. 
	상속 계층의 클래스끼리는 타입 호환성이 있으므로 같은 타입이라고 봐도 무방하다. 
	다형성 실습에서 사용했던 객체 배열을 벡터로 작성해 보자.

	*/
	vector<Graphic*> vg;
	vg.push_back(new Graphic());
	vg.push_back(new Rect());
	vg.push_back(new Circle());
	vg.push_back(new Line());

	vector<Graphic*>::iterator it;

	for (it = vg.begin(); it != vg.end(); it++) 
	{
		(*it)->Draw();
	}
	for_each(vg.begin(), vg.end(), del);
	//vector<Graphic *> 타입은 Graphic으로부터 파생된 클래스의 집합을 다룰 수 있는 벡터이다. 
	//크기에 무관하고 삽입, 삭제가 자유롭고 STL 알고리즘의 도움을 받을 수도 있다.
	//단, 앞에서 얘기했다시피 벡터는 포인터만 관리할 뿐 포인터가 가리키는 객체까지 관리하지는 않으므로 벡터가 파괴되기 전에 객체들은 직접 삭제해야 한다.

	//컴퓨터가 가장 잘 하는 일은 비슷한 일을 아무 불평없이 처리하는 반복이며 반복을 위해서는 같은 타입의 변수 집합을 다룰 일이 아주 많다. 
	//모든 프로그램은 이런 타입의 집합을 다루므로 벡터가 특히 더 실용적이며 매력있는 컨테이너이다. 
	//벡터만 자유 자재로 활용할 수 있다면 다른 자료 구조는 모르더라도 왠만한 프로그램은 다 만들 수 있는 정도다.



	return 0;
}

