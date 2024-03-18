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
    StepCoefficientHandler(ParameterHandler<DIM> & param) : m_param(param)
    {
        if(m_param.step_coeff_method.coeff_solver == "Exponential")
            step_coeff_method = std::make_shared<StepCoefficientExp<DIM>>(param);
        if(m_param.step_coeff_method.coeff_solver == "InverseDecay")
            step_coeff_method = std::make_shared<StepCoefficientInvDecay<DIM>>(param);
        if(m_param.step_coeff_method.coeff_solver == "Armijo")
            step_coeff_method = std::make_shared<StepCoefficientArmijo<DIM>>(param);
    };

    const double get_alpha_k(const unsigned int k) const
    {
        return step_coeff_method->compute_alpha_k(k);
    }
    
private:
    ParameterHandler<DIM> m_param;
    std::shared_ptr<StepCoefficientBase<DIM>> step_coeff_method;

};

#endif