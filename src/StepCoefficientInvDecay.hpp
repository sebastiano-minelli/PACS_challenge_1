#ifndef HH_STEP_COEFFICIENT_INV_DECAY_HH
#define HH_STEP_COEFFICIENT_INV_DECAY_HH


#include<cmath>
#include "StepCoefficientBase.hpp"

template <unsigned int DIM>
class StepCoefficientInvDecay : public StepCoefficientBase<DIM>
{
public:
    StepCoefficientInvDecay(ParameterHandler<DIM> & param) : StepCoefficientBase<DIM>(param) {};

    double compute_alpha_k(const unsigned int step) override
    {
        double alpha_k =  this->m_param.step_coeff_method.alpha_zero / ( 1 + this->m_param.step_coeff_method.mu * static_cast<double>(step) );
        return alpha_k;
    }

};

#endif