#ifndef HH_STEP_COEFFICIENT_BASE_HH
#define HH_STEP_COEFFICIENT_BASE_HH

#include "ParameterHandler.hpp"

template <unsigned int DIM>
class StepCoefficientBase
{
public:
    StepCoefficientBase(const ParameterHandler<DIM>& param) : m_param(param) {};

    virtual ~StepCoefficientBase() = default;

    // compute the step parameter alpha_k
    virtual const double compute_alpha_k(const unsigned int step, std::array<double, DIM> point = {}) const = 0;

    const ParameterHandler<DIM> m_param;
};

#endif