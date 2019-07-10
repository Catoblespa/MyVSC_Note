#include <iostream>
#include <typeinfo>


using namespace std;

template <typename T>
struct tagVector
{
	T x, y, z;
	tagVector<T>(T _x, T _y, T  _z) : x(_x), y(_y), z(_z) {};

};

template <typename T>
class CMyVetor : public tagVector<T>
{
public:
	CMyVetor<T>(T _x, T _y, T  _z) : tagVector<T>(_x, _y, _z) {};

	CMyVetor<T> operator+(const CMyVetor<T>& vec)
	{
		T x = this->x + vec.x;
		T y = this->y + vec.y;
		T z = this->z + vec.z;


		return CMyVetor(x, y, z);
	}
};

int main()
{
	CMyVetor<float>	vPos1(1,2,3);
	CMyVetor<float>	vPos2(1,2,3);


	CMyVetor<float>	vPos3 = vPos1 + vPos2;

	cout << vPos3.x <<endl;
	cout << vPos3.y <<endl;
	cout << vPos3.z <<endl;
	return 0;
}