#ifndef CWAVE_H
#define CWAVE_H

#include <stddef.h>

typedef double (*WaveFn)(double);

struct WaveForm {
  double* samples;
  size_t num_samples;
  double* timestamps;
  WaveFn fn;
};

void wave_init(struct WaveForm* dest, double* samples, size_t num_samples,
               double* timestamps, WaveFn fn);

double wave_start(struct WaveForm* dest);

/** make a sin-like waveform */
void wave_sinusoid(struct WaveForm* dest, WaveFn fn);

/** make a consine waveform
 *
 * @param dest the destination object
 * @param frequency the frequency of wave
 * @param amplitude the amplitude
 * @param offset the phase in radians.
 * */
void wave_cos(struct WaveForm* dest, float frequency, float amplitude,
              float offset);

/** make a sin waveform
 *
 * @param dest the destination object
 * @param frequency the frequency of wave
 * @param amplitude the amplitude
 * @param offset the phase in radians.
 * */
void wave_sin(struct WaveForm* dest, float frequency, float amplitude,
              float offset);

#endif
