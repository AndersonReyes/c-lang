#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "util/results.hpp"

namespace engine {
namespace core {

/// interface that represents an engine component
class Component {
 public:
  virtual Result<Empty> init() = 0;
  virtual Result<Empty> update(double delta) = 0;
  virtual Result<Empty> shutdown() = 0;

  virtual ~Component() {};
};
}  // namespace core
}  // namespace engine

#endif
