#include "lossLayer.h"
#include <iostream>
#include "lylayer.h"
using namespace std;

lossLayer::lossLayer() 
{
	m_bNeedLearn = false;
}

void lossLayer::forward(blobData& inputData, blobData& outData)
{
	//实现loss前向运算
	if (inputData.m_nWidth != 1 || inputData.m_nHeight!=1
		|| outData.m_nWidth != 1 || outData.m_nHeight != 1
		|| m_labelData.m_nWidth != 1 || m_labelData.m_nHeight != 1)
	{
		cout << "error: lossLayer input or label not all 1*1!" << endl;
	}

	double* pData = outData.data();
	double inData = *(inputData.data());
	double lData = *(m_labelData.data());

	*pData = pow((inData - lData), 2)/2;
}

void lossLayer::backward(blobData& inputData, blobData& outData)
{
	if (inputData.m_nWidth != 1 || inputData.m_nHeight != 1
		|| outData.m_nWidth != 1 || outData.m_nHeight != 1
		|| m_labelData.m_nWidth != 1 || m_labelData.m_nHeight != 1)
	{
		cout << "error: lossLayer input or output or  label not all 1*1!" << endl;
	}

	double* pDiff = inputData.diff();
	double oData = *(inputData.data());
	double lData = *(m_labelData.data());
	*pDiff = oData - lData;
}