
bool IsPicking(const D3DXVECTOR3 & vPos, size_t iIndex)
{
    
	//////////////////////////////////////////////////////////////////////
    //                        내적 (데카르트 기준)
	//////////////////////////////////////////////////////////////////////

	// 마름모의 꼭지점 시계방향으로 12시, 3시, 6시, 9시를 구한다.
	D3DXVECTOR3 vPoint[4] =
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX * 0.5f, m_vecTile[iIndex]->vPos.y, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX * 0.5f, m_vecTile[iIndex]->vPos.y, 0.f),
	};

	// 시계방향으로 4개의 방향벡터를 구한다.
	D3DXVECTOR3 vDir[4] = 
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	// 위에서 구한 방향벡터의 법선벡터들을 구한다.
	D3DXVECTOR3 vNormal[4] = {};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Cross(&vNormal[i], &D3DXVECTOR3(0.f, 0.f, 1.f), &vDir[i]);

	// 각 꼭지점에서 마우스 위치로 향하는 벡터 4개 구한다.
	D3DXVECTOR3 vMouseDir[4] =
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	// vNormal와 vMouseDir을 내적해서 모두 음수(둔각)가 나오면 true
	for (int i = 0; i < 4; ++i)
	{
		// 하나라도 양수(예각)가 나오면 false
		if (0.f < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}

	return true;


	//////////////////////////////////////////////////////////////////////
    //                         직선의 방정식 사용
	//////////////////////////////////////////////////////////////////////


	// 직선의 방정식 (데카르트 기준)
	// 마름모를 이루는 직선 4개에 대한 기울기를 구한다.
	float fGradient[4] = 
	{
		-(TILECY * 0.5f) / (TILECX * 0.5f),
		(TILECY * 0.5f) / (TILECX * 0.5f),
		-(TILECY * 0.5f) / (TILECX * 0.5f),
		(TILECY * 0.5f) / (TILECX * 0.5f)
	};

	// 마름모의 꼭지점 시계방향으로 12시, 3시, 6시, 9시를 구한다.
	D3DXVECTOR3 vPoint[4] =
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX * 0.5f, m_vecTile[iIndex]->vPos.y, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX * 0.5f, m_vecTile[iIndex]->vPos.y, 0.f),
	};

	// Y절편 구한다.
	// 0 = ax + b - y
	// b = y - ax
	float fB[4] = 
	{
		vPoint[0].y - fGradient[0] * vPoint[0].x,
		vPoint[1].y - fGradient[1] * vPoint[1].x,
		vPoint[2].y - fGradient[2] * vPoint[2].x,
		vPoint[3].y - fGradient[3] * vPoint[3].x
	};

	// 0 = ax + b - y: 현재 점은 직선과 같은 선상에 있다. (직선이 점을 통과한다)
	// 0 > ax + b - y: 현재 점은 직선보다 위에 있다.
	// 0 < ax + b - y: 현재 점은 직선보다 아래에 있다.
	return (0 < fGradient[0] * vPos.x + fB[0] - vPos.y &&
		0 > fGradient[1] * vPos.x + fB[1] - vPos.y &&
		0 > fGradient[2] * vPos.x + fB[2] - vPos.y &&
		0 < fGradient[3] * vPos.x + fB[3] - vPos.y);
}