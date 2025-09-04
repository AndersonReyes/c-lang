#include <array>

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "particle_system.hpp"

namespace engine {
namespace particles {

ParticleSystem::ParticleSystem() : particles() {}

ParticleSystem::~ParticleSystem() {
  for (Particle *p : particles) {
    delete p;
  }
  particles.clear();
}

void ParticleSystem::PushBack(Particle *particle) {
  particles.push_back(particle);
}
void ParticleSystem::Update(double delta) {
  for (Particle *p : particles) {
    if (p->IsAlive()) p->Update(delta);
  }
}

void ParticleSystem::Render(SDL_Renderer *renderer) {
  // TODO: can be more efficient here instead of creating a new vector each
  // render call?
  std::vector<SDL_FPoint> sdlPoints;
  sdlPoints.reserve(particles.size());

  for (Particle *p : particles) {
    if (p->IsAlive()) sdlPoints.push_back(SDL_FPoint{p->GetX(), p->GetY()});
  }

  SDL_RenderPoints(renderer, sdlPoints.data(), sdlPoints.size());

  sdlPoints.clear();
}

}  // namespace particles
}  // namespace engine
