#ifndef HH_STEPCOEFFICIENTHANDLER_HH
#define HH_STEPCOEFFICIENTHANDLER_HH

#include "ParameterHandler.hpp"
#include "StepCoefficientBase.hpp"
#include "StepCoefficientExp.hpp"
#include "StepCoefficientInvDecay.hpp"
#include "StepCoefficientArmijo.hpp"
#include <string>
#include <memory>
#include <iostream>

template<unsigned int DIM>
class StepCoefficientHandler
{
public:
    StepCoefficientHandler(const ParameterHandler<DIM> & param) : m_param(param)
    {
        if(m_param.step_coeff_method.coeff_solver == "Exponential")
            m_step_coeff_method = std::make_shared<StepCoefficientExp<DIM>>(param);
        if(m_param.step_coeff_method.coeff_solver == "InverseDecay")
            m_step_coeff_method = std::make_shared<StepCoefficientInvDecay<DIM>>(param);
        if(m_param.step_coeff_method.coeff_solver == "Armijo")
            m_step_coeff_method = std::make_shared<StepCoefficientArmijo<DIM>>(param);
    };

    const double get_alpha_k(const unsigned int k, const std::array<double, DIM>& point) const
    {
        return m_step_coeff_method->compute_alpha_k(k, point);
    }
    
    
    const ParameterHandler<DIM> m_param;
    std::shared_ptr<StepCoefficientBase<DIM>> m_step_coeff_method;

};

#endif