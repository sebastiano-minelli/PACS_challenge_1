#ifndef HH_STEP_COEFFICIENT_EXP_HH
#define HH_STEP_COEFFICIENT_EXP_HH


#include<cmath>
#include "StepCoefficientBase.hpp"

template <unsigned int DIM>
class StepCoefficientExp : public StepCoefficientBase<DIM>
{
public:
    StepCoefficientExp(const double alpha_zero, const double mu = 0.2) : StepCoefficientBase<DIM>(alpha_zero), m_mu(mu) {};

    double compute_alpha_k(const unsigned int step) const override
    {
        double alpha_k =  this->m_alpha_zero * exp(- m_mu * static_cast<double>(step));
        return alpha_k;
    }

private:
    const double m_mu;

};

#endif