
//텍스처 로딩.

	//D3DXCreateTextureFromFile 함수로 불러오려면 이미지의 크기는 2의 n승이여야 한다.
	//D3DXCreateTextureFromFileEx는 2의 n승 제약으로부터 자유롭다.


RESULT CSingleTexture::LoadTexture(
	const wstring & wstrFilePath, 
	const wstring & wstrStateKey/* = L""*/, 
	int iImgCount/* = 0*/)
{
	D3DXIMAGE_INFO tImgInfo;
	ZeroMemory(&tImgInfo, sizeof(D3DXIMAGE_INFO));

	//파일로부터 이미지 정보를 얻어오는 함수.
	HRESULT  hr = D3DXGetImageInfoFromFile(wstrFilePath.c_str(),&tImgInfo);
	FAILED_CHECK_RETURN(hr, E_FAIL);


	LPDIRECT3DTEXTURE9 pTexture;
	//파일을 통해 텍스처를 불러와서 
	//IDirectTexture9 객체를 생성하는 함수.
	hr = D3DXCreateTextureFromFileEx(
		Devicemgr->GetDevice(),		//디바이스
		wstrFilePath.c_str(),		//경로		
		tImgInfo.Width,				//텍스처 가로 크기		//D3DPOOL	항목			: 불러온 이미지를 어느 메모리에 저장할것인가?
		tImgInfo.Height,			//텍스처 세로 크기		//D3DPOOL_DEFAULT		: 그래픽카드 메모리에 저장한다.
		tImgInfo.MipLevels,			//밉맵 레벨				//D3DPOOL_MANAGED		: 디폴트와 시스템의 중간. 램과 그래픽카드메모리 둘다 씀.(RAM에 백업)
		0,							//텍스처 사용방식.		//D3DPOOL_SYSTEMMEM		: RAM 사용
		tImgInfo.Format,			//텍스쳐 픽셀 포맷
		D3DPOOL_MANAGED,			//메모리 저장방식
		D3DX_DEFAULT,				// 텍스쳐 필터링 방식					//D3DX_DEFAULT : 장치가 알아서 처리함.
		D3DX_DEFAULT,				// 밉맵 필터링 방식.
		0,							// 제거할 색상 (Color)				//0 : 색상제거 안함.
		nullptr,					// D3DXIMAGE_INFO의 포인터(InOut)	// 위에서 이미 불러와서 썻으니 nullptr
		nullptr,					// PALETTEENTRY 포인터
		&pTexture
	);
	FAILED_CHECK_RETURN(hr, E_FAIL);


	m_pTexInfo = new TEX_INFO;
	m_pTexInfo->pTexture = pTexture;
	m_pTexInfo->tImgInfo = tImgInfo;


	return S_OK;
}

void CSingleTexture::Release()
{
	m_pTexInfo->pTexture->Release();//m_pTexInfo 가 갖고있는 COM객체 해제
	SafeDelete(m_pTexInfo);	//m_pTexInfo 해제

}
///////////////////////////////////////


	LPD3DXSPRITE m_pSprite;			//스프라이트 객체를 담을 포인터를 만든다.
	D3DXCreateSprite(m_pDevice, &m_pSprite); //디바이스로 부터 스프라이트 객체를 생성하여 m_pSprite에 저장한다.


	//Render Begin에 추가
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);// 스프라이트의 알파블랜딩을 사용함.(배경의 알파값이 있으면 출력안함)
	//Render End 에 추가
	m_pSprite->End();



	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;


	//GameManager의 랜더에서 그리기 
	m_pSprite->GetSprate()->Draw(
		pTexInfo->pTexture,			/* LPDIRECT3DTEXTURE9 */ 
		nullptr,					/* 텍스처에서 그릴 영역. nullptr일 경우 텍스처 전체 그림*/
		nullptr,					/*  D3DVECTOR3  그려야할 텍스처의 중심점 */
		&D3DXVECTOR3(400.f , 300.f, 0.f),		/*D3DXVECTOR3*  화면 어디에 그릴 것인가?*/ 
												/*월드행렬를 SetTransform으로 넘겨주면 nullptr넣을것.*/
		D3DCOLOR_ARGB(255,255,255,255)		/*D3DCOLOR_ARGB(투명도 , R비율 , G비율 ,B비율)*/
		)

    