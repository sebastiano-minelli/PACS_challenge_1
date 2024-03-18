#ifndef HH_STEP_COEFFICIENT_EXP_HH
#define HH_STEP_COEFFICIENT_EXP_HH


#include<cmath>
#include "StepCoefficientBase.hpp"

template <unsigned int DIM>
class StepCoefficientExp : public StepCoefficientBase<DIM>
{
public:
    StepCoefficientExp(const ParameterHandler<DIM> & param) : StepCoefficientBase<DIM>(param) {};

    double compute_alpha_k(const unsigned int step, std::array<double, DIM> point = {}) const override
    {
        double alpha_k =  this->m_param.step_coeff_method.alpha_zero * exp(- this->m_param.step_coeff_method.mu * static_cast<double>(step));
        return alpha_k;
    }

};

#endif