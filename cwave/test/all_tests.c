
#include <stdio.h>

void test_wave_init(void);


typedef void (*fn) (void);

void runner(const char* name, fn func, const char* file) {
    func();

    printf("%s:%s PASSED\n", file, name);
}

int main(void) {

    printf("\n======== RUNNING TESTS ========\n");

    runner("test_wave_init", test_wave_init, "cwave_test.c");

    return 0;
}
