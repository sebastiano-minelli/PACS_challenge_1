// function that computes the minimum 
#include<iostream>
#include<functional>
#include<string>
#include<vector>

double compute_min(std::function<double(std::vector<double>)> fun, 
                    std::function<std::vector<double>(std::vector<double>)> grad_fun, 
                    bool compute_numeric_grad, 
                    double toll_res, 
                    double toll_var, 
                    double toll_grad, 
                    double max_it,
                    std::string min_method,
                    std::string step_method)
{
    

}