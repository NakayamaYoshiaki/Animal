#pragma once
#include "Object3D.h"

class CCaptureWindow
{
private:
	static CCaptureWindow* m_pThis;
	LPDIRECT3DTEXTURE9 m_pRendTex; //�����_�����O��̃e�N�X�`��
	LPDIRECT3DSURFACE9 m_pRendTexSurface; //�e�N�X�`������擾����T�[�t�F�[�X
	LPDIRECT3DSURFACE9 m_pRendTexZ; //�e�N�X�`���p��Z �o�b�t�@�[
	LPDIRECT3DSURFACE9 m_pBackbuffer; //�o�b�N�o�b�t�@�[
	LPDIRECT3DSURFACE9 m_pBackZ;
 D3DVIEWPORT9 viewport1;

	bool m_bShot; 
public:
	CCaptureWindow(void);
	

	virtual ~CCaptureWindow(void);

	CCaptureWindow* Create();
	bool Initialize();

	bool ScreenShot();
	void		PreservedWindow();
	void		ChangeTex();
	void		Draw();
	void Release(){SAFE_RELEASE(m_pThis);};
	void SetScrShot(){m_bShot = true;};
	static CCaptureWindow* GetThis(){return m_pThis;};
};

