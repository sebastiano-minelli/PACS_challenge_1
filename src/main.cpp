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

int main()
{

  static constexpr unsigned int DIM = 3; // Domain dimension R^DIM

  std::string fname = "data.txt";
  ParameterHandler<DIM> p(fname); // parameters

  p.show_data();
  
  std::vector<double> grad = p.compute_gradient();
  for(const auto & a : grad)
    std::cout << "Gradient " << a << std::endl;

  

  // min = compute_min(fun, grad_fun, compute_numeric_grad, toll_res, toll_var, toll_grad, max_it);
  return 0;
}