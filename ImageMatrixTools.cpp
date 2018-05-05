#include "stdafx.h"
#include "ImageMatrixTools.h"

ImageMatrixTools::ImageMatrixTools()
{
}


ImageMatrixTools::~ImageMatrixTools()
{
}

std::vector<int> ImageMatrixTools::ImageToMatrix(Eigen::MatrixXd*& eigenMatrix, std::string location)
{
	std::vector<int> imageSize;

	cv::Mat image;
	image = cv::imread(location);

	if (!image.data)
	{
		std::cout << "Could not open or find the image" << std::endl;
		imageSize.push_back(-1);
		imageSize.push_back(-1);
		return imageSize;
	}

	//cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);// Create a window for display.
	//imshow("Display window", image);                   // Show our image inside it.
	//
	//cv::waitKey(0);

	int imageRows = image.rows;
	int imageCols = image.cols;

	imageSize.push_back(imageRows);
	imageSize.push_back(imageCols);

	//int imageChannels = image.channels();
	int offset = 0;

	eigenMatrix = new Eigen::MatrixXd(imageRows, imageCols * 3);

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

	return imageSize;
}

std::vector<int> ImageMatrixTools::RGBImageToRGBMatrix(Eigen::MatrixXd*& red, Eigen::MatrixXd*& green, Eigen::MatrixXd*& blue, std::string location)
{
	std::vector<int> imageSize;
	cv::Mat image;
	image = cv::imread(location);

	if (!image.data)
	{
		std::cout << "Could not open or find the image" << std::endl;
		imageSize.push_back(-1);
		imageSize.push_back(-1);
		return imageSize;
	}

	int imageRows = image.rows;
	int imageCols = image.cols;

	imageSize.push_back(imageRows);
	imageSize.push_back(imageCols);

	red   = new Eigen::MatrixXd(imageRows, imageCols);
	green = new Eigen::MatrixXd(imageRows, imageCols);
	blue  = new Eigen::MatrixXd(imageRows, imageCols);

	for (int i = 0; i < imageRows; ++i)
	{
		for (int j = 0; j < imageCols; ++j)
		{
			cv::Vec3b bgrPixel = image.at<cv::Vec3b>(i, j);
			red->data()[i*imageCols + j] = bgrPixel[2];
			green->data()[i*imageCols + j] = bgrPixel[1];
			blue->data()[i*imageCols + j] = bgrPixel[0];
		}
	}

	return imageSize;
}

void ImageMatrixTools::MatrixToImage(Eigen::MatrixXd* eigenMatrix, std::string location)
{
	assert(eigenMatrix != nullptr);

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

void ImageMatrixTools::RGBMatrixToRGBImage(Eigen::MatrixXd* red, Eigen::MatrixXd* green, Eigen::MatrixXd* blue, std::string location)
{
	assert(red != nullptr);
	assert(green != nullptr);
	assert(blue != nullptr);

	int imageRows = red->rows();
	int imageCols = red->cols();

	cv::Mat image(imageRows, imageCols, CV_8UC3);

	for (int i = 0; i < imageRows; ++i)
	{
		for (int j = 0; j < imageCols; ++j)
		{
			cv::Vec3b bgrPixel;
			bgrPixel[2] = red->data()[i*imageCols + j];
			bgrPixel[1] = green->data()[i*imageCols + j];
			bgrPixel[0] = blue->data()[i*imageCols + j];
			image.at<cv::Vec3b>(i, j) = bgrPixel;
		}
	}

	cv::imwrite(location, image);
}