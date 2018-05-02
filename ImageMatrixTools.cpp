#include "stdafx.h"
#include "ImageMatrixTools.h"

ImageMatrixTools::ImageMatrixTools()
{
}


ImageMatrixTools::~ImageMatrixTools()
{
}

int ImageMatrixTools::ImageToMatrix(Eigen::MatrixXd*& eigenMatrix, std::string location)
{
	cv::Mat image;
	image = cv::imread(location);

	if (!image.data)
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	//Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> imageEigen(image.ptr<float>(), image.rows, image.cols);

	//cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);// Create a window for display.
	//imshow("Display window", image);                   // Show our image inside it.
	//
	//cv::waitKey(0);

	int imageRows = image.rows;
	int imageCols = image.cols;
	int imageChannels = image.channels();
	int offset = 0;
	for (int i = 0; i < imageRows; ++i)
	{
		for (int j = 0; j < imageCols; ++j)
		{
			//(*eigenMatrix)(i + 0, j) = imagePtr[i * imageCols * imageChannels + j *imageChannels + 0];

			cv::Vec3b bgrPixel = image.at<cv::Vec3b>(i, j);
			eigenMatrix->data()[offset + 0] = bgrPixel[2];
			eigenMatrix->data()[offset + 1] = bgrPixel[1];
			eigenMatrix->data()[offset + 2] = bgrPixel[0];

			offset += 3;
		}
	}

	return 0;
}


void ImageMatrixTools::MatrixToImage(Eigen::MatrixXd* eigenMatrix, std::string location)
{
	int imageRows = eigenMatrix->rows();
	int imageCols = eigenMatrix->cols() / 3;

	cv::Mat image(imageRows, imageCols, CV_8UC3);

	int offset = 0;
	for (int i = 0; i < imageRows; ++i)
	{
		for (int j = 0; j < imageCols; ++j)
		{
			cv::Vec3b bgrPixel;
			bgrPixel[0] = eigenMatrix->data()[offset + 2];
			bgrPixel[1] = eigenMatrix->data()[offset + 1];
			bgrPixel[2] = eigenMatrix->data()[offset + 0];
			image.at<cv::Vec3b>(i, j) = bgrPixel;

			offset += 3;
		}
	}

	cv::imwrite(location, image);
}
