#include <iostream>

#include "SDL3/SDL_log.h"
#include "particle.hpp"

namespace engine {
namespace particles {

Particle::Particle(glm::dvec2 position, glm::dvec2 acceleration,
                   glm::dvec2 velocity, int lifespan)
    : position(position),
      acceleration(acceleration),
      velocity(velocity),
      lifespan(lifespan),
      forces{} {}

// Particle::Particle(const Particle& other)
//     : position(other.position),
//       acceleration(other.acceleration),
//       velocity(other.velocity),
//       lifespan(other.lifespan),
//       forces(other.forces) {
//   SDL_Log("Particle copied!\n");
// }

Particle::Particle(const Particle&& other)
    : position(other.position),
      acceleration(other.acceleration),
      velocity(other.velocity),
      lifespan(other.lifespan),
      forces(other.forces) {
  SDL_Log("Particle moved!\n");
}

void Particle::AddForce(glm::dvec2 force) { forces.push_back(force); }

void Particle::Update(double delta) {
  ApplyForces();

  position += delta * (acceleration + velocity);
  lifespan -= delta * 20;
}

bool Particle::IsAlive() const { return lifespan > 0; }

void Particle::ApplyForces() {
  // apply each force vector to the acceleration
  for (const glm::dvec2& f : forces) {
    acceleration += f;
  }
}

float Particle::GetX() const { return position.x; }

float Particle::GetY() const { return position.y; }
}  // namespace particles
}  // namespace engine
