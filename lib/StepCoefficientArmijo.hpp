#ifndef HH_STEP_COEFFICIENT_ARMIJO_HH
#define HH_STEP_COEFFICIENT_ARMIJO_HH

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include "muParserXInterface.hpp"
#include "StepCoefficientBase.hpp"

template <unsigned int DIM>
class StepCoefficientArmijo : public StepCoefficientBase<DIM>
{
public:
    StepCoefficientArmijo(const ParameterHandler<DIM> & param) : StepCoefficientBase<DIM>(param)
    {};

    const double compute_alpha_k(const unsigned int step, std::array<double, DIM> point) const override
    {
        const unsigned int n_max_it = 10000; // maximum number of iterations
        unsigned int it = 0; // iterations
        const double min_tol = std::numeric_limits<double>::epsilon() * 10.0; // minimum tolerance


        double alpha_k = 2.0 * this->m_param.step_coeff_method.alpha_zero;

        // compute argouments
        std::array<double, DIM> y;

        double L2norm = 0.0;
        std::vector<double> grad_eval = this->m_param.compute_gradient(point);
        
        for(size_t i = 0; i < DIM; ++i)
            L2norm += grad_eval[i] * grad_eval[i];

        double tolerance = 0.0;

        do
        {   
            alpha_k = alpha_k * 0.5;
            for(size_t i = 0; i < DIM; ++i)
                y[i] = this->m_param.function_param.x[i] - alpha_k * grad_eval[i];
            
            tolerance = this->m_param.function_param.fun(this->m_param.function_param.x) - this->m_param.function_param.fun(y); 

        }while(this->m_param.function_param.fun(this->m_param.function_param.x) - this->m_param.function_param.fun(y) < this->m_param.step_coeff_method.sigma * alpha_k * L2norm
                && it++ < n_max_it
                && tolerance > min_tol );

        return alpha_k;
    
    }

};

#endif