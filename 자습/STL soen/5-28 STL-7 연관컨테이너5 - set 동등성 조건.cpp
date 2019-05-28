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

template<typename C> void dump(const char* desc, C c) {
	cout.width(12); cout << left << desc << "==> ";

	copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " ")); cout << endl;
}

/*
*****************동등성 조건*****************

디폴트 비교 함수 객체인 less는 키 비교를 위해 < 연산자를 사용하며 greater로 바꿀 경우는 > 연산자가 필요하다.
 비교 함수 객체를 직접 만들 때도 크다 또는 작다 둘 중의 하나로 전후 관계를 분명히 판별하는 식으로 작성해야 한다.
 정렬을 위한 위치를 판별하는데 == 연산자는 별반 쓸모가 없다.
  왜냐하면 이분 검색이 가능하기 위해서는 상등 비교가 아닌 대소 비교를 여러 번 해야 하기 때문이다.
  정렬이란 상대적인 순서를 정하는 연산이므로 같다는 조건은 필요가 없다.

비슷한 이유로 >=, <= 같은 조건도 사용할 수 없다.
이 두 조건은 실제로는 두 조건의 OR 결합이기 때문에 키의 분명한 전후 관계를 판별하는데는 쓸 수 없기 때문이다.
<=연산자로 키를 비교해서 true라는 결과가 나왔다 하더라도 같아서 ture인지 작아서 true인지를 알 수 없으므로 애매모호한 것이다.

<= 연산은 확정적이지 못하므로 셋이 정신을 못차리고 엉뚱한 비교를 해 대며 그러다 보니 같은 값도 다르다고 판단하여 중복 삽입되는 것이다.
그래서 셋은 < 아니면 > 두 연산자 중 하나로만 비교해야 한다.
둘 중 어떤 것을 쓰나 상관은 없는데 사람들은 보통 오름차순을 더 좋아하므로 디폴트 비교 객체는 less로 선택되어 있다.


그런데 이분 검색중에 범위를 좁혀 나갈 때는 < 미만 비교 연산자만으로도 충분하지만
검색을 할 때는 정확하게 같은 것이 있는지 조사해야 하므로 == 연산이 필요하다.
그러나 셋은 == 연산을 요구하지 않으며 대신 < 연산의 조합으로 검색할 키를 찾는다.

여기서 동일성과 동등성의 개념이 나누어진다.
	■ 동일성(equality) : 두 값이 완전히 같은지 검사한다. 객체의 경우 모든 멤버가 일치해야 동일하며 주로 == 연산자를 사용한다.
	■ 동등성(equivalance) : 두 값이 같은 값으로 인정되는지 검사한다. 키에 해당하는 값만 비교하며 < 연산자의 조합으로 정의된다.


동일성은 두 값이 완전히 같다는 뜻이고 동등성은 두 값이 집합의 기준에서 볼 때 같다고 인정된다는 뜻이다.
STL에서 두 키 a와 b의 동등성은 다음 조건으로 점검한다.
	!(a < b) && !(b < a)
 동등성을 표현하는 이 조건은 비교 객체가 디폴트인 less일 때의 얘기이고
 좀 더 일반적으로 얘기하자면 비교 객체가 Comp일 때 다음 조건을 만족해야 두 키가 동등하다고 한다.
	!Comp(a,b) && !Comp(b,a)

순서를 바꿔가며 비교해 봐도 둘 다 거짓일 때만 동등하다. 셋의 insert 함수는 삽입 위치를 결정하기 위해 동등성의 개념을 사용한다

*****************키 변경 불가 원칙*****************

셋은 요소를 정렬할 때 항상 키값을 기준으로 하며 검색할 때도 키값의 대소를 판별하여 이분 검색한다.
객체의 어떤 멤버가 키인가는 객체마다 다를 수 있는데 동등성 비교에 사용되는 모든 멤버가 키라고 할 수 있다.
키는 셋이 요소의 순서를 정하기 위해 사용하는 중요한 값이므로 셋에 이미 들어가 있는 키를 변경해서는 안된다.

*/

class President
{
public:
	int Id;
	string Name;
	string Addr;
	President(int aId, const char* aName, const char* aAddr) : Id(aId), Name(aName), Addr(aAddr) { }

	void OutPresident() const
	{
		printf("Id:%d, 이름:%s, 주소:%s\n", Id, Name.c_str(), Addr.c_str());
	}

	//동등성 비교를 위한 operator.    a>b, a<b 모두 false일때 a와 b는 동등성을 가진다.
	bool operator<(const President& Other) const // 이 씨1발. STL에서는 상수성 함수가 가능하다 판단될땐 꼭 const쓰자 ㅅㅂ개년들이 안쓰면 애러난다.
	{
		return Id < Other.Id;
	}

	//set은 연산에 동일성 검사를 하지 않으므로, 해당 operator==을 삭제해도 잘 작동한다.
	bool operator==(const President& Other) const
	{
		return (Id == Other.Id && Name == Other.Name && Addr == Other.Addr);
	}
};


int main()
{

	set<President> King;


	King.insert(President(516, "박정희", "동작동"));
	King.insert(President(1212, "전두환", "연희동"));
	King.insert(President(629, "노태우", "강북"));
	King.insert(President(3030, "김영삼", "상도동"));
	King.insert(President(1234, "김대중", "강남"));


	//cout << sizeof(King) << endl;

	set<President>::iterator it;

	for (it = King.begin(); it != King.end(); it++)
	{
		(*it).OutPresident();
	}
	//별다른 비교 함수 객체를 지정하지 않았으므로 디폴트 비교 함수 객체인 less가 사용되며 
	//따라서 실제 비교에는 객체의 < 연산자가 사용된다. 
	//< 연산자가 Id로 비교를 수행하므로 Id의 오름차순으로 정렬되며 같은 Id를 가지는 요소는 삽입이 거부된다.
	//출력해 보면 순서를 아무렇게나 삽입했지만 Id순으로 정렬되어 들어감을 확인할 수 있다.
	//즉 여기서 set은 <연산자로 정렬을 하며, 중복개체를 제거할때, <를 사용한 동등성을 계산하여 판단한다.


	President ZeroThree(3030, "아무개", "아무데나");
	it = King.find(ZeroThree);	
	//find 멤버 함수가 이분 검색을 하면서 < 연산자만을 사용하여 동등성을 비교하기 때문이다.
	//그러므로 Zeorothree와 id가 같은것을 찾아 반환한다.
	if (it != King.end())
	{
		cout << "검색되었음" << endl;
		(*it).OutPresident();
	}

	it = find(King.begin(), King.end(), ZeroThree);
	//전역 맴버 함수 find는 동등성 검사를 한다. king set에서 ZeoroThree를 즉 찾지 못한다.
	if (it != King.end())
	{
		cout << "검색되었음" << endl;
		(*it).OutPresident();
	}

	//*it = President(1515,"asd","afq"); 안됨!!!

	return 0;
}
