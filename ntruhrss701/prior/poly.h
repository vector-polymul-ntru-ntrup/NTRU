#ifndef POLY_H
#define POLY_H

#include "params.h"

#include <stddef.h>
#include <stdint.h>

#define MODQ(X) ((X) & (NTRU_Q-1))
#define NTRU_N_32 704
#define NTRU_N_PAD 704

typedef struct{
  uint16_t coeffs[NTRU_N_PAD];
} poly;

void poly_mod_3_Phi_n(poly *r);
void poly_mod_q_Phi_n(poly *r);

void poly_Sq_tobytes(unsigned char *r, const poly *a);
void poly_Sq_frombytes(poly *r, const unsigned char *a);

void poly_Rq_sum_zero_tobytes(unsigned char *r, const poly *a);
void poly_Rq_sum_zero_frombytes(poly *r, const unsigned char *a);

void poly_S3_tobytes(unsigned char msg[NTRU_PACK_TRINARY_BYTES], const poly *a);
void poly_S3_frombytes(poly *r, const unsigned char msg[NTRU_PACK_TRINARY_BYTES]);

void poly_Sq_mul(poly *r, poly *a, poly *b);
void poly_Rq_mul(poly *r, poly *a, poly *b);
void poly_S3_mul(poly *r, poly *a, poly *b);
void poly_lift(poly *r, const poly *a);
void poly_lift_add(poly *ct, const poly *a);
void poly_lift_sub(poly *b, const poly *c, const poly *a);
void poly_Rq_to_S3(poly *r, const poly *a);

void poly_R2_inv(poly *r, const poly *a);
void poly_Rq_inv(poly *r, const poly *a);
void poly_S3_inv(poly *r, const poly *a);

void poly_Z3_to_Zq(poly *r);
void poly_trinary_Zq_to_Z3(poly *r);

void polyhps_mul3(poly *g);
void polyhrss_mul3(poly *g);

#endif

