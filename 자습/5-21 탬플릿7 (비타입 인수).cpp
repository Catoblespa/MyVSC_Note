#include <iostream>
#include <Windows.h>

using namespace std;


//타입 T와 티타입 정수형 상수 N을 쓰는 탬플릿 클래스.
template <typename T, int N>
class Array
{
private:
	T ar[N];
public:
	void SetAt(int n, T v) { if (n < N && n >= 0) ar[n] = v; }
	T GetAt(int n) { return (n < N && n >= 0 ? ar[n] : 0); }

};

template <int N>
void func(void)
{
	int ar[N];
	printf("배열 크기=%d\n", N);

}

int main()
{


	Array<int,5> ari;
	ari.SetAt(1, 1234);
	ari.SetAt(1000, 5678);				//ari의 범위를 넘어선 위치이기 때문에 값이 들어가지 않음
	printf("%d\n", ari.GetAt(1));
	printf("%d\n", ari.GetAt(5));


	//int a = 5;
	//Array<int, a> ari;			//클래스 선언문의 비타입 인수는 반드시 상수여야 하며 실행중에 값이 결정되는 변수는 인수로 사용할 수 없다. 
	//템플릿이란 컴파일러가 인수를 적용하여 컴파일 중에 클래스를 만들어 내는 형틀이므로 모든 정보를 컴파일 중에 알 수 있어야 한다. 
	//실행중에 없던 클래스를 만들어내는 기능이 아니라 컴파일 중에 구체화해야 하므로 변수는 쓸 수 없다. 물론 const int size=5; 로 상수 선언했다면 가능하다.


	func<5>();
	func<8>();

	return 0;
}

