#include "stdafx.h"
#include "IncludedLibraries.h"
#include "Display.h"
#include "Tools.h"
#include "ImageMatrixTools.h"

using Eigen::MatrixXd;
using namespace std;

int main(int argc, char* argv[])
{
	Eigen::MatrixXd* I = nullptr;
	Eigen::MatrixXd* r = nullptr;
	Eigen::MatrixXd* g = nullptr;
	Eigen::MatrixXd* b = nullptr;


	Eigen::MatrixXd* O = nullptr;
	Eigen::MatrixXd* Or = nullptr;
	Eigen::MatrixXd* Og = nullptr;
	Eigen::MatrixXd* Ob = nullptr;

	std::vector<int> imageSize = ImageMatrixTools::RGBImageToRGBMatrix(r,g,b, "C:/Users/Araib/Documents/Visual Studio 2015/Projects/ImageProcessing/ImageProcessing/Images/7.jpg");
	//Eigen::MatrixXd Filter(10,10);
	//Eigen::MatrixXd* F = &Filter;
	//Tools::GaussianKernel(F, 3.0f);
	//Tools::PadMatrixAround(F, imageSize[0], imageSize[1]);
	Eigen::MatrixXd* F = nullptr;
	Tools::SobelGradientX(F, imageSize[0], imageSize[1]);
	Tools::FourierConvolution(Or, r, F, false, false);
	Tools::FourierConvolution(Og, g, F, false, false);
	Tools::FourierConvolution(Ob, b, F, false, false);
	Tools::ShiftMatrixCenter(Or);
	Tools::ShiftMatrixCenter(Og);
	Tools::ShiftMatrixCenter(Ob);
	ImageMatrixTools::RGBMatrixToRGBImage(Or,Og,Ob, "C:/Users/Araib/Documents/Visual Studio 2015/Projects/ImageProcessing/ImageProcessing/Images/Result.jpg");

	return 0;
}

