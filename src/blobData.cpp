#include <iostream>
#include <string.h>
#include "lylayer.h"

using namespace std;

blobData::blobData(int h, int w)
{
	if (m_pData != nullptr)
		delete m_pData;
	if (m_pDiff != nullptr)
		delete m_pDiff;

	m_nHeight = h;
	m_nWidth = w;;
	m_pData = new double[h*w];
	for (int i = 0; i < h*w; i++)
		*(m_pData+i) = 1;
	
	m_pDiff = new double[h*w];
	
	for (int i = 0; i < h*w; i++)
		*(m_pDiff + i) = 0.0;
}

blobData::blobData(const blobData &data)
{
	m_nHeight = data.m_nHeight;
	m_nWidth = data.m_nWidth;
	m_pData = new double[m_nHeight*m_nWidth];
	memcpy(m_pData, data.data(), m_nHeight*m_nWidth*sizeof(double));
	m_pDiff = new double[m_nHeight*m_nWidth];
	memcpy(m_pDiff, data.diff(), m_nHeight*m_nWidth*sizeof(double));
}

blobData& blobData::operator=(const blobData &data)
{
	if (this == &data)
		return *this;

	if (m_pData != nullptr)
		delete m_pData;
	if (m_pDiff != nullptr)
		delete m_pDiff;

	m_nHeight = data.m_nHeight;
	m_nWidth = data.m_nWidth;

	m_pData = new double[m_nHeight*m_nWidth];
	memcpy(m_pData, data.data(), m_nHeight*m_nWidth*sizeof(double));
	m_pDiff = new double[m_nHeight*m_nWidth];
	memcpy(m_pDiff, data.diff(), m_nHeight*m_nWidth*sizeof(double));

	return *this;
}

blobData::~blobData()
{
	if (m_pData != nullptr)
	{
		delete m_pData;
		m_pData = nullptr;
	}

	if (m_pDiff != nullptr)
	{
		delete m_pDiff;
		m_pDiff = nullptr;
	}
}

void blobData::update()
{
	if (m_pData==nullptr || m_pDiff==nullptr)
		return;

	double * pData = m_pData;
	double * pDiff = m_pDiff;
	for (int i = 0; i < m_nHeight*m_nWidth; i++)
	{
		*(m_pData+i) = *(m_pData+i) - *(pDiff+i)/10000;
	}
	return;
}

double* blobData::curData(int x, int y)
{
	double* pData = m_pData + (x*m_nWidth) + y;
	return pData;
}

double* blobData::curDiff(int x, int y)
{
	double* pDiff = m_pDiff + (x*m_nWidth) + y;
	return pDiff;
}
