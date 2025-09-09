#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <vector>

#include "glm/ext/vector_double2.hpp"

namespace engine {
namespace particles {

class Particle {
 public:
  Particle(glm::dvec2 position, glm::dvec2 acceleration, glm::dvec2 velocity,
           int lifespan);

  Particle(const Particle& other) = delete;
  Particle(const Particle&& other);

  virtual void Update(double delta);
  virtual ~Particle() {}

  void AddForce(glm::dvec2 force);
  bool IsAlive() const;
  float GetX() const;
  float GetY() const;

 protected:
  glm::dvec2 position;
  glm::dvec2 acceleration;
  glm::dvec2 velocity;
  float lifespan;
  std::vector<glm::dvec2> forces;

  void ApplyForces();
};

}  // namespace particles
}  // namespace engine

#endif
