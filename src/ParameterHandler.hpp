#ifndef HH_PARAMETER_HANDLER_HH
#define HH_PARAMETER_HANDLER_HH

#include "Parameters.hpp"
#include<vector>
#include<array>

template<unsigned int DIM>
class ParameterHandler : public Parameters<DIM>
{
public:
    ParameterHandler(const std::string &filename) :
        Parameters<DIM>(filename),
        m_dfun_num(0.0),
        m_min(0.0)
    {};

    // function that handles automatically the analytic or numeric gradient
    std::vector<double> compute_gradient()
    {
        std::vector<double> dfun_eval(DIM, 0.0);
        
        if(!this->coefficients.compute_num_grad)
        {
            for(size_t i = 0; i < DIM; ++i)
                dfun_eval[i] = this->function_param.dfun[i](this->function_param.x);
        }else
        {
            for(size_t i = 0; i < DIM; ++i)
            {
                std::array<double, DIM> x_plus = this->function_param.x;
                std::array<double, DIM> x_minus = this->function_param.x;
                x_plus[i] += this->coefficients.h;
                x_minus[i] -= this->coefficients.h;
                dfun_eval[i] = (this->function_param.fun(x_plus) - this->function_param.fun(x_minus)) /  (2 * this->coefficients.h);
            }
        }
        return dfun_eval;
    };

    void show_data() const
    {
        std::cout << "SELECTED OPTIONS" << std::endl;
        std::cout << "- Function:                     " << this->function_param.funString << std::endl;
        if(!this->coefficients.compute_num_grad)
        {
            std::cout << "- Gradient of the function:     [1]: " << this->function_param.dfunString[0] << std::endl;
            for(size_t i = 1; i < DIM; ++i)
                std::cout<< "                                [" << i + 1 << "]: " << this->function_param.dfunString[i] << std::endl;
        }else
        {
            std::cout << "- Gradient of the function:     none" << std::endl;
        }
        std::cout << "- Initial point:                [1]: " << this->function_param.x[0] << std::endl;
        for(size_t i = 1; i < DIM; ++i)
        std::cout<< "                                [" << i + 1 << "]: " << this->function_param.x[i] << std::endl;
        std::cout << "- Maximum n. of iterations:     " << this->coefficients.max_it << std::endl;
        std::cout << "- Residue tolerance:            " << this->coefficients.tol_res << std::endl;
        std::cout << "- Argument tolerance:           " << this->coefficients.tol_x << std::endl;
        std::cout << "- Compute numeric gradient:     " << this->coefficients.compute_num_grad << std::endl;
        std::cout << "- Finite difference increment:  " << this->coefficients.h << std::endl;
        std::cout << "- Solver type:                  '" << this->min_method.solver_type << "'" << std::endl;
        std::cout << "- Step coefficient method:      '" << this->step_coeff_method.coeff_solver << "'" << std::endl;
    };

private:
    double m_dfun_num; // numeric function gradient
    double m_min;
};



#endif