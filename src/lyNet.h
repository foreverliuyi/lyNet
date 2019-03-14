#ifndef _LYNET_H_
#define _LYNET_H_
#include <vector>
#include <string>
#include "lylayer.h"
#include "lossLayer.h"
#include "fcLayer.h"
#include "reluLayer.h"

class lyNet
{
public:
	explicit lyNet();
	std::vector<lylayer*> m_layers;
	std::vector<blobData> m_blobDatas;
	blobData m_label;
	void setData(blobData& inputData);
	void setTrainData(blobData& inputData, blobData& labelData);
	double forward();
	void backward();
	void updateNet();

	void printLayer();
	void printData();

	void train();
	void trainIter();
public:
	int m_nMaxIter;
	int m_nIter;
	double m_dLoss;
	double m_dMinLoss;
	void readFromModel(std::string fileName);
	void writeToModel(std::string fileName);
};






#endif
