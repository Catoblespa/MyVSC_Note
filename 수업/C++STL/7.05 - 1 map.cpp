// ConsoleApplication2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


// ## map 의 특징
//	1.자가 균형 이진 탐색트리를 기반으로 한다 (레드 블랙 트리)
//	2. 표준 연관 컨테이너
//	3. list 와 같은 노드 기반 컨테이너 이지만 , 탐색속도가 월등하다
//	4. 원소 하나가 key , value 한쌍을 이룬다
//	5. 원소를 삽입할때마다 key를 기준으로 정렬이 일어난다. 그러므로 삽입속도가 존나게 느리다
//	6. 중복 key를 허용하지 않는다.
//	7. 노드 기반이지만, key를 통해 인덱스연산[]을 할 수 있다. 
			//(배열과 다르게 , 탐색을 하는 연산이다 operator[]로 오버로딩 되어 있다.
//  8. 한번 삽입된 key는 수정 할 수 없다. 수정하고 싶다면 해당 key를 삭제하고 삽입해라
//	9. 단. value는 수정가능.



int main()
{
	//// ## 1 map의 선언	////////////////////////////////////////////////
	////key 타입은 대소 비교가 가능한 자료형 이여야 한다.
	//map<int, int> MyMap1;
	//map<float, int> MyMap2;
	//map<string, int> MyMap3;
	//map<double, int> MyMap4;

	////오름차순을 사용하는 Map
	//map<int, int, greater<int>> MyMap5;



	//// ##2 pair 객체		////////////////////////////////////////////////
	//// map 의 원소는 pair 구조체로 이루어져 있다.
	//map <int, int > myMap;
	//myMap.insert(pair<int, int>(1, 2));


	////// ##3 map의 데이터 삽입		////////////////////////////////////////////////
	//map<int, int > Mymap;

	//pair<int, int> myPair(2, 200);
	//Mymap.insert(myPair);						// 방법 1 :삽입시 pair 객체를 전달.
	//Mymap.insert(pair<int, int>(1, 100));		// 방법 2 : 임시 객체 활용
	//pair<int, int> MyPair2 = make_pair(5, 500);	// 방법 3 :make_pair 함수 를 활용하여 pair 생성
	//Mymap.insert(MyPair2);
	//Mymap.insert(make_pair(4, 400));			// 방법 4 :make_pair를 써서 바로 전달!!!!!!!

	////typedef pair<const key, type> value_type
	////map의 키값은 const를 갖는 상수다. 한번 들어가면 변경이 불가능한데,
	////위의 삽입 방식은 key값에 const를 안했으므로, 묵시적 형변환이 일어난다.
	////pair의 타입을 잘못 써줄때도 묵시적 형변환이 일어난다.
	////묵시적 형변환이 일어나지 않도록 value_type를 사용하는것이 가장 안전하다.
	//map<int, int>::value_type MyPair3(6, 600);
	////	MyPair3.first = 7;	 키값 수정 불가!
	//Mymap.insert(MyPair3);
	//Mymap.insert(map<int, int>::value_type(7, 700));		//방법 5 : value_type 을 사용하여 삽입.
	//

	////map 은 삽입할 때마다 key를 기준으로 정렬을 수행한다.
	//// 그러믈 map은 정적으로 삽입되어 있을 컨테이너로 사용할때 적합하다.
	//// 동적으로 넣으면 쥰내 느리다. 해봐서 안다.  개느리다.
	//for (map<int,int>::value_type element : Mymap)
	//{
	//	cout << "key	: "<<element.first << endl;
	//	cout << "value	: "<<element.second << endl;
	//}





	////// ##4 map의  [] (인덱스) 연산		////////////////////////////////////////////////
	//key값을 통해 인덱스 연산이 가능하도록 오버로딩이 되어 있음.
	// 이는 연속된 배열과 같은 인덱스 연산이 아니라,  단순 이진탐색을 의미한다.
	//map<int, int> Mymap;
	//Mymap.insert(pair<int, int>(3,300));
	//Mymap.insert(pair<int, int>(2,200));
	//Mymap.insert(pair<int, int>(1,100));

	//cout << "Mymap.begin()->first : "<<Mymap.begin()->first << endl;		//오름차순 했을때 가장 작은값(가장 왼쪽에 있는값)이 begin이 된다.
	//cout << "Mymap[1]" <<Mymap[1] << endl;		//key값으로 인덱스 연산을 하면 &value를 반환한다.
	//
	//Mymap[1] = 1000; //인덱스연산으로 value수정
	//cout << "Mymap.begin()->second : "<< Mymap.begin()->second << endl;		
	//cout << "size : " << Mymap.size() << endl;
	//cout << " ======================================" << endl;
	//
	//cout << "Mymap[5];" << endl;
	//Mymap[5];								//존재하지 않는 key값으로 인덱스 연산 수행시 원소를 새로 만들어 버린다.
	//										// 이때 value는 0초기화
	//cout << "size : " << Mymap.size() << endl;
	//cout << " ======================================" << endl;
	//cout << "Mymap[6] =200;" << endl;
	//Mymap[6] =200;							//6번 key를 삽입하고 value값이 200을 갖게 한다.
	//										// 이때 value는 0초기화
	//cout << "size : " << Mymap.size() << endl;
	//cout << " ======================================" << endl;

	//cout << " ===============Mymap===================" << endl;

	//for (map<int,int>::value_type element : Mymap)
	//{
	//	cout << "key	: "<<element.first << endl;
	//	cout << "value	: "<<element.second << endl;
	//	cout << "-----------------------------" << endl;
	//}




	////// ##5 map에서 중복 key insert		////////////////////////////////////////////////

	//map<int, int> Mymap;
	//
	//Mymap.insert(make_pair(1, 100));		//삽입 ok
	//Mymap.insert(make_pair(1, 200));		//삽입 No
	//Mymap.insert(make_pair(1, 300));		//삽입 No
	//Mymap.insert(make_pair(1, 100));		//삽입 No
	//
	//if (false == Mymap.insert(make_pair(1, 999)).second)	//insert는 pair를 반환하는데 , 
	//	cout << "이미 존재하는 키 !!" << endl;				//second에 bool타입을 반환한다.
	//cout << "size : " << Mymap.size() << endl;				//삽입 성공시 true, 실패시 false!!
	//cout << "value : " << Mymap[1] << endl;


	//////// ##6 map 원소 삭제		////////////////////////////////////////////////
	//map<int, int> Mymap;
	//Mymap.insert(make_pair(1, 100));		
	//Mymap.insert(make_pair(2, 200));		
	//Mymap.insert(make_pair(3, 300));		
	//for (map<int, int>::value_type element : Mymap)
	//	cout << element.first << "," << element.second << endl;

	//Mymap.erase(2);		//해당 key값의 원소를 제거!

	//for (map<int, int>::value_type element : Mymap)
	//	cout << element.first << "," << element.second << endl;



	return 0;
}

