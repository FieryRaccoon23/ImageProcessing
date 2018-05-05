#include "stdafx.h"
#include "Tools.h"

Tools::Tools()
{
}


Tools::~Tools()
{
}


void Tools::ImageToMatrix(Eigen::MatrixXd* red, Eigen::MatrixXd* green, Eigen::MatrixXd* blue, std::string location)
{
}

void Tools::ForwardFourierTransform(Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& Output,
									Eigen::MatrixXd* Input, bool halfSpecturm)
{
	int matrixRowsCount = Input->rows();
	int matrixColumnsCount = Input->cols();

	Eigen::FFT<float> fft;

	if (halfSpecturm)
		fft.SetFlag(Eigen::FFT<float>::HalfSpectrum);

	std::vector<float> timevecRow;
	std::vector<std::complex<float>> freqvecRow;

	std::vector<float> timevecCol;
	std::vector<std::complex<float>> freqvecCol;

	Eigen::MatrixXd tempTime(matrixRowsCount, matrixColumnsCount);
	Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> tempFreq(matrixRowsCount, matrixColumnsCount);

	for (int i = 0; i < matrixRowsCount; ++i)
	{
		for (int j = 0; j < matrixColumnsCount; ++j)
		{
			timevecRow.push_back((*Input)(i, j));
		}
		
		fft.fwd(freqvecRow, timevecRow);
		
		for (int j = 0; j < matrixColumnsCount; ++j)
		{
			(tempFreq)(i, j) = freqvecRow[j];
		}

		freqvecRow.clear();
		timevecRow.clear();
	}

	freqvecRow.clear();
	timevecRow.clear();

	for (int j = 0; j < matrixColumnsCount; ++j)
	{
		for (int i = 0; i < matrixRowsCount; ++i)
		{
			freqvecCol.push_back((tempFreq)(i, j));
		}

		fft.fwd(freqvecRow, freqvecCol);

		for (int i = 0; i < matrixRowsCount; ++i)
		{
			(Output)(i, j) = freqvecRow[i];
		}

		freqvecRow.clear();
		freqvecCol.clear();
	}
}

void Tools::InverseFourierTransform(Eigen::MatrixXd*& Output,
									Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& Input,
									bool halfSpecturm, bool shiftFromCenter)
{
	int matrixRowsCount = Input.rows();
	int matrixColumnsCount = Input.cols();

	Eigen::FFT<float> fft;

	if (halfSpecturm)
		fft.SetFlag(Eigen::FFT<float>::HalfSpectrum);

	std::vector<float> timevecRow;
	std::vector<std::complex<float> > freqvecRow;

	std::vector<std::complex<float> > timevecCol;
	std::vector<std::complex<float> > freqvecCol;

	Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> tempTime(matrixRowsCount, matrixColumnsCount);
	Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> tempFreq(matrixRowsCount, matrixColumnsCount);


	for (int j = 0; j < matrixColumnsCount; ++j)
	{
		for (int i = 0; i < matrixRowsCount; ++i)
		{
			freqvecCol.push_back((Input)(i, j));
		}

		fft.inv(timevecCol, freqvecCol);

		for (int i = 0; i < matrixRowsCount; ++i)
		{
			(tempTime)(i, j) = timevecCol[i];
		}

		freqvecCol.clear();
		timevecCol.clear();
	}

	freqvecCol.clear();
	timevecCol.clear();

	for (int i = 0; i < matrixRowsCount; ++i)
	{
		for (int j = 0; j < matrixColumnsCount; ++j)
		{
			freqvecRow.push_back((tempTime)(i, j));
		}

		fft.inv(timevecRow, freqvecRow);

		for (int j = 0; j < matrixColumnsCount; ++j)
		{
			if (shiftFromCenter)
			{
				(*Output)((i + matrixRowsCount / 2) % matrixRowsCount, (j + matrixColumnsCount / 2) % matrixColumnsCount) = timevecRow[j];
			}
			else
			{
				(*Output)(i, j) = timevecRow[j];
			}
		}

		freqvecRow.clear();
		timevecRow.clear();
	}

}

void Tools::FourierConvolution(Eigen::MatrixXd*& Output, Eigen::MatrixXd* Input, Eigen::MatrixXd* K, bool shiftFromCenter, bool halfSpectrum)
{
	assert(Input->rows() == K->rows() && Input->cols() == K->cols());

	int imgRows    = Input->rows();
	int imgColumns = Input->cols();

	Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> freqDomainOutputImage(imgRows, imgColumns);
	Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> freqDomainKernel(imgRows, imgColumns);
	Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> freqDomainInputImage(imgRows, imgColumns);

	//DSFT: Time Domain Kernel =======> Frequency Domain Kernel
	ForwardFourierTransform(freqDomainKernel, K, halfSpectrum);

	//DSFT: Time Domain Input Image =======> Frequency Domain Input Image
	ForwardFourierTransform(freqDomainInputImage, Input, halfSpectrum);

	freqDomainOutputImage = freqDomainInputImage.cwiseProduct(freqDomainKernel);

	//DSFT: Frequency Domain Output Image =======> Time Domain Output Image
	Output = new Eigen::MatrixXd(imgRows, imgColumns);
	InverseFourierTransform(Output, freqDomainOutputImage, shiftFromCenter, halfSpectrum);
}

void Tools::GaussianKernel(Eigen::MatrixXd*& Kernel, float sigma)
{
	int kernelRow = Kernel->rows();
	int kernelCol = Kernel->cols();
	int midValueRow = kernelRow / 2;
	int midValueCol = kernelCol / 2;

	for (int i = 0; i < kernelRow; ++i)
	{
		for (int j = 0; j < kernelCol; ++j)
		{
			float value = -(pow(static_cast<float>(i - midValueRow), 2.0f) + pow(static_cast<float>(j - midValueCol), 2.0f)) 
						  / (2.0f * sigma * sigma);
			(*Kernel)(i, j) = exp(value);
		}
	}
	(*Kernel) /= Kernel->sum();
}

void Tools::PadMatrixAround(Eigen::MatrixXd*& Input, int newRow, int newCol, float value)
{
	Eigen::MatrixXd* mat = new Eigen::MatrixXd(newRow, newCol);
	*mat = Eigen::MatrixXd::Constant(newRow,newCol, value);

	assert(Input->rows() < newRow && Input->cols() < newCol);

	int startRow = (newRow - Input->rows()) / 2;
	int startCol = (newCol - Input->cols()) / 2;

	mat->block(startRow, startCol, Input->rows(), Input->cols()) = (*Input);

	//delete matrix
	Input->resize(0, 0);

	Input = mat;
}

void Tools::ShiftMatrixCenter(Eigen::MatrixXd*& Input)
{
	int imageRows = Input->rows();
	int imageCols = Input->cols();

	Eigen::MatrixXd* shiftedMatrix = new Eigen::MatrixXd(imageRows, imageCols);

	for (int i = 0; i < imageRows; ++i)
	{
		for (int j = 0; j < imageCols; ++j)
		{
			(*shiftedMatrix)((i + imageRows / 2) % imageRows, (j + imageCols / 2) % imageCols) = (*Input)(i, j);
		}
	}

	Input->resize(0,0);
	Input = shiftedMatrix;
}
