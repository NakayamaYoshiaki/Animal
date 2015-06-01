#include "MySort.h"
#include "define.h"

CMySort::CMySort(void)
{
}


CMySort::~CMySort(void)
{
}


void CMySort::QuiqSort(SortData* Data, int nArrNum)
{
	if(nArrNum < 3)
		return;

	int nHalf = (nArrNum - 1) / 2;		// ����
	int nAmari = (nArrNum) % 2;
	float fBaseData = Data[nHalf].fData;		// ��l
	int nCnt = nArrNum - 1;
	SortData Wk;

	// �Y�����̏�����������
	for(int i = 0; i <= nHalf; i++)
	{
		// ��l�ȏ�
		if(Data[i].fData >= fBaseData)
		{
			// �Y�����̑傫��������
			for(nCnt; nCnt > nHalf; nCnt--)
			{
				// ��l����
				if(Data[nCnt].fData < fBaseData)
				{
					// ����
					Wk			= Data[i];
					Data[i]		= Data[nCnt];
					Data[nCnt]	= Data[i];
					break;
				}
			}
		}
	}

	if(nHalf < 3)		// �v�f����3�ȉ��Ȃ�
		return;

	// �z���2�ɕ�����
	SortData* Data1 = new SortData[nHalf + 1];
	SortData* Data2 = new SortData[nArrNum - nHalf - 1];

	// �ڂ�
	for(int i = 0; i <= nHalf; i++)
	{
		Data1[i] = Data[i];
	}

	for(int i = 0; i < nArrNum - nHalf - 1; i++)
	{
		Data2[i] = Data[i + nHalf + 1];
	}

	// �ċN
	QuiqSort(Data1, nHalf + 1);
	QuiqSort(Data2, nArrNum - nHalf - 1);

	// �A��
	for(int i = 0; i <= nHalf; i++)
	{
		Data[i] = Data1[i];
	}

	for(int i = 0; i < nArrNum - nHalf - 1; i++)
	{
		Data[i + nHalf + 1] = Data2[i];
	}

	// ���
	SAFE_DELETE_ARRAY(Data1);
	SAFE_DELETE_ARRAY(Data2);
}


// eof