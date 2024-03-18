#ifndef HH_MINMETHODBASE_HH
#define HH_MINMETHODBASE_HH

#include<array>
#include "ParameterHandler.hpp"
#include "StepCoefficientHandler.hpp"

template<unsigned int DIM>
class MinMethodBase
{
public:

    MinMethodBase(const ParameterHandler<DIM>& param) : m_param(param), m_step_handl(param) {};
    virtual ~MinMethodBase() = default;

    virtual std::array<double, DIM> compute_min() const = 0;

    const ParameterHandler<DIM> m_param;
    const StepCoefficientHandler<DIM> m_step_handl;

};

#endif