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

    MinMethodGradient(const ParameterHandler<DIM>& param) : MinMethodBase<DIM>(param) 
    {};

    const std::array<double, DIM> compute_min() const override
    {
        std::array<double, DIM> xold{this->m_param.function_param.x};
        std::array<double, DIM> xnew{};
        double x_norm = std::numeric_limits<double>::infinity(); // to enter loop
        double res = std::numeric_limits<double>::infinity(); // to enter loop

        double alpha_k = this->m_param.step_coeff_method.alpha_zero;
        std::vector<double> grad_k;

        const unsigned int max_it = this->m_param.coefficients.max_it;
        const double tol_res = this->m_param.coefficients.tol_res;
        const double tol_x = this->m_param.coefficients.tol_x;


        for(size_t k = 0; k < max_it && res > tol_res && x_norm > tol_x; ++k)
        {
            grad_k = this->m_param.compute_gradient(xold);

            x_norm = 0.0;
            for(size_t j = 0; j < DIM; ++j)
            {  
                xnew[j] = xold[j] - alpha_k * grad_k[j];
            
                // compute x norm
                x_norm += (xnew[j] - xold[j]) * (xnew[j] - xold[j]);
            }
            x_norm = sqrt(x_norm);

            double fxold = this->m_param.function_param.fun(xold);
            double fxnew = this->m_param.function_param.fun(xnew);

            res = std::fabs(fxnew - fxold);

            xold = xnew;
            alpha_k = this->m_step_handl.get_alpha_k(k, xold);
        }

        return xold;
    };
};

#endif