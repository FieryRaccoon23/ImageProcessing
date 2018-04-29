#include "IncludedLibraries.h"

#pragma once
class Tools
{
public:
	Tools();
	~Tools();

	static 
	void ImageToMatrix(Eigen::MatrixXd* red, Eigen::MatrixXd* green, Eigen::MatrixXd* blue, std::string location);

	static
	void ForwardFourierTransform(Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& Output, 
								 Eigen::MatrixXd* Input, bool halfSpecturm);

	static
	void InverseFourierTransform(Eigen::MatrixXd*& Output,
								 Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& Input,
								 bool halfSpecturm, bool shiftFromCenter);

	static
	void FourierConvolution(Eigen::MatrixXd*& Output, Eigen::MatrixXd* Input, Eigen::MatrixXd* K, 
							bool shiftFromCenter = true, bool halfSpectrum = false);

	static
	void GaussianKernel(Eigen::MatrixXd*& Kernel, float sigma);
	
};

