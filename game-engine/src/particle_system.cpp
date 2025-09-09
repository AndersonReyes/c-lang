#include <array>
#include <memory>

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "particle_system.hpp"

namespace engine {
namespace particles {

ParticleSystem::ParticleSystem() : particles() { particles.reserve(500); }

ParticleSystem::~ParticleSystem() { particles.clear(); }

void ParticleSystem::PushBack(std::unique_ptr<Particle> particle) {
  particles.push_back(std::move(particle));
}
void ParticleSystem::Update(double delta) {
  for (auto &p : particles) {
    if (p->IsAlive()) p->Update(delta);
  }
}

void ParticleSystem::Render(SDL_Renderer *renderer) {
  // TODO: can be more efficient here instead of creating a new vector each
  // render call?
  std::vector<SDL_FPoint> sdlPoints;
  sdlPoints.reserve(particles.size());

  for (auto &p : particles) {
    if (p->IsAlive()) sdlPoints.push_back(SDL_FPoint{p->GetX(), p->GetY()});
  }

  SDL_RenderPoints(renderer, sdlPoints.data(), sdlPoints.size());

  sdlPoints.clear();
}

}  // namespace particles
}  // namespace engine
