#include <iostream>
#include <time.h>
#include <random>		//mt19937 Random을 사용하기 위해 필요한 해더
#include <chrono>		//시드값을 사용하기 위해 인클루드

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;

/*
난수 생성기: 어떻게
난수 분포기: 형(type), 범위


보안 등의 목적으로 절대 예측할 수 없는 진정한 의미의 난수를 생성하기 위
해서는 비 결정적 난수 생성기를 사용해야 한다.
- std::mt19937는 의사 난수


random_device
비 결정적인 난수를 생성하므로 다른 의사 난수 생성 엔진의 시드 초기화나
암호화 용도로 사용할 수 있다

random_device는 Mersenne twister와 달리 예측 불가능한 난수를 생성해야
하므로 소프트웨어로 구현하지 않고 하드웨어 리소스를 사용하여 만든다.
예) 하드웨어 노이즈나 마우스 움직임 등을 사용.
*/


int main()
{
	// 시드 사용하기 위해 
	auto curTime = std::chrono::system_clock::now();
	auto duration = curTime.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	mt19937 mtRand(millis);		//난수 생성기
//	mt19937_64 mtRand64; // 64비트 버젼

	for (int i = 0; i < 7; ++i)
	{
		cout << mtRand() << endl;		//호출마다 난수 생성
	}




	cout << "=========" << endl;
	random_device rng;
	for (int i = 0; i < 7; i++)
	{
		auto result = rng();
		cout << result << endl;
	}

	/*
	난수를 특정 타입과 특정 범위 안에서 생성하기 위해서는 난수 생성기에 난수분포기를 더하여 난수를 생성한다.
	정수 타입의 난수를 분포 할 때는 uniform_int_distribution,
	실수 타입은 uniform_real_distribution을 사용한다

	uniform_int_distribution dist와 std::uniform_real_distribution는 포함 범위가 다르므로 주의해야 한다.

		std::uniform_int_distribution dist(-3, 3)
		-3 이상, 3

		std::uniform_real_distribution<double> dist(0.0, 1.0)
		0.0 이상, 1.0 미만의 범위다.


	여러가지 분포기 

	bernoulli_distribution 분포기				:	확률을 지정하면 이 확률에 근거하여 true와 false를 반환한다.
		예) ‘몬스터를 잡으면 n%의 확률로 XX 아이템을 드롭시켜라’.

	binomial_distribution 난수 분포기			:	특정 확률로 n회 실시 했을 때 몇 번 성공할 것인가를 반환.
		예) 사망 가능성(확률)이 있는 백신을 N 사람에게 투여할 때 살 수 있는 사람의 수를 구해라.

	normal_distribution 난수 분포기				:	평균과 표준편차로 정규 분포 난수를 생성한다.
		예)’평균 키 173cm, 표준편차 5cm’의 신장 데이터 생성
*/
	// 잘 모르겠다 연구 필요
	//int ia = -3;
	//int ib = 3;
	//uniform_int_distribution<__int64> dist1(ia, ib);
	//cout << "dist 최소 값 :" << dist1.min << endl;
	//cout << "dist 최대 값 :" << dist1.max << endl;

	//for (int i = 0; i < 7; ++i)
	//{	
	//	cout << dist1(rng) << endl;
	//}


	return 0;
}



/*



*/