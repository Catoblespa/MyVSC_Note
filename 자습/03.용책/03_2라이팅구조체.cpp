typedef struct _D3D1IGHT9
{
    D3D1IGHTTYPE Type ;
    D3DC010RVA1UE Diffuse;
    D3DC010RVA1UE Specular;
    D3DC010RVA1UE Ambient ;
    D3DVECTOR Position;
    D3DVECTOR Direction;
    float Range ;
    float Falloff; 
    float AttenuationO.;
    float Attenuationl;
    float Attenuation2;
    float Theta;
    float Phi;
} D3DLIGHT9;



 Type       - 우리가 만들고자 하는 광원의 타입을 지정한다. D3DLIGHT POINT, D3DLIGHT SPOT ,D3DLIGHT DIRECTIONAL 중에 하나가 될 수 있다
 Diffuse    - 광원이 발산하는 난반사광의 컬러
 Specular   - 광원이 발산하는 정반사광의 컬러
 Amb ient   - 광원이 발산하는 환경광의 컬러
 Position   - 광원의 위치를 정의하는 벡터. 방향성 광원의 경우에 이 값은 의미가 없다
 Direction  - 빛이 향하는 방향을 정의하는 벡터 점 광원에서는 이 값을 이용하지 않는다
 Range      - 빛이 완전히 소멸할 때까지 진행할 수 있는 최대 거리 이 값은 Ý FLT_ MAX 보다 클 수 없으며 방향성 광원의 경우에는 의미가 없다
 Falloff    - 이 값은 스포트 광원에서만 이용되며 안쪽의 원뿔파 바깥쪽의 원뿔 간 빛의 세기 차이를 정의한다 이 값은 보통 1.0f로 지정된다
            AttenuationO , Attenuation1 , Attenuation2 - 감쇠 attenuation ) 변수는 거리에 따라 빛의 세기가 약해지는 정도를 정의하며 
            점 광원과 스포트 광원에서만 이용된다 attenuationO 변수는 상수 감소를, 
            attenuation1 변수는 선형 감소를 attenuation2 변수는 이차 감소를
            정의한다. 광원에서의 거리를 D로 하고. Attenuation 0, 1, 를 각각 A0, A1, A2 라고 하면
            다음과 같은 식을 세울 수 있다
                           Attenuation =  1/ A0 + (A1 * D )+ (A2 *D^2)
Theta       - 스포트 광원에서만 이용되며 안쪽 원뿔의 각도를 라디안으로 지정한다
Phi         - 스포트 광원에서만 이용되며 바깥쪽 원뿔의 각도를 라디안으로 지정한다 




//라이팅 구조체 만들는 핳ㅁ수.

D3DLIGHT9 CDeviceManager::InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = *color * 0.6f;
	light.Diffuse = *color;
	light.Specular = *color * 0.6f;
	light.Direction = *direction;

	return light;
}


D3DLIGHT9 CDeviceManager::InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_POINT;
	light.Ambient = *color * 0.6f;
	light.Diffuse = *color;
	light.Specular = *color * 0.6f;
	light.Position = *position;
	light.Range = 1000.0f;
	light.Falloff = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	return light;
}

D3DLIGHT9 CDeviceManager::InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_SPOT;
	light.Ambient = *color * 0.0f;
	light.Diffuse = *color;
	light.Specular = *color * 0.6f;
	light.Position = *position;
	light.Direction = *direction;
	light.Range = 1000.0f;
	light.Falloff = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Theta = 0.4f;
	light.Phi = 0.9f;

	return light;
}



/*
    라이팅 등록 
*/
m_pDevice->SetRenderState(D3DRS_LIGHTING, true);	//라이트 연산을 사용한다는 옵션. false면 라이트 연산X


D3DXVECTOR3 dir(1.0f, 0.0f, 0.0f);                  //X+축이 방향
D3DXCOLOR c = WHITE;                                //색상은 화이트
D3DLIGHT9 dirLight = InitDirectionalLight(&dir, &c);//방향과 색을 받아 다이렉션라이트 생성.



m_pDevice->SetLight(1, &dirLight);  // 디바이스 갖고있는 라이트 리스트에 1번으로 넣음
m_pDevice->LightEnable(1, true);   // 1번 라이트 켬   수동으로 안켜주면 활성화 안됨.




/*
장면에 광원을 추가하는 단계는 다음과 같다.
1 조명을 활성화한다
2 각 물체의 재질을 만들고 해당 물체를 렌더링하기 전에 재질을 지정한다
3 한 개 이상의 광원을 만들고 광원을 지정한 후 이를 활성화한다
4 정반사광과 같은 부가적인 조명 상태를 활성화한다. 


*/