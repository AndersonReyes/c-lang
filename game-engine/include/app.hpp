#ifndef APP_HPP
#define APP_HPP

#include "component.hpp"
#include "util/results.hpp"

namespace engine {
namespace core {

/// main interface for creating engine apps/demos/games
class Application : public Component {
 public:
  Application();

  virtual Result<Empty> init() override = 0;
  virtual Result<Empty> update(double delta) override = 0;
  virtual Result<Empty> shutdown() override = 0;
};
}  // namespace core
}  // namespace engine

#endif
