#ifndef HH_MINMETHODGRADIENT_HH
#define HH_MINMETHODGRADIENT_HH

#include "MinMethodBase.hpp"
#include <vector>
#include <array>

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
            alpha_k = this->m_step_handl.get_alpha_k(k);
            grad_k = this->m_param.compute_gradient();

            for(size_t j = 0; j < DIM; ++j)
                xnew[j] = xold[j] - alpha_k * grad_k[j];
            
            x_norm = 0.0;
            // compute x norm
            for(size_t z = 0; z < DIM; ++z)
            {
                x_norm += (xnew[z] - xold[z]) * (xnew[z] - xold[z]);
                x_norm = sqrt(x_norm);
            }

            res = abs(this->m_param.function_param.fun(xnew) - this->m_param.function_param.fun(xold));

            xold = xnew;
        }

        return xold;
    };
};

#endif