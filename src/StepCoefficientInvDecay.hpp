#ifndef HH_STEP_COEFFICIENT_INV_DECAY_HH
#define HH_STEP_COEFFICIENT_INV_DECAY_HH


#include<cmath>
#include "StepCoefficientBase.hpp"

class StepCoefficientInvDecay : public StepCoefficientBase
{
public:
    StepCoefficientInvDecay(const double alpha_zero, const double mu = 0.2) : StepCoefficientBase(alpha_zero), m_mu(mu) {};

    double compute_alpha_k(const unsigned int step, const double alpha_zero) const override
    {
        double alpha_k =  m_alpha_zero / ( 1 + m_mu * static_cast<double>(step) );
        return alpha_k;
    }

private:
    const double m_mu;

};

#endif