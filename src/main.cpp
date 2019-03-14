#include <iostream>
#include "blobData.h"
#include "lylayer.h"
#include "fcLayer.h"
#include "lyNet.h"

using namespace std;



int main()
{
	lyNet net;

	net.train();

	net.writeToModel("../../dat/model.lymodel");
	net.printLayer();
	
	blobData inputData(3, 1);
	*(inputData.curData(0, 0)) = 1;
	*(inputData.curData(1, 0)) = 21;
	*(inputData.curData(2, 0)) = 11;
	blobData labelData(1, 1);
	*(labelData.curData(0, 0)) = 20;
	net.setTrainData(inputData, labelData);
	double res = net.forward();
	cout << "res = " << res << endl;

	net.readFromModel("../../dat/model.lymodel");
	//net.printLayer();
	res = net.forward();
	cout << "res = " << res << endl;
	
}