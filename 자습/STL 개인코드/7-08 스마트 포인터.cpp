// ConsoleApplication2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//



/*
        https://blog.koriel.kr/cpp11-smart-pointer/
        참고
 */
#include "stdafx.h"
#include <memory>

class Object
{
private:
	static int count;

public:
	Object() 
	{ 
		count++; 
		ID = count;
	};
	int ID;
	virtual void Rend()
	{
		cout << ID << endl;
	}
};
int Object::count = 0;
class Block :public Object
{
public:
	virtual void Rend()
	{
		cout << ID*100 << endl;
	}
};


int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1365);      //누수 라인 중단점
	_CrtDumpMemoryLeaks();			//메모리 누수 출력 (디버그 모드)
	vector<auto_ptr<Object>> ptV;


	// 수동으로 pop하면 자동으로 소멸자가 호출되어 delete된다.. 
	//그러나 다른 참조 아래의 for_each, rfor 등등.. 이 오게 되면 값을유지안하고 NULL이 된다..
	ptV.push_back(auto_ptr<Object>(new Object));
	ptV.push_back(auto_ptr<Object>(new Object));
	ptV.push_back(auto_ptr<Object>(new Object));
	ptV.push_back(auto_ptr<Object>(new Block));
	ptV.push_back(auto_ptr<Object>(new Block));
	ptV.push_back(auto_ptr<Object>(new Block));



	//for_each(ptV.begin(), ptV.end(), [](auto_ptr<Object> a)
	//{
	//	a->Rend();
	//});
	//cout << "=================" << endl;

	//for (auto& i : ptV)
	//{
	//	i->Rend();
	//}

	//cout << "======================" << endl;
	//auto begin = ptV.begin();
	//auto end = ptV.end();
	//for (; begin != end; ++begin)
	//{
	//	(*begin)->Rend();
	//}

	while (true)
	{
		if (ptV.empty())
			break;
		ptV.pop_back();
	}



	cout << "shard_ptr" << endl;


	//vector<auto_ptr<Object>> ptV;
	vector<shared_ptr<Object>> sV;
	//shard_ptr은 컨테이너에 대해 중복 참조를 허용한다.
	//std::shared_ptr는 이름처럼 가리키는 객체의 소유권을 다른 포인터들과 공유할 수 있는 포인터다. 
	//std::unique_ptr과는 다르게 복사도 마음껏 할 수 있다. 같은 객체를 가리키는 std::shared_ptr은 레퍼런스 카운팅으로 추적된다. 
	//참조된 횟수를 세는 것이므로 포인터가 복사될 때 마다 1씩 증가한다. 
	//그리고 해제될 때 마다 1씩 감소한다. 
	//포인터가 가리키는 객체의 메모리가 해제되는 시점은 레퍼런스 카운트가 0이 될 때이다. 
	//레퍼런스 카운트는 use_count() 멤버 함수로 가져올 수 있다.

	sV.push_back(shared_ptr<Object>(new Object));
	sV.push_back(shared_ptr<Object>(new Object));
	sV.push_back(shared_ptr<Object>(new Object));
	sV.push_back(shared_ptr<Object>(new Block));
	sV.push_back(shared_ptr<Object>(new Block));
	sV.push_back(shared_ptr<Object>(new Block));


	cout << "sv.back()의 use_count() : " << sV.back().use_count() << endl;

	for (auto& i : sV)	// 쌉가능
	{
		i->Rend();
	}

	cout << "shared_ptr<Object> A = sV.back()"<<endl;
	shared_ptr<Object> A = sV.back();
	cout <<"A.use_count() :"<< A.use_count() << endl;
	return 0;
}
