#include "fcLayer.h"
#include <iostream>
using namespace std;

fcLayer::fcLayer(SfcLayerParam fcParam)
{
	int width = fcParam.inputNum;
	int height = fcParam.outputNum;
	m_weightData = new blobData(height, width);
	m_bNeedLearn = true;
}

void fcLayer::forward(blobData& inputData, blobData& outputData)
{
	if (m_weightData->m_nWidth != inputData.m_nHeight ||
		m_weightData->m_nHeight != outputData.m_nHeight)
	{
		cout << "error: fcLayer input or output is not match weight!" << endl;
	}

	int outHeight = outputData.m_nHeight;
	int outWidth = outputData.m_nWidth;

	for (int i = 0; i < outHeight; i++)
	{
		for (int j = 0; j < outWidth; j++)
		{
			double value = 0;
			for (int m = 0; m < m_weightData->m_nWidth; m++)
            {
				double wData = *(m_weightData->curData(i, m));
				double iData = *(inputData.curData(m, j));
				value += wData*iData;
            }
			*(outputData.curData(i, j)) = value;
		}
	}
}

void fcLayer::backward(blobData& inputData, blobData& outputData)
{
	//计算输入inputData梯度
	int inHeight = inputData.m_nHeight;
	int inWidth = inputData.m_nWidth;
	int outHeight = outputData.m_nHeight;
	int outWidth = outputData.m_nWidth;

	for (int i = 0; i < inHeight; i++)
	{
		for (int j = 0; j < inWidth; j++)
		{
			double value = 0;
			for (int m = 0; m < outHeight; m++)
			{
				double outDiff = 0;
				//需要重新检查
				for (int n = 0; n < outWidth; n++)
				{
					double outWDiff = *(outputData.curDiff(m, n));
					double weightData = *(m_weightData->curData(m, i));
					outWDiff *= weightData;
					outDiff += outWDiff;
				}
				value += outDiff;
			}
			*(inputData.curDiff(i, j)) = value;
		}
	}

	//计算权值m_weightData梯度
	int weiHeight = m_weightData->m_nHeight;
	int weiWidth = m_weightData->m_nWidth;
	for (int i = 0; i < weiHeight; i++)
	{
		for (int j = 0; j < weiWidth; j++)
		{
			double outDiff = *(outputData.curDiff(i,0));
			double inData = *(inputData.curData(j,0));
			*(m_weightData->curDiff(i, j)) = outDiff*inData;
		}
	}
}


void fcLayer::update()
{
	m_weightData->update();
}


