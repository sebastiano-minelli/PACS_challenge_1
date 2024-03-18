#ifndef HH_MINMETHOD_HANDLER_HH
#define HH_MINMETHOD_HANDLER_HH

#include "ParameterHandler.hpp"
#include "StepCoefficientHandler.hpp"
#include "MinMethodBase.hpp"
#include "MinMethodGradient.hpp"
#include "MinMethodHeavyBall.hpp"
#include "MinMethodNesterov.hpp"
#include "MinMethodAdam.hpp"
#include <string>
#include <memory>
#include <iostream>

template<unsigned int DIM>
class MinMethodHandler
{
public:
    MinMethodHandler(const ParameterHandler<DIM> & param) : m_param(param)
    {
        if(m_param.min_method.solver_type == "Gradient")
            m_method_type = std::make_shared<MinMethodGradient<DIM>>(param);
        else
        {
            if(m_param.step_coeff_method.coeff_solver == "Armijo")
            {    std::cerr << "Cannot use Armijo with any method but 'Gradient'" << std::endl;
                exit(1);
            }
            if(m_param.min_method.solver_type == "HeavyBall")
                m_method_type = std::make_shared<MinMethodHeavyBall<DIM>>(param);
            if(m_param.min_method.solver_type == "Nesterov")
                m_method_type = std::make_shared<MinMethodNesterov<DIM>>(param);
            if(m_param.min_method.solver_type == "Adam")
                m_method_type = std::make_shared<MinMethodAdam<DIM>>(param);
        }
    };

    std::array<double, DIM> get_min() const
    {
        return m_method_type->compute_min();
    }
    
    
    const ParameterHandler<DIM> m_param;
    std::shared_ptr<MinMethodBase<DIM>> m_method_type;

};

#endif