/*
--------------
    D3DX 행렬
--------------
    Direct3D 애플리케이션을 프로그래밍 할때는 4*4 행렬과 1*4행 벡터만을 이용한다.
    두 가지 크기의 행렬만을 이용한다는 것은 다음과 같은 행렬 곱이 정의된다는 것이다.
    
    - 백터와 행렬 곱 v가 1*4 행 백터이고 T가 4*4행렬이면 vT가 정의되며, 그결과는
        1*4행 벡터가 된다.

    - 행렬과 행렬 곱 T가 4*4행렬이고 R이 4*4행렬이라면 TR과 RT가 정의되며, 
        두 가지 모두 4*4행렬이 된다. 행렬 곱은 상호 교환적이지 않으므로 TR이 RT와 다를 수 있다.
    

    D3DX에서 1*4 행 벡터를 나타내기 위해서 우리는 보통 D3DXVECTOR3와 D3DXVECTOR3 벡터 클래스를 이용한다.
    물론 D3DXVECTOR3는 4개가 아닌 3개의 성분만을 가지고 있지만, 네번째 성분은 일반적으로 1이나 0으로 취급된다.
    
    D3DX에서 4*4행렬을 나타내는데 D3DXMATRIX클래스가 이용된다.


행렬 함수

항등 행렬을 만드는 함수 :pout을 항등 행렬로 지정한다.
D3DXMatrixIdentity(D3DXMATRIX *pout );      

전치 행렬 함수 : pM행렬의 전치 행렬을 pOut에 전달한다.
D3DXMatrixTranspose(D3DXMATRIX *pOut ,CONST D3DXMATRIX *pM );

//역행렬 함수 :  pOut            : pM의 역행렬을 pOut으로 리턴한다. 
//              pDeterminant    : 행렬식을 전달 필요한 경우에만 전달하고 그렇지 않으면 0을 전달
//              pM              :뒤집을 행렬
D3DXMatrixInverse(D3DXMATRIX *pOut, F10AT *pDeterminant,CONST D3DXMATRIX *pM);



--------------
기본적인 변환 
--------------
Direct3 를 이용한 프로그래밍 에서 는 변환을 표현하기 위해 4x4 행렬을 용하며，
기본적인 방식은 다음과 같다. 

4x4 행렬의 각 항목을 특정한 변환을 나타내는 값으로 채운 음， 1x4 행 벡터 v의 열에 포인트의 좌표나 벡터를 넣는다. 
이제 곱 vX가 새로이 변환된 벡터에 넣어진다. 
예를 들어， X가 x-축으로의 10-단위 이동을 나타내고 
v = [2, 6, -3, 1] 이라면， 곱 vX = [12 ， 6, - 3, 1] 이다.

몇 가지 명확하게 해둘 것이 있다. 4*4행렬을 이용하는 것은 이 크기를 이용해 우리가
원하는 모든 변환을 표현 할수 있기 때문이다. 언뜻 보기에는 3*3행렬이 3D에 더욱 적합해 보이기도 하지만,
실제로 이동이나 투영, 반사등과 같이 3*3행렬로는 표현 할수 없는 변환들이 있다.
우리가 작업하려는 것은 벡터-행렬 곱임을 기억하자.
따라서 변환 수행을 위한 행렬 곱의 규칙에 제한을 받는다 4*4 행렬을 보충한다면 행렬과 정의 된 벡터 * 행렬 곱을 이용한
좀더 다양한 변환을 시도 할 수 있다.

앞서 우리는 1*4행 벡터의 열에 포인트의 좌표나 벡터의 성분을 넣는다고 하였다.
하지만 포인트나 벡터는 3D가 아닌가?! 1*4 행 벡터를 이용하는 이유는 무엇일까?
벡터-행렬 곱을 정의하기 위해서는 4D행 벡터에 3D 포인트/벡터를 보충해야한다.
즉 1*3행 벡터와 4*4행렬의 곱은 정의 할 수가 없다.

그렇다면 w로 표기하는 네번째 성분은 어떻게 이용해야 하는가?
        1*4행 벡터에 포인트를 배치할 때는 w성분을 1로 지정해야 포인트의 이동이 올바르게 동장 할수 있다]
반면에 벡터는 위치를 가지지 않으므로 벡터의 이동은 정의 될 수 없으며, 벡터를 이동하려는 시도는 의미 없는 벡터라는 결과로 이어진다.
벡터의 이동을 막기 위해서는 1*4행 벡터에 벡터를 넣을때 w 성분에 0을 넣어야한다. 
    예를 들어, 포인트 p =(p1, p2, p3)는 [p1,p2,p3,1]로 행 벡터에 넣어야 하며,
    벡터 v = (v1, v2,v3)는 [v1 ,v2 ,v3 , 0]으로 행 벡터에 넣어야한다.


    ///// Note
    포인트 이동이 바르게 처리되기 위해서는 w = 1을 지정해야하며,
    벡터 이동을 막기 위해서는 w = 0을 지정해야 한다.
    이와 같은 사실은 실제로 이동행렬을 살펴 볼때 다시 확인 할수 있다.
    /////
    보충된 4D 벡터를 동치 벡터라고 부른다. 동치 벡터는 포인트나 벡터를 기술 할 수 있으므로,
    대상을 확실히 하기 위해 '벡터;라는 용어를 이용한다.
    /////

때로는 행렬 변환 과정에서 벡터의 w성분을 바꾸어 w!=0과 w!=1일 수 도 있다.



--------------
이동 행렬
--------------
D3DXMatrixTranslation (D3DXMATRIX* pOut, float x, float y, float z);
    pOut : 결과
     x-axis 축으로 이동할 단위의 수
     y-axis 축으로 이동할 단위의 수
     z-axis 축으로 이동할 단위의 수
            [ 1, 0, 0, 0]
    pOut *  [ 0, 1, 0, 0]
            [ 0, 0, 1, 0]
            [ x, y, z, 1]

            
--------------
회전 행렬
--------------
다음의 행렬을 이용하면 X-, y-, z- 축에서 벡터 라디안을 회전시킬 수 있다 각도는
회전축을 내려다 볼 때 시계 방향으로 측정한다


다음은 x-축 회전 행렬을 구성하는 D3DX 함수이다.
D3DXMATRIX *D3DXMatrixRotationX(D3DXMATRIX* pOut, FLOAT Angle )
            [ 1,    0,    0, 0]
    X(θ) *  [ 0, cosθ, sinθ, 0]
            [ 0,-sinθ, cosθ, 0]
            [ 0,    0,    0, 1]

다음은 y-축 회전 행렬을 구성하는 D3DX 함수이다.
D3DXMATRIX *D3DXMatrixRotationY(D3DXMATRIX* pOut, FLOAT Angle )
            [ cosθ, 0,-sinθ, 0]
    Y(θ) *  [ 0,    1,    0, 0]
            [ sinθ, 0, cosθ, 0]
            [ 0,    0,    0, 1]


다음은 z-축 회전 행렬을 구성하는 D3DX 함수이다.
D3DXMATRIX *D3DXMatrixRotationZ(D3DXMATRIX* pOut, FLOAT Angle )
            [ cosθ, sinθ,  0,  0]
    Z(θ) *  [-sinθ, cosθ,  0,  0]
            [ 0,       0,  1,  0]
            [ 0,       0,  0,  1]


            
--------------
크기 변환 행렬
--------------
다음의 행렬을 벡터와 곱하면 x-축으로 qx 단위만큼 ,  y-축으로 qy단위 만큼， 
z-축으로 qz단위만큼 벡터의 크기를 변경할 수 있다.
            [qx, 0,  0,  0]
    S(q) *  [ 0,qy,  0,  0]
            [ 0, 0, qz,  0]
            [ 0, 0,  0,  1]
다음은 크기 변환 행렬을 구성하는 D3DX 함수이다.
D3DXMatrixScaling( D3DXMATRIX* pOut, float sx, float sy, float sz);

*/



/*
D3DX 라이브러리는 포인트와 벡터 변환을 위한 두 개의 함수를 제공한다 

D3DXVec3TransformCoord 함수는 포인트를 변환하며，
                     벡터의 네번째 성분이 1로 인식된다고 가정한다.
D3DXVec3TransformNormal 함수는 벡터를 변환하며 
                     벡터의 네번째 성분이 0으로 인식된다고 가정한다. 

D3DXVec3TransformCoord (D3DXVECTOR3* pOut ,CONST D3DXVECTOR3* pV,CONST D3DXMATRIX* pM)
    //pOut : 결과
    //pV   : 변환할 포인트
    //pM   : 변환 행렬
D3DXMATRIX T( ... ) ; / / 변환 행렬을 초기화한다.
D3DXVECTOR3 p( ... ) ; // 포인트를 초가화한다 •
D3DXVec3TransformCoord( &p , &p, &T); // 포인트를 변환한다 . 



D3DXVec3TransformNormal(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV,CONST D3DXMATRIX *pM);
    //pOut : 결과
    //pV   : 변환할 벡터 
    //pM   :  변환 행렬 

D3DXMATRIX T ( . . . ) ; / / 변환 행렬을 초기화한다 .
D3DXVECTOR3 v( . .. ); // 벡터를 초기화한다
D3DXVec3TransformNormal( &v , &v , &T) ; // 벡터를 변환한다 . 

        D3DX 라이브러리는 포인트 열과 벡터 배열을 변환히는 D3DXVec3TransformCoordArray와
        D3DXVec3TransformNormalArray 함수도 제공한다. 


*/
