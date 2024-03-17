#ifndef HH_STEP_COEFFICIENT_ARMIJO_HH
#define HH_STEP_COEFFICIENT_ARMIJO_HH


#include<cmath>
#include<vector>
#include<array>
#include "muParserXInterface.hpp"
#include "StepCoefficientBase.hpp"

template <unsigned int DIM>
class StepCoefficientArmijo : public StepCoefficientBase<DIM>
{
public:
    StepCoefficientArmijo(const double alpha_zero,
                         const double sigma = 0.3, 
                         const std::array<double, DIM> x = {},
                         const MuParserInterface::muParserXInterface<DIM> fun = " ",
                         const std::vector<MuParserInterface::muParserXInterface<DIM>> dfun = " ") : 

    StepCoefficientBase<DIM>(alpha_zero), 
    m_sigma(sigma),
    m_fun(fun),
    m_dfun(dfun),
    m_x(x) 
    {};

    double compute_alpha_k(const unsigned int step) const override
    {
        const unsigned int n_max_it = 10000; // maximum number of iterations
        unsigned int it = 0; // iterations
        const double min_tol = std::numeric_limits<double>::epsilon() * 100.0; // minimum tolerance


        double alpha_k = 2.0 * this->m_alpha_zero;

        // compute argouments
        std::array<double, DIM> y;

        double L2norm = 0.0;
        for(size_t i = 0; i < DIM; ++i)
            L2norm += m_dfun[i](m_x) * m_dfun[i](m_x);

        do
        {   
            alpha_k = alpha_k * 0.5;
            for(size_t i = 0; i < DIM; ++i)
                y[i] = m_x[i] - alpha_k * m_dfun[i](m_x);

        }while(m_fun(m_x) - m_fun(y) >= m_sigma * alpha_k * L2norm
                && it++ < n_max_it
                && alpha_k > min_tol );

        return alpha_k;
    
    };

private:
    const double m_sigma;
    const MuParserInterface::muParserXInterface<DIM> m_fun;
    const std::vector<MuParserInterface::muParserXInterface<DIM>> m_dfun;
    const std::array<double, DIM> m_x;

};

#endif