#include "stdafx.h"
#include "IncludedLibraries.h"
#include "Display.h"
#include "Tools.h"
#include "ImageMatrixTools.h"

using Eigen::MatrixXd;
using namespace std;

int main(int argc, char* argv[])
{
	//uint16_t displayError = Display::DrawWindow(argc, argv, "COW");
    //return displayError;

	//Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Output;
	//Eigen::MatrixXd* Input = nullptr;
	//Tools::ForwardFourierTransform(Output, Input, false);
	//Tools::InverseFourierTransform(Input, Output, false, true);
	//
	//Eigen::MatrixXd* O = nullptr;
	//Eigen::MatrixXd* I = nullptr;
	//Eigen::MatrixXd* K = nullptr;
	//Tools::FourierConvolution(O, I, K);
	//
	//Tools::GaussianKernel(K, 3.0f);

	int row = 250;
	int col = 250;

	Eigen::MatrixXd Kernel(3, 3);
	Eigen::MatrixXd* K = &Kernel;

	//Eigen::MatrixXd Input(row, col * 3);
	Eigen::MatrixXd* I = nullptr;// = &Input;
	Eigen::MatrixXd* r = nullptr;
	Eigen::MatrixXd* g = nullptr;
	Eigen::MatrixXd* b = nullptr;


	Eigen::MatrixXd Output(row, col * 3);
	Eigen::MatrixXd* O = &Output;

	Tools::GaussianKernel(K, 3.0f);
	
	//int error = ImageMatrixTools::ImageToMatrix(I, "C:/Users/Araib/Documents/Visual Studio 2015/Projects/ImageProcessing/ImageProcessing/Images/RedSpot.jpg");
	
	//Tools::PadMatrixAround(K, row, col * 3);
	//Tools::FourierConvolution(O, I, K, true, false);
	//ImageMatrixTools::MatrixToImage(I, "C:/Users/Araib/Documents/Visual Studio 2015/Projects/ImageProcessing/ImageProcessing/Images/Result.jpg");

	ImageMatrixTools::RGBImageToRGBMatrix(r,g,b, "C:/Users/Araib/Documents/Visual Studio 2015/Projects/ImageProcessing/ImageProcessing/Images/RedSpot.jpg");
	ImageMatrixTools::RGBMatrixToRGBImage(r,g,b, "C:/Users/Araib/Documents/Visual Studio 2015/Projects/ImageProcessing/ImageProcessing/Images/Result.jpg");

	return 0;
}

