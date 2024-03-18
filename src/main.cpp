#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include "muParserXInterface.hpp"
#include "GetPot"
#include "ParameterHandler.hpp"
#include "StepCoefficientHandler.hpp"
#include "MinMethodGradient.hpp"

int main()
{

  static constexpr unsigned int DIM = 2; // Domain dimension R^DIM

  ParameterHandler<DIM> param("data.txt"); // parameters


  double a = -9;
  double b = 5;

  std::cout << "val abs: " << abs(a - b) << std::endl;
  param.show_data();

  MinMethodGradient<DIM> min_method(param);

  std::array<double, DIM> min = min_method.compute_min();

  std::cout << "The minimum is:" << std::endl;
  for(size_t i = 0; i < DIM; ++i)
    std::cout << "{" << i + 1 << "}: " << min[i] << std::endl;
  
  return 0;
}