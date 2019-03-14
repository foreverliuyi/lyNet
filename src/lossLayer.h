#ifndef _LOSSLAYER_H_
#define _LOSSLAYER_H_

#include "lylayer.h"

class lossLayer :public lylayer
{
public:
	lossLayer();

	void setLabel(blobData labelData){ m_labelData = labelData; };
	void forward(blobData& inputData, blobData& outData);
	void backward(blobData& inputData, blobData& outData);
};

#endif