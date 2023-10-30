

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "api.h"
#include "params.h"
#include "poly.h"
#include "tmvp.h"
#include "batch_multiplication.h"

#define NTESTS 1000

uint64_t time0, time1;
uint64_t cycles[NTESTS];

#ifdef __APPLE__

#include "m1cycles.h"
#define __AVERAGE__
#define SETUP_COUNTER() {(void)cycles; setup_rdtsc();}
#define CYCLE_TYPE "%lld"
#define GET_TIME rdtsc()

#else

#include "hal.h"
#undef __AVERAGE__
#define __MEDIAN__
#define SETUP_COUNTER() {}
#define CYCLE_TYPE "%ld"
#define GET_TIME hal_get_time()


static int cmp_uint64(const void *a, const void *b){
    return ((*((const uint64_t*)a)) - ((*((const uint64_t*)b))));
}

#endif

#ifdef __AVERAGE__

#define LOOP_INIT(__clock0, __clock1) { \
    __clock0 = GET_TIME; \
}
#define LOOP_TAIL(__f_string, records, __clock0, __clock1) { \
    __clock1 = GET_TIME; \
    printf(__f_string, (__clock1 - __clock0) / NTESTS); \
}
#define BODY_INIT(__clock0, __clock1) {}
#define BODY_TAIL(records, __clock0, __clock1) {}

#elif defined(__MEDIAN__)

#define LOOP_INIT(__clock0, __clock1) {}
#define LOOP_TAIL(__f_string, records, __clock0, __clock1) { \
    qsort(records, sizeof(uint64_t), NTESTS, cmp_uint64); \
    printf(__f_string, records[NTESTS >> 1]); \
}
#define BODY_INIT(__clock0, __clock1) { \
    __clock0 = GET_TIME; \
}
#define BODY_TAIL(records, __clock0, __clock1) { \
    __clock1 = GET_TIME; \
    records[i] = __clock1 - __clock0; \
}

#endif

#define WRAP_FUNC(__f_string, records, __clock0, __clock1, func){ \
    LOOP_INIT(__clock0, __clock1); \
    for(size_t i = 0; i < NTESTS; i++){ \
        BODY_INIT(__clock0, __clock1); \
        func; \
        BODY_TAIL(records, __clock0, __clock1); \
    } \
    LOOP_TAIL(__f_string, records, __clock0, __clock1); \
}



int main()
{


    SETUP_COUNTER();

    poly src1, src2;
    poly des;

    uint16_t tmp[SB0 * 9 * 3]; // SB0 = 144


    uint16_t *toepa = &tmp[0 * SB0]; /* nine 144*144 toeplitz matrix, needs nine length-288 vectors to store */
    uint16_t *kbw   = &tmp[18* SB0]; /* nine 144*144 vectors*/

    WRAP_FUNC("polymul (Z_q[x] / (x^701 - 1)): " CYCLE_TYPE " \n",
            cycles, time0, time1,
            poly_Rq_mul(&(des), &(src1), &(src2)));

    WRAP_FUNC("(TC5^{-1})^*: " CYCLE_TYPE " \n",
            cycles, time0, time1,
            ittc5(toepa, &(src1.coeffs[0])));

    WRAP_FUNC("TC5: " CYCLE_TYPE " \n",
            cycles, time0, time1,
            tc5(kbw, &(src2.coeffs[0])));

    WRAP_FUNC("TMVP 144: " CYCLE_TYPE " \n",
            cycles, time0, time1,
            tmvp_144_ka33_ka2(&kbw[0], &toepa[0]));

    WRAP_FUNC("TC5^*: " CYCLE_TYPE " \n",
            cycles, time0, time1,
            ttc5(&(des.coeffs[0]), kbw));




  return 0;

}









