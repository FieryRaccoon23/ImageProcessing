#include "IncludedLibraries.h"

#pragma once
class ImageMatrixTools
{
public:
	ImageMatrixTools();
	~ImageMatrixTools();

	static
	int ImageToMatrix(Eigen::MatrixXd*& eigenMatrix, std::string location);

	static
	void MatrixToImage(Eigen::MatrixXd* eigenMatrix, std::string location);
};

