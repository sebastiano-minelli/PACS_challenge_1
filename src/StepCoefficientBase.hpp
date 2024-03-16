#ifndef HH_STEP_COEFFICIENT_BASE_HH
#define HH_STEP_COEFFICIENT_BASE_HH

class StepCoefficientBase
{
public:
    StepCoefficientBase(const double alpha_zero, const unsigned int DIM) : m_alpha_zero(alpha_zero), m_DIM(DIM) {};

    virtual ~StepCoefficientBase() = default;

    // compute the step parameter alpha_k
    virtual double compute_alpha_k(const unsigned int step) const = 0;

protected:
    const double m_alpha_zero;
    const unsigned int m_DIM;
};

#endif