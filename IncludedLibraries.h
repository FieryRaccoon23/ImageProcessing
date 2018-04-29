#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <assert.h>

//Eigen libraries
#include <Dense> 
#include <Windows.h> 
#include <unsupported/Eigen/FFT>

//OpenGL
#include <GL\glew.h> 
#include <GL\freeglut.h> 

//CUDA runtime
#include <cuda_runtime.h>

//Helper functions and utilities to work with CUDA
#include <helper_functions.h>
#include <helper_cuda.h>

//OpenCV
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
