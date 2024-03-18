#ifndef HH_STEP_COEFFICIENT_BASE_HH
#define HH_STEP_COEFFICIENT_BASE_HH

#include "ParameterHandler.hpp"

template <unsigned int DIM>
class StepCoefficientBase
{
public:
    StepCoefficientBase(ParameterHandler<DIM>& param) : m_param(param) {};

    virtual ~StepCoefficientBase() = default;

    // compute the step parameter alpha_k
    virtual double compute_alpha_k(const unsigned int step) = 0;

    ParameterHandler<DIM> m_param;
};

#endif