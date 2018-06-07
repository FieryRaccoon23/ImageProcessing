#include "stdafx.h"
#include "Solver.h"


Solver::Solver()
{
}


Solver::~Solver()
{
}

void Solver::InPaintingSolver(Eigen::MatrixXd*& CompletedMatrix, Eigen::MatrixXd* InputMatrix, Eigen::MatrixXd* MaskMatrix, float tol /*= 10e-7*/,
                              float softThreshold /*= 5.f*/, float step /*= 0.1f*/, float increment /*= 1.f*/, float parameter /*= 900.f*/, float l2RelaxationParamter /*= 2.f*/,
                              int iterations /*= 100*/)
{
    assert(InputMatrix != nullptr);

    int imageRows = InputMatrix->rows();
    int imageCols = InputMatrix->cols();

    // Recovered data to be returned
    CompletedMatrix = new Eigen::MatrixXd(imageRows, imageCols);
    CompletedMatrix->setZero();

    Eigen::MatrixXd* ProcessingMatrix = new Eigen::MatrixXd(imageRows, imageCols);
    ProcessingMatrix->setZero();

    // P : PM = { M (i,j) if i,j in R else 0}
    //InternalMatrixType* PM = UsedMathKernel::Create(M->uRowsCount, M->uColumnsCount);
    //UsedMathKernel::Zero(PM);
    //
    //InternalDataType dataCount = 0;
    //for (Int32 i = 0; i < M->uRowsCount * M->uColumnsCount; ++i)
    //{
    //    auto value = mask->pData[i] > Consts::t0 ? Consts::t0 : Consts::t1;
    //
    //    if (value)
    //    {
    //        ++dataCount;
    //    }
    //
    //    PM->pData[i] = value * M->pData[i];
    //}
#if 0
    InternalDataType MFrobNorm = MathKernelDenseEigen::GetNormL2(M);

    InternalDataType k0 = (parameter / (step * MFrobNorm)) + 0.5f;

    // Initial Y: Y0
    for (Int32 i = 0; i < M->uRowsCount * M->uColumnsCount; ++i)
    {
        Y->pData[i] = k0 * step * PM->pData[i];
    }
#endif


    Eigen::MatrixXd* pU = new Eigen::MatrixXd(imageRows, imageRows);
    pU->setZero();

    Eigen::MatrixXd* pV = new Eigen::MatrixXd(imageCols, imageRows);
    pV->setZero();
    Eigen::MatrixXd* pVt = new Eigen::MatrixXd(pV->cols(), pV->rows());
    pVt->setZero();

    Eigen::MatrixXd* pS = new Eigen::MatrixXd(imageRows, imageRows);
    pS->setZero();

    int rank = std::min(imageRows, imageCols);
    Eigen::MatrixXd* partialU = new Eigen::MatrixXd(imageRows, rank);
    Eigen::MatrixXd* partialV = new Eigen::MatrixXd(imageCols, rank);

    float lastNuclearNorm = -1.f;
    float varianceValue = 0.f;


    for (int k = 0; k < iterations; ++k)
    {
        //Eigen::BDCSVD(pU, pS, pV, ProcessingMatrix);
#if 0
        MathKernelToolImpl::BDCSVD(pU, pS, pV, Y, SVDType::ComputeThinU | SVDType::ComputeThinV);

        for (UInt32 i = 0; i < rank; ++i)
        {
            if ((*pS)(i, i) < parameter)
            {
                (*pS)(i, i) = Consts::t0;
            }
        }

        MathKernelDenseEigen::SoftThresholdSelf(pS, softThreshold);
        UsedMathKernel::Transpose(pVt, pV);

        EigenMap(X) = EigenMapConst(pU) * EigenMapConst(pS) * EigenMapConst(pVt);

        /////////////////////////////////////////Exit Code///////////////////////////////////////
        InternalDataType currentNuclearNorm = EigenMapConst(pS).array().abs().sum();
        if (lastNuclearNorm != Consts::t_1 && lastNuclearNorm != Consts::t0)
        {
            InternalDataType nuclearNormRatio = currentNuclearNorm / lastNuclearNorm;

            std::cout << "Nuclear Norms Ratio: " << nuclearNormRatio << "  vs  Tolerance: " << tol << std::endl;

            if (nuclearNormRatio <= tol)
                break;
        }
        lastNuclearNorm = currentNuclearNorm;

        ///////////////////////////////////////////////////////////////////////////////////////

        for (Int32 i = 0; i < M->uRowsCount * M->uColumnsCount; ++i)
        {
            auto value = mask->pData[i] > Consts::t0 ? Consts::t0 : Consts::t1;
            if (value)
            {
                Y->pData[i] += step * (M->pData[i] - X->pData[i]);
            }
            else
            {
                Y->pData[i] = X->pData[i];
            }
        }

        UsedMathKernel::Zero(pU);
        UsedMathKernel::Zero(pV);
        UsedMathKernel::Zero(pS);

        std::cout << Scalar(k) / Scalar(n_iter_max)*100.f << " %" << std::endl;
#endif
    }

#if 0
    std::cout << "Inpainting Exited" << std::endl;
    bStopInPainting = false;
    UsedMathKernel::Destroy(partialV);
    UsedMathKernel::Destroy(partialU);
    UsedMathKernel::Destroy(pU);
    UsedMathKernel::Destroy(pV);
    UsedMathKernel::Destroy(pS);
    UsedMathKernel::Destroy(Y);
    UsedMathKernel::Destroy(PM);
#endif
}
