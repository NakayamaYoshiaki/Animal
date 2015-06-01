#pragma once

// �\����
typedef struct
{
	float x;
	float y;
	float z;
}KEY;

class CMyMath
{
private:

public:
	CMyMath(void);
	virtual ~CMyMath(void);

	static void Bezier2D(float* x, float* y, float t, KEY Key[4]);					// �x�W�G�Ȑ��\����
	static void Bezier3D(float* x, float* y, float* z, float t, KEY Key[4]);					// �x�W�G�Ȑ��\����

	static void Hermite2D(float* x, float* y, float t, KEY Key[2], KEY VKey[2]);	// �G���~�[�g
	static void Hermite3D(float* x, float* y, float* z, float t, KEY Key[2], KEY VKey[2]);	// �G���~�[�g

};

