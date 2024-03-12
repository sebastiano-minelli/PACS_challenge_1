// function that computes the minimum 
#include<iostream>
#include<functional>
#include<string>
#include<vector>

using double domain_type;
using double codomain_type;

double compute_min(std::function<codomain_type(std::vector<domain_type>)> fun, 
                    std::function<std::vector<codomain_type>(std::vector<domain_type>)> grad_fun, 
                    bool compute_numeric_grad, 
                    double toll_res, 
                    double toll_var, 
                    double toll_grad, 
                    double max_it,
                    std::string min_method,
                    std::string step_method)
{

}