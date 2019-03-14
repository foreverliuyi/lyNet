#ifndef _RELULAYER_H_
#define _RELULAYER_H_
#include "lylayer.h"


class reluLayer :public lylayer
{
public:
	reluLayer();
	void forward(blobData& inputData, blobData& outData);
	void backward(blobData& inputData, blobData& outData);
};



#endif
