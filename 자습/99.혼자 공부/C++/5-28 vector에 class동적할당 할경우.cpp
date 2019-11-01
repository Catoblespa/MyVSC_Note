#include <iostream>
#include <time.h>
#include <string>
#include <vector>		//STL Vector
#include <list>			//STL List
#include <map>			//STL Map
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	
#include <iterator>		//여러 종류의 반복자의 정의 담음.
#include <deque>		//STL deque 정의 헤더
#include <set>

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;

class Object
{
	friend struct objSort;
	friend struct OutObject;
	friend struct objfind;

	struct Pos {
	public:
		int x, y;
		Pos() { x = 0, y = 0; }
		Pos(int x, int y ) :x(x), y(y){}
	};

private:
	Pos pos;
public:
	Object() { pos.x = 0; pos.y = 0; };
	Object(int _x, int _y) : pos(_x,_y) {}

	void OutObject () const
	{
		cout << "X: " << pos.x << "," << "Y : " << pos.y << endl;
	}
};

struct OutObject
{
	void operator()(Object* a) const
	{
		a->OutObject();
	}
};

struct objfind
{
private :
	int _x, _y;
public:
	objfind(int x, int y) : _x(x), _y(y) {};
	bool operator()(const Object* a) const
	{
		return _x == a->pos.x && _y == a->pos.y;
	}
};


struct objSort
{
	bool operator() (Object* a, Object* b)const
	{
		return a->pos.x < b->pos.x;
	}
};

void dump(const char* desc, vector<Object*> c) {
	cout.width(12); cout << left << desc << "==> ";
	for_each(c.begin(), c.end(),OutObject());
}
int main()
{
	vector<Object*> vo;
	vector<Object*>::iterator it;

	vo.push_back(new Object(10, 10));

	randomize();	//초기화
	for (int i = 0; i < 10; i++)
	{
		vo.push_back(new Object(random(50), random(50)));
	}


	dump(" sortbefore", vo);
	cout << "before" << endl;
	//for (it = vo.begin(); it != vo.end(); it++)
	//{
	//	(**it).OutObject();
	//}


	sort(vo.begin(), vo.end(), objSort());
	cout << "after" << endl;
	//for (it = vo.begin(); it != vo.end(); it++)
	//{
	//	(**it).OutObject();
	//}
	dump("sort after", vo);


	it = find_if(vo.begin(), vo.end(), objfind(10,10));

	cout << "find 10,10" << endl;
	(**it).OutObject();
	return 0;
}
