#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
					
using namespace std;

/*
for_each 함수는 순회 중에 할 일을 결정하기 위해 반드시 함수 객체를 부르도록 되어 있다. 
순회만 할 바에야 for_each를 부를 필요가 없으므로 for_each에게 함수 객체는 필수적인 존재라고 할 수 있다.
이처럼 함수 객체를 명시적으로 요구하는 알고리즘도 있고 필요할 때만 함수 객체를 옵션으로 받는 알고리즘도 있다.

컨테이너에서 값을 검색하는 find는 순회중의 반복자 값과 세 번째 인수로 지정한 값(val)을 == 연산자로 비교하여 정확하게 일치하는 요소를 찾아낸다. 
그런데 때로는 ==로 정확한 일치를 검색하는 것이 아니라 사용자가 정의하는 방식으로 검색할 요소를 골라야 하는 경우도 있다.
이때 함수 객체로 요소를 직접 비교할 수 있는데 이런 함수는 보통 원래 함수의 이름 끝에 _if가 붙는다. 
find의 함수 객체 버전은 다음과 같다.
		// InIt find_if(InIt first, InIt last, UniPred F);

세 번째 인수 F는 () 연산자를 오버로딩하는 함수 객체이며 요소값 하나를 인수로 전달받아 이 값이 원하는 조건이 맞는지 검사하여 bool형을 리턴한다. 
찾는 조건에 맞으면 true를 리턴하고 아니면 false를 리턴할 것이다. 
이처럼 bool을 리턴하는 함수 객체를 특별히 조건자(Predicate)라고 부르는데 요소가 지정 조건을 만족하는지를 검사하는 역할을 한다. 

다음은 find_if를 활용한 검색 예제이다.
*/


struct IsKim {
	bool operator()(string name) const {
		return (strncmp(name.c_str(), "김", 2) == 0);
		//string.c_str() : 반환형이 const char *으로, string의 첫번째 문자의 주소값을 반환합니다.
		//strncmp = name.c_str()에서 뽑힌 name의 성씨가 "김"일경우 0을 반환한다.
		//즉 return에서는 strncmp에서 반환 값이 0과 같다면 true를 반환한다.
	}
};



int main()
{

	string names[] = { "김유신","이순신","성삼문","장보고","조광조",
		 "신숙주","김홍도","정도전","이성계","정몽주" };

	vector<string> vs(&names[0], &names[10]);

	vector<string>::iterator it;

	
																	//함수 객체를 직접 전달해도 된다.			
	it = find_if(vs.begin(), vs.end(), IsKim());					//IsKim K;								
	//'김'씨 성을 갖는 사람을 찾는다. 							  		//it = find_if(vs.begin(), vs.end(), K);
	//전체 이름을 다 검사하는 것이 아니라 이름의 일부만을 검사하므로	
	//find 함수로는 이 검색을 수행할 수 없다.	
	//IsKim()임시 함수객체가 '김'씨를 찾을 겨우 true를 반환한다.
	//find_if는 true를 반환받을경우 해당 vs요소의 주소를 it에 전달		//함수 포인터를 전달해도 작동한다.											
																	//bool IsKim(string & name)										
	if (it == vs.end())												//{										
		cout << "없다." << endl;										//	return (strncmp(name.c_str(), "김", 2) == 0);
	else 															//}
		cout << *it << "이(가) 있다." << endl;						 //it = find_if(vs.begin(), vs.end(), IsKim);
																	//이때는 IsKim 다음에 괄호를 적지 말아야 하는데 함수명 자체가 함수 포인터이므로 괄호가 붙을 필요가 없으며 붙어서도 안된다.
																	//위의 두 방법 모두 사용 가능하나, 함수 포인터를 전달할경우 비교할때마다 함수를 불러와야 하므로 오버해드가 엄청 커진다.

	//만약 최초의 김가만 찾는 것이 아니라 컨테이너내의 모든 김가를 다 검색하고 싶다면 
	//다 찾을 때까지 루프를 돌리면 된다.main의 코드를 다음과 같이 수정하면 모든 김가들이 다 검색된다.

	cout << "--김씨 모두 찾기" << endl;
	for (it = vs.begin();; it++) {				//it을 vs.begin() 부터 계속 ++
		it = find_if(it, vs.end(), IsKim());	//find_if로 현재 it위치부터 vs.end()까지 탐색. IsKim이 true일 경우 It에 전달. 이때 it은 검색하는동안 ++계속됨.
		if (it == vs.end()) break;				//만약 it이 vs.end() 까지 도달했을경우 반복문 빠져나온다
		cout << *it << "이(가) 있다" << endl;	//*it을 출력
	}
	//find는 템플릿으로 되어 있으므로 임의의 컨테이너에 대해 검색을 수행할 수 있는 일반성을 가진다. 
	//검색 대상을 템플릿 인수로 전달받으므로 인수로 검색 대상을 지정할 수 있다. 
	//find_if는 여기에 비교 방식까지도 인수로 전달받아 검색 조건이 무엇인가까지도 사용자가 지정할 수 있다. 
	//그래서 find보다 find_if가 훨씬 더 일반적이다.
	return 0;
}