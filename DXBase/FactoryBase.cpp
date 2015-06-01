#include "FactoryBase.h"
#include "ObjBase.h"
#include "Title.h"

CFactoryBase::CFactoryBase(void)
{
}


CFactoryBase::~CFactoryBase(void)
{
}

// 初期化
void CFactoryBase::Initialize()
{

}

// 生成（自身）
CFactoryBase* CFactoryBase::Create()
{
	CFactoryBase* pFac = new CFactoryBase();

	pFac->Initialize();

	return pFac;
}

// 解放
void CFactoryBase::Release()
{

}

// 生成依頼
void CFactoryBase::Request2D(int nID, D3DXVECTOR3 vPos)
{
	
}

// 生成依頼
void CFactoryBase::Request3D(int nID, D3DXVECTOR3 vPos)
{
	
}