재질은 물체의 표면에서 반사할 빛의 퍼센테이지를 지정할 수 있도록 해준다 
코드에서는 다음과 같은 D3DMATERIAL9 구조체로 재질을 나타낸다.


typedef struct _D3DMATERIAL9
{
    D3DCOLORVALUE Diffuse , Ambient, Specular, Emissive ;
    float Power;
} D3DMATERIAL9; 

 Diffuse    -   표면이 반사하는 난반사광의 양을 지정한다
 Ambient    -   표면이 반사하는 환경광의 양을 지정한다
 Specular   -   표면이 반사하는 정반사광의 양을 지정한다
 Emissive   -   이 성분은 전반적인 표면의 컬러를 더하는 데 사용되며 ， 물제 자체가 빛을 발하는 것처럼
                좀더 밝은 물체 효과를 만들어낸다
 Power      -   정반사광의 닐카로운 정도 sha rpn ess) 를 지정하며， 값이 높아질수록 라이트가 강조된다 


 /////////////////////////////////////////////
예를 들어 빨간 공을 원한다고 가정해보자. 이 예시에서는 빨간빛만을 반사하고 다른 모든 빛을 흡수하도록 재질을 설정하면 된다


D3DMATERIAL9 red ;
ZeroMemory(&red, sizeof(red));
red.Diffuse =  D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) ; // 빨간색
red.Ambient =  D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) ; // 빨간색
red.Specular = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) ; // 빨간색
red.Emissive = D3DXCOLOR(0.Of, 0.0f, 0.0f, 1.0f) ; // 빛을 발산하지 않음
red.power = 5.0f;

 녹색과 청색 성분을 으로 지정하여 재질이 두 가지 빛을 0% 반사하도록 정했으며， 
 적색 성분은 1.0f로 지정하여， 적색 빚은 100% 반사하도록 하였다.


