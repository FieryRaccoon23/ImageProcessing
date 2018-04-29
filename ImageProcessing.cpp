#include "stdafx.h"
#include "IncludedLibraries.h"
#include "Display.h"
#include "Tools.h"

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
	Eigen::MatrixXd Kernel(5,5);
	Eigen::MatrixXd* K = &Kernel;

	Eigen::MatrixXd Input(5, 5);
	Eigen::MatrixXd* I = &Input;

	Eigen::MatrixXd Output(5, 5);
	Eigen::MatrixXd* O = &Output;

	Tools::GaussianKernel(K, 3.0f);

	return 0;
}

