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
#include "MinMethodGradient.hpp"

int main()
{

  static constexpr unsigned int DIM = 2; // Domain dimension R^DIM

  ParameterHandler<DIM> p("data.txt"); // parameters

  p.show_data();

  StepCoefficientHandler<DIM> step_coeff(p);

  MinMethodGradient<DIM> min_method(p);

  std::array<double, DIM> min = min_method.compute_min();

  std::cout << "The minimum is:" << std::endl;
  for(size_t i = 0; i < DIM; ++i)
    std::cout << "[" << i + 1 << "]: " << min[i] << std::endl;
  

  return 0;
}