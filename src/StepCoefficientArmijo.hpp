#ifndef HH_STEP_COEFFICIENT_INV_DECAY_HH
#define HH_STEP_COEFFICIENT_INV_DECAY_HH


#include<cmath>
#include<vector>
#include "StepCoefficientBase.hpp"
#include "muParserXInterface.hpp"

class StepCoefficientArmijo : public StepCoefficientBase
{
public:
    StepCoefficientArmijo(const double alpha_zero, 
                         const unsigned int DIM,
                         const double sigma = 0.3, 
                         const std::array<double, DIM> x
                         const muParserXInterface<DIM> fun = " ",
                         const std::vector<muParserXInterface<DIM>> dfun = " ") : 

    StepCoefficientBase(alpha_zero, DIM), 
    m_sigma(sigma),
    m_fun(fun),
    m_dfun(dfun),
    m_x(x) 
    {};

    double compute_alpha_k(const unsigned int step) const override;

private:
    const double m_sigma;
    const MuParserInterface<DIM> m_fun;
    const std::vector<MuParserInterface<DIM>> m_dfun;
    const std::array<double, DIM> m_x;

};

#endif