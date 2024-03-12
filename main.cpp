#include<iostream>
#include<functional>
#include<string>
#include<vector>
// #include<Eigen>

int main()
{
    typedef double domain_type; //type of the domain
    typedef double codomain_type; //type of the codomain

    std::vector<domain_type> vectors;

    unsigned int n = 0; // dimension of the domain
    double min = 0.0; // minimum
    double toll_res = 0.0; // tolerance for the residual
    double toll_var = 0.0; // tolerance for the variation
    double toll_grad = 0.0; // tolerance for the gradient
    double max_it = 0.0; // maximum number of iterations
    std::string min_method; // method to use to compute the minimum
    std::string step_method; // method to use to compute the step coefficient

    bool compute_numeric_grad = false; // choice to compute gradient numerically instead of providing it directly
    std::function<codomain_type(std::vector<domain_type>)> fun; // function
    std::function<std::vector<codomain_type>(std::vector<domain_type>)> grad_fun; // function gradient

    while(std::cout << "Insert the dimension of the domain (i.e. the number of variables) " << std::endl && !(std::cin >> n))
    {
        std::cin.clear();
        std::cout << "Wrong value provided" << std::endl;
    }


    ///// implementing a function to read user parameters ////

   

    // min = compute_min(fun, grad_fun, compute_numeric_grad, toll_res, toll_var, toll_grad, max_it);

    std::cout << "The minimum is: " << min << std::endl;

    return 0;
}