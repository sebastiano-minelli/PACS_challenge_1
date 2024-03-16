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

    double compute_alpha_k(const unsigned int step) const override;

private:
    const double m_sigma;
    const MuParserInterface::muParserXInterface<DIM> m_fun;
    const std::vector<MuParserInterface::muParserXInterface<DIM>> m_dfun;
    const std::array<double, DIM> m_x;

};

#endif