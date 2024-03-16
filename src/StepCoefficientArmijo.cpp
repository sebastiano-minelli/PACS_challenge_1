#include "StepCoefficientArmijo.hpp"
#include<array>

double StepCoefficientArmijo::compute_alpha_k(const unsigned int step) const override
{
    double alpha_k = 2.0 * m_alpha_zero;

    // compute argouments
    std::array<double, m_DIM> y;
    double L2norm = 0.0;
    do
    {   
        alpha_k = alpha_k / 2.0;
        for(size_t i = 0; i < m_DIM; ++i)
        {
            y[i] = x[i] - alpha_k * m_dfun[i](x);
            L2norm += m_dfun[i](x) * m_dfun[i](x);
        }

    }while(abs(m_fun(x) - m_fun(y)) < sigma * alpha_k * L2norm);

    return alpha_k;
    
}