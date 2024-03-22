#include<iostream>
#include<string>
#include "GetPot"
#include "ParameterHandler.hpp"
#include "MinMethodHandler.hpp"

int main()
{
  constexpr unsigned int DIM = 2; // Domain dimension (i.e. R^DIM)

  ParameterHandler<DIM> param("data.txt"); // parameters

  param.show_data();

  MinMethodHandler<DIM> min_method(param);

  std::array<double, DIM> min = min_method.get_min();

  // Print minimum
  std::cout << "The minimum is:" << std::endl;
  for(size_t i = 0; i < DIM; ++i)
    std::cout << "{" << i + 1 << "}: " << min[i] << std::endl;
  
  return 0;
}