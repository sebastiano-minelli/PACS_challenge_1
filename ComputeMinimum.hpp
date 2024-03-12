#ifndef COMPUTE_MINIMUM_H
#define COMPUTE_MINIMUM_H

#include <cmath>
#include <functional>
#include <iostream>
#include <limits>

class ComputeMinimum
{
public:
  ComputeMinimum(const std::function<double(const double &)> &fun_,
                const std::function<double(const double &)> &grad_fun_,
                const unsigned int                           max_it_ = 100,
                const double tol_res_ = std::numeric_limits<double>::epsilon() *
                                        1000.0,
                const double tol_var_ = std::numeric_limits<double>::epsilon() *
                                      1000.0,
                const double tol_grad_ = std::numeric_limits<double>::epsilon() *
                                      1000.0,
                const bool compute_numeric_grad_ = false,
                const std::string min_method_ = "GradientMethod",
                const std::string step_method_ = "ExponentialDecay"):
    m_fun(fun_),
    m_grad_fun(grad_fun_),
    m_max_it(max_it_),
    m_tol_res(tol_res_),
    m_tol_var(tol_var_),
    m_tol_grad(tol_grad_),
    m_compute_numeric_grad(compute_numeric_grad_),
    m_min_method(min_method_),
    m_step_method(step_method_)
  {}

  void
  solve(const double &x0)
  {
    m_x = x0;
    for (m_iter = 0; m_iter < m_n_max_it; ++m_iter)
      {
        m_res = m_fun(m_x);

        if (std::abs(m_res) < m_tol_fun)
          break;

        m_df_dx = m_dfun(m_x);

        m_dx = -m_res / m_df_dx;
        m_x += m_dx;

        if (std::abs(m_dx) < m_tol_x)
          break;
      }
  }

  double
  get_result() const
  {
    return m_x;
  };

  double
  get_residual() const
  {
    return m_res;
  };

  unsigned int
  get_iter() const
  {
    return m_iter;
  };

private:
    std::function<double(const double &)> m_fun; // function
    std::function<double(const double &)> m_grad_fun; // function gradient
    const unsigned int  m_max_it; // maximum number of iterations
    const double        m_tol_res; // residual tolerance
    const double        m_tol_var; // value tolerance
    const double        m_tol_grad; // gradient tolerance
    const bool          m_compute_numeric_grad; // true = compute the gradient numerically
    const std::string   m_min_method; // method to compute the minimization
    const std::string   m_step_method; // method to compute the minimization coefficient at every step


};

#endif /* NEWTON_H */
