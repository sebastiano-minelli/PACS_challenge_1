#include "StepCoefficientArmijo.hpp"
#include<array>

template <unsigned int DIM>
double StepCoefficientArmijo<DIM>::compute_alpha_k(const unsigned int step) const
{
    double alpha_k = 2.0 * this->m_alpha_zero;

    // compute argouments
    std::array<double, DIM> y;
    double L2norm = 0.0;
    do
    {   
        alpha_k = alpha_k / 2.0;
        for(size_t i = 0; i < DIM; ++i)
        {
            y[i] = m_x[i] - alpha_k * m_dfun[i](m_x);
            L2norm += m_dfun[i](m_x) * m_dfun[i](m_x);
        }

    }while(abs(m_fun(m_x) - m_fun(y)) < m_sigma * alpha_k * L2norm);

    return alpha_k;
    
}