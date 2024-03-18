#ifndef HH_MINMETHODGRADIENT_HH
#define HH_MINMETHODGRADIENT_HH

#include "MinMethodBase.hpp"
#include <vector>
#include <array>
#include <cmath>

template<unsigned int DIM>
class MinMethodGradient : public MinMethodBase<DIM>
{
public:

    MinMethodGradient(ParameterHandler<DIM>& param) : MinMethodBase<DIM>(param) 
    {};

    std::array<double, DIM> compute_min() override
    {
        std::array<double, DIM> &xold{this->m_param.function_param.x}; // reference to change x directly
        std::array<double, DIM> xnew{};
        double x_norm = std::numeric_limits<double>::infinity(); // to enter loop
        double res = std::numeric_limits<double>::infinity(); // to enter loop

        double alpha_k = this->m_param.step_coeff_method.alpha_zero;
        std::vector<double> grad_k;

        unsigned int max_it = this->m_param.coefficients.max_it;
        double tol_res = this->m_param.coefficients.tol_res;
        double tol_x = this->m_param.coefficients.tol_x;


        for(size_t k = 0; k < max_it && res > tol_res && x_norm > tol_x; ++k)
        {
            grad_k = this->m_param.compute_gradient();
            std::cout << "alpha k: " << alpha_k << std::endl;

            for(size_t j = 0; j < DIM; ++j)
            {    xnew[j] = xold[j] - alpha_k * grad_k[j];
                std::cout << "xnew: {" << j + 1 << "}: " << xnew[j] << std::endl; 
                std::cout << "Grad evaluation from min grad: " << grad_k[j] << "[" << j + 1 << "]" << std::endl;
            }
            
            x_norm = 0.0;
            // compute x norm
            for(size_t z = 0; z < DIM; ++z)
                x_norm += (xnew[z] - xold[z]) * (xnew[z] - xold[z]);
            x_norm = sqrt(x_norm);
            std::cout << "Norm from min grad: " << x_norm << std::endl;    

            std::array<double, 2> vec = {1, 2};
            std::cout << "Function evaluation from min grad: " << this->m_param.function_param.fun(vec) << std::endl;

            double fxold = this->m_param.function_param.fun(xold);
            double fxnew = this->m_param.function_param.fun(xnew);
            if(fxnew >= fxold)
                res = fxnew - fxold;
            else
                res = fxold - fxnew;
            // res = abs(this->m_param.function_param.fun(xnew) - this->m_param.function_param.fun(xold));
            std::cout << "Residual: " << res << std::endl;
            std::cout << "f(new): " << this->m_param.function_param.fun(xnew) << std::endl;
            std::cout << "f(old): " << this->m_param.function_param.fun(xold) << std::endl;
            std::cout << "f diff: " << this->m_param.function_param.fun(xnew) - this->m_param.function_param.fun(xold) << std::endl;

            xold = xnew;
            for(size_t ii = 0; ii < DIM; ii++)
            {
            std::cout << "X old:" << xold[ii] << std::endl;
            std::cout << "x: " << this->m_param.function_param.x[ii] << std::endl;
            }
            alpha_k = this->m_step_handl.get_alpha_k(k);
        }

        return xold;
    };
};

#endif