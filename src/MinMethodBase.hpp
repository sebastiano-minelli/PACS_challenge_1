#ifndef HH_MINMETHODBASE_HH
#define HH_MINMETHODBASE_HH

#include<array>
#include "ParameterHandler.hpp"
#include "StepCoefficientHandler.hpp"

template<unsigned int DIM>
class MinMethodBase
{
public:

    MinMethodBase(ParameterHandler<DIM>& param) : m_param(param), m_step_handl(param) {};
    virtual ~MinMethodBase() = default;

    virtual std::array<double, DIM> compute_min() = 0;

ParameterHandler<DIM> m_param;
StepCoefficientHandler<DIM> m_step_handl;

};

#endif