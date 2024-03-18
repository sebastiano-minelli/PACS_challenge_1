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

    const std::shared_ptr<StepCoefficientBase<DIM>> get_step_method() const
    {
        std::cout << "Selected method " << m_param.step_coeff_method.coeff_solver << std::endl;
        return step_coeff_method;
    }
    
private:
    ParameterHandler<DIM> m_param;
    std::shared_ptr<StepCoefficientBase<DIM>> step_coeff_method;

};

#endif