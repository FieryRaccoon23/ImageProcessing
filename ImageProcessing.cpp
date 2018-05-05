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

	//int row = 240;//148;
	//int col = 240;//192;

	Eigen::MatrixXd Kernel(3, 3);
	Eigen::MatrixXd* K = &Kernel;

	Eigen::MatrixXd* I = nullptr;
	Eigen::MatrixXd* r = nullptr;
	Eigen::MatrixXd* g = nullptr;
	Eigen::MatrixXd* b = nullptr;


	//Eigen::MatrixXd Output(row, col);
	Eigen::MatrixXd* Or = nullptr;
	Eigen::MatrixXd* Og = nullptr;
	Eigen::MatrixXd* Ob = nullptr;

	Tools::GaussianKernel(K, 1.0f);
	
	//int error = ImageMatrixTools::ImageToMatrix(I, "C:/Users/Araib/Documents/Visual Studio 2015/Projects/ImageProcessing/ImageProcessing/Images/7.jpg");
	//
	////Tools::PadMatrixAround(K, row, col * 3);
	////Tools::FourierConvolution(O, I, K, true, false);
	//ImageMatrixTools::MatrixToImage(I, "C:/Users/Araib/Documents/Visual Studio 2015/Projects/ImageProcessing/ImageProcessing/Images/Result.jpg");

	std::vector<int> imageSize = ImageMatrixTools::RGBImageToRGBMatrix(r,g,b, "C:/Users/Araib/Documents/Visual Studio 2015/Projects/ImageProcessing/ImageProcessing/Images/7.jpg");
	Tools::PadMatrixAround(K, imageSize[0], imageSize[0]);
	//Tools::FourierConvolution(Or, r, K, true, false);
	//Tools::FourierConvolution(Og, g, K, true, false);
	//Tools::FourierConvolution(Ob, b, K, true, false);
	ImageMatrixTools::RGBMatrixToRGBImage(r,g,b, "C:/Users/Araib/Documents/Visual Studio 2015/Projects/ImageProcessing/ImageProcessing/Images/Result.jpg");

	return 0;
}

