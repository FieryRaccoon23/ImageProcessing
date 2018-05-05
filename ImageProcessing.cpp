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

	//Eigen::MatrixXd Kernel(3, 3);
	//Eigen::MatrixXd* K = &Kernel;

	Eigen::MatrixXd* I = nullptr;
	Eigen::MatrixXd* r = nullptr;
	Eigen::MatrixXd* g = nullptr;
	Eigen::MatrixXd* b = nullptr;


	//Eigen::MatrixXd Output(row, col);
	Eigen::MatrixXd* Or = nullptr;
	Eigen::MatrixXd* Og = nullptr;
	Eigen::MatrixXd* Ob = nullptr;

	//Tools::GaussianKernel(K, 10.0f);
	
	std::vector<int> imageSize = ImageMatrixTools::RGBImageToRGBMatrix(r,g,b, "C:/Users/Araib/Documents/Visual Studio 2015/Projects/ImageProcessing/ImageProcessing/Images/Square.jpg");
	//Tools::PadMatrixAround(K, imageSize[0] , imageSize[1] );
	//Tools::PadMatrixAround(r, imageSize[0] , imageSize[1] );
	//Tools::PadMatrixAround(g, imageSize[0] , imageSize[1] );
	//Tools::PadMatrixAround(b, imageSize[0] , imageSize[1] );

	Eigen::MatrixXd Filter(10,10);
	Eigen::MatrixXd* F = &Filter;
	Tools::GaussianKernel(F, 3.0f);
	Tools::PadMatrixAround(F, imageSize[0], imageSize[1]);
	Tools::FourierConvolution(Or, r, F, false, false);
	Tools::FourierConvolution(Og, g, F, false, false);
	Tools::FourierConvolution(Ob, b, F, false, false);
	Tools::ShiftMatrixCenter(Or);
	Tools::ShiftMatrixCenter(Og);
	Tools::ShiftMatrixCenter(Ob);

	ImageMatrixTools::RGBMatrixToRGBImage(Or,Og,Ob, "C:/Users/Araib/Documents/Visual Studio 2015/Projects/ImageProcessing/ImageProcessing/Images/Result.jpg");

	return 0;
}

