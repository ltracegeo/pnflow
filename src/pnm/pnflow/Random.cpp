// #include "include/Random.h"
#include "Random.h"

namespace pnflow {

std::unique_ptr<std::default_random_engine> Random::random_generator_;

void Random::Init(unsigned int seed) {
  random_generator_ = std::make_unique<std::default_random_engine>(seed);
}

double Random::Generate(std::uniform_real_distribution<double> &uniform_distribution) {
  if (random_generator_) {
    return uniform_distribution(*random_generator_);
  } else {
    return 0.0;
  }
}

double Random::Generate(std::uniform_int_distribution<int> &uniform_distribution) {
  if (random_generator_) {
    return uniform_distribution(*random_generator_);
  } else {
    return 0.0;
  }
}

}  // namespace pnflow
