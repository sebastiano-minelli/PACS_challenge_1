#ifndef HH_MINMETHOD_NESTEROV_HH
#define HH_MINMETHOD_NESTEROV_HH

#include "MinMethodBase.hpp"
#include <vector>
#include <array>
#include <cmath>

template<unsigned int DIM>
class MinMethodNesterov : public MinMethodBase<DIM>
{
public:

    MinMethodNesterov(const ParameterHandler<DIM>& param) : MinMethodBase<DIM>(param) 
    {};

    const std::array<double, DIM> compute_min() const override
    {
        // initialize method
        double alpha_k = this->m_param.step_coeff_method.alpha_zero; // alpha0
        std::array<double, DIM> xold_old{this->m_param.function_param.x}; //x0
        std::vector<double> grad_k = this->m_param.compute_gradient(xold_old); //grad0
        std::array<double, DIM> xold = {}; // x1
        for(size_t i = 0; i < DIM; ++i)
            xold[i] = xold_old[i] - alpha_k * grad_k[i];

        std::array<double, DIM> xnew{}; // x_{k+1}
        double x_norm = std::numeric_limits<double>::infinity(); // to enter loop
        double res = std::numeric_limits<double>::infinity(); // to enter loop
        
        // compute eta = (1 - alpha_k) if alpha_k < 1, eta = 0.9 otherwise
        constexpr double ETA_STD_VALUE = 0.9;
        double eta = ETA_STD_VALUE;
        if(alpha_k < 1)
            eta = 1 - alpha_k;
        else
            eta = ETA_STD_VALUE;

        // compute y
        std::array<double, DIM> y{};
        for(size_t i = 0; i < DIM; ++i)
            y[i] = xold[i] + eta * (xold[i] - xold_old[i]);

        // just to improve readability
        const unsigned int max_it = this->m_param.coefficients.max_it;
        const double tol_res = this->m_param.coefficients.tol_res;
        const double tol_x = this->m_param.coefficients.tol_x;

        // implement iteration
        for(size_t k = 2; k < max_it && res > tol_res && x_norm > tol_x; ++k)
        {
            alpha_k = this->m_step_handl.get_alpha_k(k - 1, xold);
            if(alpha_k < 1)
                eta = 1 - alpha_k;
            else
                eta = ETA_STD_VALUE;

            grad_k = this->m_param.compute_gradient(y);

            x_norm = 0.0;
            for(size_t j = 0; j < DIM; ++j)
            {  
                xnew[j] = y[j] - alpha_k * grad_k[j];
            
                // compute L2 x norm
                x_norm += (xnew[j] - xold[j]) * (xnew[j] - xold[j]);
            }
            x_norm = sqrt(x_norm);

            // compute residue
            double fxold = this->m_param.function_param.fun(xold);
            double fxnew = this->m_param.function_param.fun(xnew);
            res = std::fabs(fxnew - fxold);

            // update solutions
            xold_old = xold;
            xold = xnew;
            for(size_t i = 0; i < DIM; ++i)
                y[i] = xold[i] + eta * (xold[i] - xold_old[i]);
        }

        return xold;
    };
};

#endif