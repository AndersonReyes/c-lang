#ifndef PARTICLE_SYSTEM_HPP
#define PARTICLE_SYSTEM_HPP

#include <memory>

#include "particle.hpp"

namespace engine {
namespace particles {

class ParticleSystem {
 public:
  ParticleSystem();
  virtual ~ParticleSystem();
  void PushBack(std::unique_ptr<Particle> particle);
  void Update(double delta);
  void Render(SDL_Renderer *renderer);

 private:
  std::vector<std::unique_ptr<Particle>> particles;
};

}  // namespace particles
}  // namespace engine
#endif
