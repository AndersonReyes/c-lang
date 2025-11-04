#include "cwave.h"

void wave_init(struct WaveForm* dest, double* samples, size_t num_samples,
               double* timestamps, WaveFn fn) {
  dest->timestamps = timestamps;
  dest->samples = samples;
  dest->num_samples = num_samples;
  dest->fn = fn;
}

double wave_start(struct WaveForm* dest) { return dest->timestamps[0]; }

void wave_cos(struct WaveForm* dest, float frequency, float amplitude,
              float offset) {}
