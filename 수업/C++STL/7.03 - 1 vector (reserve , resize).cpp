#include <iostream>
#include <vector>


using namespace std;




int main()
{

	////#1 재할당, 복사 확인
	//vector<int> vec;
	//for (int i = 0; i < 10; i++)
	//{
	//	vec.push_back(1);
	//	cout<<"Address : " << &vec[0] <<endl;
	//	cout<<"size : " <<vec.size() <<endl;
	//	cout<<"capacity : " << vec.capacity() <<endl;
	//	cout << "=================" << endl;
	//}


	////##2 메모리 예약 reserve
	//// vector의 속도를 개선하게 위해서는 reserve로 메모리를 예약해서 사용하는 습관이 있어야한다.
	//// 넉넉한 메모리를 잡아두면 벡터의 재할당을 막을 수도 있다.
	//// 벡터는 유한한 데이터를 다룰떄 (삽입될 갯수가 정해져 있을때) 좋은 컨테이너다.

	//vector<int> vec;
	//vec.reserve(10);
	//cout << "size : " << vec.size() << endl;
	//cout << "capacity : " << vec.capacity() << endl;
	//for (int i = 0; i < 10; i++)
	//{
	//	vec.push_back(1);
	//	cout << "Address : " << &vec[0] << endl;
	//	cout << "size : " << vec.size() << endl;
	//	cout << "capacity : " << vec.capacity() << endl;
	//	cout << "=================" << endl;
	//}

	//##3 메모리 예약 resize
	//사용자가 예약한 공간에 대해서 원소도 같이 채워주는 함수.
	//이때 모든 원소들은 0초기화 상태다	클라스일경우 디폴트 생성자 초기화 된다.
	vector<int> vec;
	//vector<int> vec(10) resize와 같은 효과
	vec.resize(10);			//원소 갯수를 미리 채운다.
	cout << "Address : " << &vec[0] << endl;
	cout << "size : " << vec.size() << endl;
	cout << "capacity : " << vec.capacity() << endl;
	cout << "=================" << endl;





	
	return 0;
}