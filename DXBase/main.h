// ���C���w�b�_
#pragma once


#include <d3d9.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800		// DirectInput�̌x���h�~
#include <dinput.h>					// DirectInput
#define DIRECTSOUND_VERSION	(0x0800)
#include <dsound.h>					// DirectSound
#include "define.h"



//-------- ���C�u�����̃����N�i�����L�q���Ă����Εʓr�����N�ݒ肪�s�v�ƂȂ�j
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib,"dsound")			// DirectSound
#pragma comment(lib, "dxguid.lib")



// EOF