#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<iomanip>
#include<memory>
#include "GetPot"
#include "muParserXInterface.hpp"
#include "StepCoefficientBase.hpp"
#include "StepCoefficientInvDecay.hpp"
#include "StepCoefficientExp.hpp"
#include "StepCoefficientArmijo.hpp"

int main(int argc, char **argv)
{
  using namespace MuParserInterface;

  static constexpr unsigned int DIM = 3; // Domain dimension R^DIM

  // bool compute_numeric_grad = false; // choice to compute gradient numerically instead of providing it directly

  // GetPot reads from file
  GetPot datafile("data.txt");
  std::string section = "Parameters/";

  const unsigned int max_it = datafile((section + "max_it").data(), 50); // Maximum numebr of iterations
  const double tol_res = datafile((section + "tol_res").data(), 1.0e-3); // tolerance for the variation on the codomain
  const double tol_x = datafile((section + "tol_x").data(), 1.0e-3); // tolerance for the variation on the domain

  section = "Functions/";
  std::string funString = datafile((section + "fun").data(), " "); // function
  std::vector<std::string> dfunString(DIM, " "); // gradient of the function
  for(size_t i = 0; i < DIM; ++i)
  {
    // evaluate the right term of the gradient vector
    std::string scalar_place = std::to_string(i + 1);
    dfunString[i] = datafile((section + "grad_fun_" + scalar_place).data(), " "); // function derivative
  }

  

  section = "Solver_Type/";
  std::string solver_type = datafile((section + "solver_type").data(), "GradientMethod"); // Solver choice

  section = "Compute_Coefficient_Method/";
  std::string coeff_solver = datafile((section + "coeff_solver").data(), "Exponential"); // Step coefficient choice


  // Creating muParserX function and respective gradient
  muParserXInterface<DIM> fun(funString);

  std::vector<muParserXInterface<DIM>> dfun;
  for(size_t i = 0; i < DIM; ++i)
  {
    dfun.emplace_back(dfunString[i]);
  }
  

  // recall that to evaluate expression I have to pass std::array<double, DIM> x;

  // Ouput read options
  std::cout << "SELECTED OPTIONS" << std::endl;
  std::cout << "- Function:                  " << funString << std::endl;
  std::cout << "- Gradient of the function:  [1]: " << dfunString[0] << std::endl;
  for(size_t i = 1; i < DIM; ++i)
    std::cout<< "                             [" << i + 1 << "]: " << dfunString[i] << std::endl;

  std::cout << "- Maximum n. of iterations:  " << max_it << std::endl;
  std::cout << "- Residue tolerance:         " << tol_res << std::endl;
  std::cout << "- Argument tolerance:        " << tol_x << std::endl;
  std::cout << "- Solver type:               '" << solver_type << "'" << std::endl;
  std::cout << "- Step coefficient method:   '" << coeff_solver << "'" << std::endl;

  double alpha_zero = 0.00000000001;
  double mu = 0.5;
  std::array<double, DIM> x = {1, 2, 3};
  std::unique_ptr<StepCoefficientBase<DIM>> step_coeff = std::make_unique<StepCoefficientArmijo<DIM>>(alpha_zero, mu, x, fun, dfun);
  double alpha_k = step_coeff->compute_alpha_k(10);
  std::cout << "Alpha_k: " << alpha_k << std::endl;



  // min = compute_min(fun, grad_fun, compute_numeric_grad, toll_res, toll_var, toll_grad, max_it);
  return 0;
}