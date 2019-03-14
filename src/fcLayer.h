#ifndef _FCLAYER_H_
#define _FCLAYER_H_
#include <string>
#include "lylayer.h"
using namespace std;

struct SfcLayerParam
{
	string name;
	int inputNum;
	int outputNum;
};

class fcLayer :public lylayer
{
public:
	explicit fcLayer(SfcLayerParam fcParam);
public:
	void forward(blobData& inputData, blobData& outputData);
	void backward(blobData& inputData, blobData& outputData);
	void update();
};




#endif
