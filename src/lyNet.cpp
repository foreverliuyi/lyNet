#include "lyNet.h"
#include <iostream>
#include <fstream>  
#include <time.h> 

#define random(x) (rand()%x)
lyNet::lyNet() : m_label(1, 1), m_nMaxIter(500),
                 m_dLoss(0), m_dMinLoss(0.00001)
{
	//fc1²ã
	SfcLayerParam fcParam;
	fcParam.name = "fc1";
	fcParam.inputNum = 3;
	fcParam.outputNum = 3;
	lylayer* layer1 = new fcLayer(fcParam);
	m_layers.push_back(layer1);

	////fc2²ã
	fcParam.name = "fc2";
	fcParam.inputNum = 3;
	fcParam.outputNum = 1;
	lylayer* layer2 = new fcLayer(fcParam);
	m_layers.push_back(layer2);

	lylayer* layer3 = new reluLayer;
	m_layers.push_back(layer3);

	lylayer* layer4 = new lossLayer;
	m_layers.push_back(layer4);

	blobData blData0(3, 1);
	m_blobDatas.push_back(blData0);
	blobData blData1(3, 1);
	m_blobDatas.push_back(blData1);
	blobData blData2(1, 1);
	m_blobDatas.push_back(blData2);
	blobData blData3(1, 1);
	m_blobDatas.push_back(blData3);
	blobData blData4(1, 1);
	m_blobDatas.push_back(blData4);
}

void lyNet::setData(blobData& inputData)
{
	if (inputData.m_nWidth != 1)
		cout << "setTrainData error: input width is not 1 axis!" << endl;

	m_blobDatas[0] = inputData;
}

void lyNet::setTrainData(blobData& inputData, blobData& labelData)
{
	if (labelData.m_nHeight != 1 || labelData.m_nWidth != 1)
		cout << "setTrainData error: label is not 1 axis!" << endl;
	if (inputData.m_nWidth != 1)
		cout << "setTrainData error: input width is not 1 axis!" << endl;

	m_blobDatas[0] = inputData;
	m_label = labelData;
}

double lyNet::forward()
{
	int layerNum = m_layers.size();
	for (int i = 0; i < layerNum; i++)
	{
		m_layers[i]->setLabel(m_label);
		m_layers[i]->forward(m_blobDatas[i], m_blobDatas[i+1]);
	}

	int dataNum = m_blobDatas.size();
	m_dLoss = *(m_blobDatas[dataNum-1].curData(0, 0));
	return *(m_blobDatas[dataNum-2].curData(0, 0));
}


void lyNet::backward()
{
	int layerNum = m_layers.size();
	for (int i = layerNum-1; i >= 0; i--)
	{
		m_layers[i]->setLabel(m_label);
		m_layers[i]->backward(m_blobDatas[i], m_blobDatas[i + 1]);
	}
}

void lyNet::updateNet()
{
	for (int i = 0; i < 2; i++)
	{
		if (m_layers[i]->m_bNeedLearn)
		{
			m_layers[i]->update();
		}
	}
}

void lyNet::printLayer()
{
	int layerNum = m_layers.size();
	for (int i = 0; i < layerNum; i++)
	{
		if (m_layers[i]->m_bNeedLearn)
		{
			int height = m_layers[i]->m_weightData->m_nHeight;
			int width = m_layers[i]->m_weightData->m_nWidth;
			cout << endl << "weight layer" << i << " data:" << endl;
			for (int m = 0; m < height; m++)
			{
				for (int n = 0; n < width; n++)
					cout << *(m_layers[i]->m_weightData->curData(m, n)) << " ";
			}
			cout << endl << "weight layer" << i << " diff:" << endl;
			for (int m = 0; m < height; m++)
			{
				for (int n = 0; n < width; n++)
					cout << *(m_layers[i]->m_weightData->curDiff(m, n)) << " ";
			}
			cout << endl;
		}
	}
}


void lyNet::printData()
{
	cout << endl;
	cout << "data[1]: " << *(m_blobDatas[1].curData(0, 0)) << endl;
	cout << "data[1].diff: " << *(m_blobDatas[1].curDiff(0, 0)) << endl;
	cout << "data[2]: " << *(m_blobDatas[2].curData(0, 0)) << endl;
	cout << "data[2].diff: " << *(m_blobDatas[2].curDiff(0, 0)) << endl;
}



void lyNet::train()
{
	m_nIter = 0;
	for (int i = 0; i < m_nMaxIter; i++)
	{
		srand(time(0));
		for (int j = 0; j < 100; j++)
		{
			double x1 = random(20);
			double x2 = random(20);
			double x3 = random(20);
			double label = x1 * 20 + x2 * 13 + x3 * (-1);
			//cout << "x1:" << x1 << "  x2:" << x2 << "  x3:" << x3 << "  label:"<<label<<endl;
			blobData inputData(3, 1);
			*(inputData.curData(0, 0)) = x1;
			*(inputData.curData(1, 0)) = x2;
			*(inputData.curData(2, 0)) = x3;
			blobData labelData(1, 1);
			*(labelData.curData(0, 0)) = label;
			setTrainData(inputData, labelData);
			trainIter();
			m_nIter++;
			//cout << "m_nIter = " << m_nIter << "; m_dLoss = " << m_dLoss << endl;
			if (m_dLoss <= m_dMinLoss)
			{
			//	return;
			}
			//printLayer();
		}
	}
}

void lyNet::trainIter()
{
	forward();
	backward();
	updateNet();
}

void lyNet::readFromModel(std::string fileName)
{
	ifstream in(fileName);
	for (auto& it : m_layers)
	{
		if (it->m_bNeedLearn)
		{
			int weiHeight = it->m_weightData->m_nHeight;
			int weiWidth = it->m_weightData->m_nWidth;
			for (int i = 0; i < weiHeight; i++)
			{
				for (int j = 0; j < weiWidth; j++)
				{
					double value;
					in >> value;
					*(it->m_weightData->curData(i, j)) = value;
				}
			}
		}
	}

	in.close();
}

void lyNet::writeToModel(std::string fileName)
{
	ofstream out(fileName);
	for (auto& it : m_layers)
	{
		if (it->m_bNeedLearn)
		{
			int weiHeight = it->m_weightData->m_nHeight;
			int weiWidth = it->m_weightData->m_nWidth;

			for (int i = 0; i < weiHeight; i++)
			{
				for (int j = 0; j < weiWidth; j++)
				{
					double value = *(it->m_weightData->curData(i, j));
					out << value;
					out << " ";
				}
			}
		}
	}

	out.close();
}