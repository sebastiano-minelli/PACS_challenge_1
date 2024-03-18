#ifndef HH_MINMETHOD_ADAM_HH
#define HH_MINMETHOD_ADAM_HH

#include "MinMethodBase.hpp"
#include <vector>
#include <array>
#include <cmath>

template<unsigned int DIM>
class MinMethodAdam : public MinMethodBase<DIM>
{
public:

    MinMethodAdam(const ParameterHandler<DIM>& param) : MinMethodBase<DIM>(param) 
    {};

    std::array<double, DIM> compute_min() const override
    {
        std::array<double, DIM> xold{this->m_param.function_param.x};
        std::array<double, DIM> xnew{};
        double x_norm = std::numeric_limits<double>::infinity(); // to enter loop
        double res = std::numeric_limits<double>::infinity(); // to enter loop

        constexpr double alpha_k = 0.001;
        constexpr double beta_1 = 0.999;
        constexpr double beta_2 = 0.9;
        constexpr double eps = 1e-8;

        std::vector<double> grad_k;
        std::array<double, DIM> m = {}; //momentum 1
        std::array<double, DIM> v = {}; // momentum 2
        std::array<double, DIM> m_corr = {}; //momentum 1 bias corrected
        std::array<double, DIM> v_corr = {}; // momentum 2 bias corrected

        const unsigned int max_it = this->m_param.coefficients.max_it;
        const double tol_res = this->m_param.coefficients.tol_res;
        const double tol_x = this->m_param.coefficients.tol_x;


        for(size_t k = 1; k < max_it && res > tol_res && x_norm > tol_x; ++k)
        {
            grad_k = this->m_param.compute_gradient(xold);

            x_norm = 0.0;
            for(size_t i = 0; i < DIM; ++i)
            {    
                // update momentum 1
                m[i] = m[i] * beta_1 + (1 - beta_1) * grad_k[i];

                // update momentum 2
                v[i] = v[i] * beta_2 + (1 - beta_2) * grad_k[i] * grad_k[i];

                // update momentum 1 bias corrected
                m_corr[i] = m[i] / (1 - std::pow(beta_1, k));

                // update momentum 1 bias corrected
                v_corr[i] = v[i] / (1 - std::pow(beta_2, k));
            
                // update solution
                xnew[i] = xold[i] - alpha_k * m_corr[i] / (sqrt(v_corr[i]) + eps);
            
                // compute x norm
                x_norm += (xnew[i] - xold[i]) * (xnew[i] - xold[i]);
            }    
            x_norm = sqrt(x_norm);

            double fxold = this->m_param.function_param.fun(xold);
            double fxnew = this->m_param.function_param.fun(xnew);

            res = std::fabs(fxnew - fxold);

            xold = xnew;
        }

        return xold;
    };
};

#endif