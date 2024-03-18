#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<memory>
#include "GetPot"
#include "ParameterHandler.hpp"
#include "muParserXInterface.hpp"
#include "StepCoefficientBase.hpp"
#include "StepCoefficientInvDecay.hpp"
#include "StepCoefficientExp.hpp"
#include "StepCoefficientArmijo.hpp"
#include "StepCoefficientHandler.hpp"

int main()
{

  static constexpr unsigned int DIM = 3; // Domain dimension R^DIM

  ParameterHandler<DIM> p("data.txt"); // parameters
  StepCoefficientHandler<DIM> step_coeff(p);

  p.show_data();

  std::shared_ptr pointer = step_coeff.get_step_method();
  double alpha_k = pointer->compute_alpha_k(10);
  std::cout << "Alpha k " << alpha_k << std::endl;
  


  std::vector<double> grad = p.compute_gradient();
  for(const auto & a : grad)
    std::cout << "Gradient " << a << std::endl;

  

  // min = compute_min(fun, grad_fun, compute_numeric_grad, toll_res, toll_var, toll_grad, max_it);
  return 0;
}