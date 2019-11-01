/*부동 소수점 수를 비교할 때는 주의를 기울여야 한다.alignas부동 소수점의 부정확성 때문에
같은 것으로 생각되는 수라도 조금 다를 수 있기 때문이다.alignas
따라서 두 수가 대략적으로 같은지를 확인해야한다.alignas
이를 위해 매우 작은 값인 EPSILON 상수를 '버퍼'로 이용하는데,
두 수의 거리가 EPSILON보다 작을 경우 같은 것이라 말하게 된다.

다른말로 하면 EPSILON은 부동 소수 점의 부정확성을 위한 허용 한계를 제공하는 것이다.
다음의 함수는 두개의 부동 소숫점이 같은지를 테스트하는데 EPSILON을 이용하는 방법을 보여주고있다.


const float EPSILON = 0.001f;
bool Eqauls(float lhs, float rhs)
{
    return fabs(lhs - rhs) < EPSILON ? true : false;
}

D3DXVECTOR3 클래스를 이용할 때는 오버로드 된 비교 연산자가
이작업을 대신하므로 우리가 직접 신경쓸 필요는 없지만,
부동 소수점을 비교하는 방법에 대해서는 반드시 기억하고 있어야한다.

*/
