#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

namespace engine {
  class Window {
    public:
      Window(int width, int height);

      /// called once on startup
      SDL_AppResult init();
      /// called on new events
      SDL_AppResult onEvent(SDL_Event *event);
      private:
        int width;
        int height;
    
  }; } // namespace engine

#endif
