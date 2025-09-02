// #include "hello.hpp"
//
//
// int main() {
//   print_hello();
//   return 0;}

#include <array>
#include <vector>

#include "SDL3/SDL_rect.h"
#include "glm/ext/vector_float2.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/simd/platform.h"
#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Uint64 last_time = 0;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define NUM_POINTS 500
#define MIN_PIXELS_PER_SECOND \
  30 /* move at least this many pixels per second. */
#define MAX_PIXELS_PER_SECOND                     \
  60 /* move this many pixels per second at most. \
      */
namespace engine {
namespace particles {

/// interface for a particle
class Particle {
 public:
  Particle(glm::vec2 position, glm::vec2 acceleration, glm::vec2 velocity,
           int lifespan)
      : position(position),
        acceleration(acceleration),
        velocity(velocity),
        lifespan(255) {}

  void Update(double delta) {}

  SDL_FPoint GetPoint() { return point; }

 protected:
  glm::vec2 position;
  glm::vec2 acceleration;
  glm::vec2 velocity;
  SDL_FPoint point;
  int lifespan;
};

/// interface for a particle
class ParticleSystem {
 public:
  ParticleSystem(glm::vec2 acceleration, glm::vec2 initialVelocity,
                 int lifespan)
      : acceleration(acceleration),
        initialVelocity(initialVelocity),
        lifespan(255),
        particles() {}

  void PushBack(SDL_FPoint point) { particles.push_back(point); }
  void Update(double delta) {
    // points[i].x += distance;
    // points[i].y += distance;
    // if ((points[i].x >= WINDOW_WIDTH) || (points[i].y >= WINDOW_HEIGHT)) {
    ///* off the screen; restart it elsewhere! */
    // if (SDL_rand(2)) {
    // points[i].x = SDL_randf() * ((float)WINDOW_WIDTH);
    // points[i].y = 0.0f;
    //} else {
    // points[i].x = 0.0f;
    // points[i].y = SDL_randf() * ((float)WINDOW_HEIGHT);
    //}
    // point_speeds[i] =
    // MIN_PIXELS_PER_SECOND +
    //(SDL_randf() * (MAX_PIXELS_PER_SECOND - MIN_PIXELS_PER_SECOND));
    //}

    for (SDL_FPoint &point : particles) {
      glm::vec2 a = acceleration + initialVelocity;
      point.x += a.x * delta;
      point.y += a.y * delta;

      if (point.x >= WINDOW_WIDTH) {
        point.x = 0;
      }

      if (point.y >= WINDOW_HEIGHT) {
        point.y = 0;
      }
    }
  }

  SDL_FPoint *Data() { return particles.data(); }
  size_t NumParticles() { return particles.size(); }

 protected:
  glm::vec2 acceleration;
  glm::vec2 initialVelocity;
  std::vector<SDL_FPoint> particles;
  int lifespan;
};

}  // namespace particles
}  // namespace engine

static std::vector<engine::particles::Particle> particles{};
static engine::particles::ParticleSystem particleSystem{glm::vec2(1, 1),
                                                        glm::vec2(0, 0), 255};

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  particles.reserve(NUM_POINTS);

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

  /* set up the data for a bunch of points. */
  for (i = 0; i < NUM_POINTS; i++) {
    float x = SDL_randf() * ((float)WINDOW_WIDTH);
    float y = SDL_randf() * ((float)WINDOW_HEIGHT);
    particleSystem.PushBack(SDL_FPoint{x, y});
  }

  last_time = SDL_GetTicks();

  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
  }
  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
  const Uint64 now = SDL_GetTicks();
  const float elapsed =
      ((float)(now - last_time)) / 1000.0f; /* seconds since last iteration */
  int i;

  /* let's move all our points a little for a new frame. */
  particleSystem.Update(elapsed);

  last_time = now;

  /* as you can see from this, rendering draws over whatever was drawn before
   * it. */
  SDL_SetRenderDrawColor(renderer, 0, 0, 0,
                         SDL_ALPHA_OPAQUE); /* black, full alpha */
  SDL_RenderClear(renderer);                /* start with a blank canvas. */
  SDL_SetRenderDrawColor(renderer, 255, 255, 255,
                         SDL_ALPHA_OPAQUE); /* white, full alpha */
  SDL_RenderPoints(renderer, particleSystem.Data(),
                   particleSystem.NumParticles()); /* draw all the points! */

  /* You can also draw single points with SDL_RenderPoint(), but it's
     cheaper (sometimes significantly so) to do them all at once. */

  SDL_RenderPresent(renderer); /* put it all on the screen! */

  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  /* SDL will clean up the window/renderer for us. */
}
