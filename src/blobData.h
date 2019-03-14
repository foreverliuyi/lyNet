#ifndef _BLOBDATA_H_
#define _BLOBDATA_H_



class blobData
{
public:
	blobData(int w, int h);
	blobData(const blobData &data);
	blobData& operator=(const blobData &data);
	~blobData();
	int m_nWidth;
	int m_nHeight;
	double* data() const{ return m_pData; }
	double* diff() const { return m_pDiff; }
	double* curData(int x, int y);   //��x�У� ��y��
	double* curDiff(int x, int y);   //��x�У� ��y��

private:
	double* m_pData;
	double* m_pDiff;

public:
	void update();
};

#endif // !_DATASTRUCT_H_