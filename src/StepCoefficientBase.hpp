#ifndef HH_STEP_COEFFICIENT_BASE_HH
#define HH_STEP_COEFFICIENT_BASE_HH

class StepCoefficientBase
{
public:
    StepCoefficientBase(const double alpha_zero) : m_alpha_zero(alpha_zero) {};

    virtual ~StepCoefficientBase() = default;

    // compute the step parameter alpha_k
    virtual double compute_alpha_k(const unsigned int step, const double alpha_zero) const = 0;

protected:
    const double m_alpha_zero;
};

#endif