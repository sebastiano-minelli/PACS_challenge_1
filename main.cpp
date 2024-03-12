#include<iostream>
#include<functional>
#include<string>
#include<Eigen>

int main()
{
    using double domain_type; //type of the domain
    using double codomain_type; //type of the codomain

    unknowns = std::vector<domain_type>;

    double min = 0.0; // minimum
    double toll_res; // tolerance for the residual
    double toll_var; // tolerance for the variation
    double toll_grad; // tolerance for the gradient
    double max_it; // maximum number of iterations
    std::string min_method; // method to use to compute the minimum
    std::string step_method; // method to use to compute the step coefficient

    bool compute_numeric_grad; // choice to compute gradient numerically instead of providing it directly
    std::function<codomain_type(std::vector<domain_type>)> fun; // function
    std::function<std::vector<codomain_type>(std::vector<domain_type>)> grad_fun; // function gradient

    ///// implementing a function to read user parameters ////

   

    min = compute_min(fun, grad_fun, compute_numeric_grad, toll_res, toll_var, toll_grad, max_it);

    std::cout << "The minimum is: " << min << std::endl;

    return 0;
}