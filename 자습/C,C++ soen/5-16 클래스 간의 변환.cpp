#include <iostream>


//Celsius에서 Fahrenheit를 사용해야하므로 프로토타입 선언.
class Fahrenheit;


// 섭씨 Class
class Celsius
{
public:
	double Tem;
	Celsius() { }
	Celsius(double aTem) : Tem(aTem) { }

	//변환 생성자를 사용하여 클래스 변환, 단 Celsius에서는 Fahernheit가 밑에 정의 되어 있어서 정확한 내부는 찾을 수 없으므로, 
	//클래스를 분할컴파일 할때만 가능!!
	//explicit Celsius(Fahrenheit F)

	//{
	//	Tem = (F.Tem - 32) / 1.8;
	//}

	//변환 함수를 사용하여 클래스 변환.
	operator Fahrenheit();

	void OutTem() { printf("섭씨=%f\n", Tem); }
};

// 화씨 Class
class Fahrenheit
{
public:
	double Tem;
	Fahrenheit() { }
	Fahrenheit(double aTem) : Tem(aTem) { }

	//변환 생성자를 사용하여 클래스 변환을 시도할 수도 있다.
	explicit Fahrenheit(Celsius C)
	{
		Tem = C.Tem * 1.8 + 32;
	}
	//변환 함수를 사용하여 클래스 변환.
	operator Celsius();

	void OutTem() { printf("화씨=%f\n", Tem); }
};



Celsius::operator Fahrenheit()
{
	Fahrenheit F;
	F.Tem = Tem * 1.8 + 32;
	return F;
}



Fahrenheit::operator Celsius()
{
	Celsius C;
	C.Tem = (Tem - 32) / 1.8;
	return C;
}



void main()
{
	Celsius C(100);
	Fahrenheit F = C;

	C.OutTem();
	F.OutTem();
	printf("\n");


	Fahrenheit F2 = 120;
	Celsius C2 = F2;

	F2.OutTem();
	C2.OutTem();

}