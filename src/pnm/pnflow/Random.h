#ifndef SRC_PNM_PNFLOW_RANDOM_H
#define SRC_PNM_PNFLOW_RANDOM_H

#include <memory>
#include <random>

namespace pnflow {

class Random {
 public:
  static void Init(unsigned int seed);

  static double Generate(std::uniform_real_distribution<double> &uniform_distribution);
  static double Generate(std::uniform_int_distribution<int> &uniform_distribution);

 private:
  static std::unique_ptr<std::default_random_engine> random_generator_;
};

}  // namespace pnflow

#endif  // SRC_PNM_PNFLOW_RANDOM_H
