/*

블랜딩

이 단원에서는 현재 래스터라이즈 과정에 있는 픽셀과 같은 위치에 있는 전의 픽셀을 서로 섞는(조합)하는 
테크닉인 블렌딩에 대해서 살펴보려고 한다. 
다른 말로 하면 앞서 그린 기본형 위에 새로운 기본형을 섞을 수 있다. 이 테크닉은 다양한 효과(특히 투명)를 가능하게 해준다. 

*/

/*
나무 상자 위에 주전자의 삼각형들을 래스터라이즈하는 동안 주전자와
나무 상자의 픽셀 컬러를 조합하는 과정이 필요하다.
현재 계산되고 있는 픽셀(원본 픽셀)을 앞서 쓰여진 픽셀 값(목적지 픽셀)과 결합하는 방식을 블렌딩이라 부른다.

블렌딩 효과는 유리와 같은 투명효과에 제한되지 않는다는 것을 기억하자.
D3D는 컬러가 조합되는 방법을 지정하는 다양한 옵션을 제공한다.
*/



/*

현재 그려지고 있는 픽셀은 앞서 후면 버퍼에 그려진 픽셀과 블렌드된다는 것을 기억하자.
앞서의 예제 그림에서 (용책 183p 그림 7.2) 나무 상자의 이미지는 먼저 그려진 것이므로
이 이미지의 픽셀은 후면 버퍼에 보관되는 것이다. 주전자는 이후에 그려져 나무 상자의 픽셀과 섞는 작업이 가능해진다.
따라서 블렌딩을 이용하기 위해서는 다음의 규칙이 반드시 지켜져야 한다..


    1. 블렌드를 이용하지 않는 물체를 먼저 그린다.
    2. 이어 블렌드를 이용할 물체들을 카메라와의 거리에 따라 정렬한다.
    3. 물체들이 뷰 스페이스 내에 있다면 , z성분을 통해 간단히 정렬이 가능하므로
        가장 손쉬운 작업이 가능하다.
    4. 마지막으로 블렌딩을 이용하는 물체들을 뒤에서 앞 순서로 그려나간다.


두 개의 픽셀 값을 섞는 데는 다음의 식이 이용된다.
    outputPixel = SourcePixel ⓧ SourceBlendFactor + DestPixel ⓧ DestBlendFactor
각각의 변수는 4D 컬러 벡터 (r g b a)이며 , ⓧ기호는 성분 단위 곱을 나타낸다.

outputPixel         : 블랜드 결과 픽셀
SourcePixel         : 후면 버퍼의 픽셀과 블렌드할 현재 픽셀
SourceBlendFactor   : 블렌드할 원본 픽셀의 퍼센트를 지정하는 [0,1] 범위 내의 값
DestPixel           : 후면 버퍼 내의 픽셀
DestBlendFactor     : 블렌드할 목적지 픽셀의 퍼센트를 지정하는 [0,1] 범위 내의 값
*/  즉 SourcePixel이  DestPixel보다 카메라에 더 가깝다 (Z버퍼 값이 작다.)
/*
원본과 목적지 블렌드 인수는 원본과 목적지 픽셀을 다양한 방법으로 변경하여 여러가지 효과를 연출 할 수 있도록 해준다.
블렌딩은 디폴트로 비활성화되어 있으며*/
D3DRS_ALPHABLENDENABLE 랜더 상태를 true로 지정하여 블랜딩을 활성화 할수 있다.

            /*
            TIP
            블렌딩은 상당한 작업이 필요한 효과이며 반드시 이를 필요로 하는 기하정보에 대해서만 활성
            화되어야 한다 그리고 해당 기하정보의 렌더링이 끝나면 다시 알파 블렌딩을 비활성화시켜야
            한다. 또한， 블렌딩이 필요한 삼각형들을 한 번에 처리하여 하나의 프레임 내에서 여러 번 블
            렌딩을 켜고 끄는 일을 피하는 것이 좋다. 
            */





/* 블랜드 인수 */
/*
원본과 목적지 블렌드 인수에 다양한 조합의 값을 넣으면 여러 가지 블렌드 효과를 만들어 낼 수 있다.
각각의 조합이 만들어내는 효과는 직접확인해보록 하자.
원본 블렌드 인수와 목적지 블렌드 인수를 지정하기 위해서는 각가 D3DRS_SRCBLEND와 D3DRS_DESTBLEND랜더 상태를 이용하면 된다.
*/
    Device- >SetRenderState(D3DRS_SRCBLEND, Source) ;
    Device- >SetRenderState(D3DRS_DESTBLEND, Destination); 

Source 와 Destination 의 값으로는 다음의 블렌드 인수 중 하나를 넣으면 된다.


(R = Red , G = Green ,  B = Blue ,  A= Alpha   /   s = Src   d = dest)

 D3DBLEND ZERO            - 블렌드 인수 =(0,0,0,0)
 D3DBLEND ONE             - 블렌드 인수 = (1,1,1,1)
 D3DBLEND SRCCOLOR        - 블렌드 인수 = ( Rs, Gs, Bs, As)                 -Src디폴트
 D3DBLEND INVSRCCOLOR     - 블렌드 인수 = (1-Rs , 1-Gs , 1-Bs , 1-As)
 D3DBLEND SRCALPHA        - 블렌드 인수 = (As , As , As , As )
 D3DBLEND INVSRCALPHA     - 블렌드 인수 = (1-As, 1-As , 1-As , 1 -As)

 D3DBLEND DESTALPHA       - 블렌드 인수 = (Ad, Ad ,  Ad, Ad)
 D3DBLEND INVDESTALPHA    - 블렌드 인수 = (1-Ad , 1-Ad , 1-Ad , 1-Ad)       -Dest 디폴트
 D3DBLEND DESTCOLOR       - 블렌드 인수 =(Rd ,  Gd ,  Bd ,  Ad )
 D3DBLEND INVDESTCOLOR    - 블렌드 인수 = (1 -Rd , 1-Gd , 1-Bd , 1-Ad)
 D3DBLEND SRCALPHASAT     - 블렌드 인수 = (f,f,f,1),   f= min(As, 1-Ad) 

D3DBLEND BOTHINVSRCALPHA - 이 블렌드 모드는 원본 블렌드 인수를 (l-As , 1-As , 1-As, 1-As) 로， 
                                            목적지 블렌드 인수를 (As , As , As , As )로 지정한다 
                                            이 블렌드 모드는 D3DRS_SRCBLEND 에만이용할수 있다 

원본 블렌드 인수와 목적지 블렌드 인수의 디폴트 값은 각각 D3DBLEND_SRCALPHA 와 D3DBLEND_INVSRCALPHA이다. 