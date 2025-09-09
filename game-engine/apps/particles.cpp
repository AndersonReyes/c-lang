#include <memory>
#include <vector>

#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "app.hpp"
#include "glm/ext/vector_double2.hpp"
#include "util/results.hpp"
#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "particle.hpp"
#include "particle_system.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define NUM_POINTS 500

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Uint64 last_time = 0;
static glm::dvec2 particleStart{50, 50};
static float lifespanLimit{25.0};

class RespawningParticle : public engine::particles::Particle {
 public:
  RespawningParticle()
      : engine::particles::Particle::Particle(
            particleStart, glm::dvec2(0, 0),
            glm::dvec2(SDL_randf() * 200, SDL_randf() * 100), lifespanLimit) {}

  void Update(double delta) override {
    lifespan = lifespanLimit;
    engine::particles::Particle::Update(delta);

    // restart the particle
    if (position.y >= WINDOW_HEIGHT || !IsAlive()) {
      position.x = particleStart.x;
      position.y = particleStart.y;
      acceleration.x = 0.0;
      acceleration.y = 0.0;
      lifespan = lifespanLimit;
    }
  }
};

static engine::particles::ParticleSystem particleSystem{};
static glm::dvec2 gravity(0, 0.01);

class ParticlesDemo {
 public:
  ParticlesDemo() {}

  engine::core::Result<engine::core::Empty> init() {
    /* set up the data for a bunch of points. */
    for (int i = 0; i < NUM_POINTS; i++) {
      // float x = SDL_randf() * ((float)WINDOW_WIDTH);
      // float y = SDL_randf() * ((float)WINDOW_HEIGHT);
      particleSystem.PushBack(std::make_unique<RespawningParticle>());
    }

    return engine::core::success(engine::core::empty);
  }

  engine::core::Result<engine::core::Empty> update(double delta) {
    /* let's move all our points a little for a new frame. */
    particleSystem.Update(delta);

    return engine::core::success(engine::core::empty);
  }

  engine::core::Result<engine::core::Empty> shutdown() {
    return engine::core::success(engine::core::empty);
  }

  // virtual
  engine::core::Result<engine::core::Empty> render(SDL_Renderer *renderer) {
    particleSystem.Render(renderer);
    return engine::core::success(engine::core::empty);
  }
};

static ParticlesDemo app{};

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  int i;

  SDL_SetAppMetadata("Example Renderer Points", "1.0",
                     "com.example.renderer-points");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("examples/renderer/points", WINDOW_WIDTH,
                                   WINDOW_HEIGHT, 0, &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!app.init()) {
    SDL_Log("failed to init app");
    return SDL_APP_FAILURE;
  }

  last_time = SDL_GetTicks();

  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs.
 */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS; /* end the program, reporting success to the OS.
                             */
  }
  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
  const Uint64 now = SDL_GetTicks();
  const float elapsed =
      ((float)(now - last_time)) / 1000.0f; /* seconds since last iteration */
  int i;

  if (!app.update(elapsed)) {
    SDL_Log("failed to update app");
    return SDL_APP_FAILURE;
  }
  last_time = now;

  /* as you can see from this, rendering draws over whatever was drawn before
   * it. */
  SDL_SetRenderDrawColor(renderer, 0, 0, 0,
                         SDL_ALPHA_OPAQUE); /* black, full alpha */
  SDL_RenderClear(renderer);                /* start with a blank canvas. */
  SDL_SetRenderDrawColor(renderer, 255, 255, 255,
                         SDL_ALPHA_OPAQUE); /* white, full alpha */

  /* You can also draw single points with SDL_RenderPoint(), but it's
     cheaper (sometimes significantly so) to do them all at once. */
  if (!app.render(renderer)) {
    SDL_Log("failed to render app");
    return SDL_APP_FAILURE;
  }

  SDL_RenderPresent(renderer); /* put it all on the screen! */

  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  /* SDL will clean up the window/renderer for us. */
  if (!app.shutdown()) {
    SDL_Log("failed to shutdown app");
  }
}
