#include "IncludedLibraries.h"

#pragma once
class ImageMatrixTools
{
public:
	ImageMatrixTools();
	~ImageMatrixTools();

	static
	std::vector<int> ImageToMatrix(Eigen::MatrixXd*& eigenMatrix, std::string location);

	static
	std::vector<int> RGBImageToRGBMatrix(Eigen::MatrixXd*& red, Eigen::MatrixXd*& green, Eigen::MatrixXd*& blue, std::string location);

	static
	void MatrixToImage(Eigen::MatrixXd* eigenMatrix, std::string location);

	static
	void RGBMatrixToRGBImage(Eigen::MatrixXd* red, Eigen::MatrixXd* green, Eigen::MatrixXd* blue, std::string location);
};

