CC ?= /usr/bin/cc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
          -Wshadow -Wpointer-arith -fomit-frame-pointer -mtune=native -O3
NISTFLAGS += -Wno-unused-result -mpopcnt -maes \
             -mtune=native -O3 -fomit-frame-pointer
RM = /bin/rm

HASH_PATH = ../../hash
HASH_HEADERS = $(HASH_PATH)/fips202.h $(HASH_PATH)/sha2.h
HASH_SOURCES = $(HASH_PATH)/fips202.c $(HASH_PATH)/sha2.c

SORT_PATH = .
SORT_HEADERS =
SORT_SOURCES =

RAND_PATH = ../../randombytes
RAND_HEADERS = $(RAND_PATH)/randombytes.h $(RAND_PATH)/rng.h $(RAND_PATH)/chacha20.h
RAND_SOURCES = $(RAND_PATH)/randombytes.c $(RAND_PATH)/rng.c $(RAND_PATH)/chacha20.c

CFLAGS += -I$(HASH_PATH) -I$(SORT_PATH) -I$(RAND_PATH)

CYCLES_PATH = ../../cycles
M1_CYCLES_HEADERS = $(CYCLES_PATH)/m1cycles.h
M1_CYCLES_SOURCES = $(CYCLES_PATH)/m1cycles.c
A72_CYCLES_HEADERS = $(CYCLES_PATH)/hal.h
A72_CYCLES_SOURCES = $(CYCLES_PATH)/hal.c
CYCLES_HEADERS = $(M1_CYCLES_HEADERS) $(A72_CYCLES_HEADERS)
CYCLES_SOURCES = $(M1_CYCLES_SOURCES) $(A72_CYCLES_SOURCES)

BENCHFLAGS = -I$(CYCLES_PATH)

ASM_HEADERS =
ASM_SOURCES =
C_HEADERS = api.h cmov.h owcpa.h params.h poly.h sample.h
C_SOURCES = cmov.c kem.c \
	owcpa.c pack3.c packq.c poly.c \
	poly_r2_inv.c poly_s3_inv.c sample.c \
	sample_iid.c
C_HEADERS += neon_batch_multiplication.h neon_matrix_transpose.h
C_SOURCES += neon_batch_multiplication.c neon_matrix_transpose.c neon_poly_lift.c neon_poly_mod.c neon_poly_rq_mul.c

HEADERS = $(ASM_HEADERS) $(C_HEADERS) $(HASH_HEADERS) $(RAND_HEADERS)
SOURCES = $(ASM_SOURCES) $(C_SOURCES) $(HASH_SOURCES) $(RAND_SOURCES)


all: test testvectors

test: $(HEADERS) $(SOURCES) test.c
	$(CC) $(CFLAGS) $(SOURCES) test.c -o test

testvectors: $(HEADERS) $(SOURCES) testvectors.c
	$(CC) $(CFLAGS) $(SOURCES) -DNORAND testvectors.c -o testvectors

speed: $(HEADERS) $(SOURCES) $(CYCLES_HEADERS) $(CYCLES_SOURCES) speed.c
	$(CC) $(CFLAGS) $(BENCHFLAGS) -DBENCH $(SOURCES) $(CYCLES_SOURCES) speed.c -o speed

speed_arith: $(HEADERS) $(SOURCES) $(CYCLES_HEADERS) $(CYCLES_SOURCES) speed_arith.c
	$(CC) $(CFLAGS) $(BENCHFLAGS) -DBENCH $(SOURCES) $(CYCLES_SOURCES) speed_arith.c -o speed_arith

.PHONY: clean

clean:
	-$(RM) -rf *.o
	-$(RM) -rf *.gch
	-$(RM) -rf test
	-$(RM) -rf speed
	-$(RM) -rf speed_arith
	-$(RM) -rf testvectors





