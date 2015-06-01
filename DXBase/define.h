//=======================================================================================
//
//	  �萔��`�A�}�N����`
//
//=======================================================================================

#ifndef _H_DEFINE
#define _H_DEFINE

#include <stdio.h>
#include <tchar.h>

//-------- �}�N��
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)			if(x){ x->Release(); x=NULL; }
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)			if(x){ delete x; x=NULL; }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if(x){ delete[] x; x=NULL; }
#endif


#define SCREEN_WIDTH	1024			// �X�N���[���̕�
#define SCREEN_HEIGHT	576			// �X�N���[���̍���

#endif

//=======================================================================================
//	End of File
//=======================================================================================