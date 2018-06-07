#include "IncludedLibraries.h"

#pragma once
class Solver
{
public:
	Solver();
	~Solver();

    void InPaintingSolver(Eigen::MatrixXd*& CompletedMatrix, Eigen::MatrixXd* InputMatrix, Eigen::MatrixXd* MaskMatrix, float tol = 10e-7,
                          float softThreshold = 5.f, float step = 0.1f, float increment = 1.f, float parameter = 900.f, float l2RelaxationParamter = 2.f,
                          int iterations = 100);
};

