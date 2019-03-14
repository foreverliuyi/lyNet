#include "reluLayer.h"
#include <iostream>
using namespace std;

reluLayer::reluLayer() 
{
	m_bNeedLearn = false;
}

void reluLayer::forward(blobData& inputData, blobData& outData)
{
	if (inputData.m_nWidth != outData.m_nWidth 
		|| inputData.m_nHeight != outData.m_nHeight)
	{
		cout << "error: reluLayer input axis is not equal output axis!" << endl;
	}
	int height = inputData.m_nHeight;
	int width = inputData.m_nWidth;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (*(inputData.curData(i, j)) < 0)
				*(outData.curData(i, j)) = 0;
			else
				*(outData.curData(i, j)) = *(inputData.curData(i, j));
		}
	}
}

void reluLayer::backward(blobData& inputData, blobData& outData)
{
	if (inputData.m_nWidth != outData.m_nWidth
		|| inputData.m_nHeight != outData.m_nHeight)
	{
		cout << "error: reluLayer input axis is not equal output axis!" << endl;
	}
	int height = inputData.m_nHeight;
	int width = inputData.m_nWidth;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (*(inputData.curData(i, j)) < 0)
            {
				*(inputData.curDiff(i, j)) = 0;
            }
			else
			{
				*(inputData.curDiff(i, j)) = *(outData.curDiff(i, j));
			}
		}
	}
}
