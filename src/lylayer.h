#ifndef _LYLAYER_H_
#define _LYLAYER_H_

#include "blobData.h"

class lylayer
{
public:
	bool m_bNeedLearn;
	blobData m_labelData;
	blobData* m_weightData;
	lylayer() :m_labelData(1, 1), m_weightData(nullptr){};
	void setLabel(blobData labelData){ m_labelData = labelData; };

	virtual void forward(blobData& inputData, blobData& outData){};
	virtual void backward(blobData& inputData, blobData& outData){};
	virtual void update(){};
};

#endif
