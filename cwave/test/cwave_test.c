#include "cwave.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

void test_wave_init(void) {
  struct WaveForm wave;
  double data[] = {1.5, 3.6, 3.7};
  double time[] = {1.0, 2.0, 3.0};

  wave_init(&wave, data, 3, time, cos);
  assert(wave.num_samples == 3);
}
