
#ifndef CORDIC_H
#define CORDIC_H
#include "ap_fixed.h"

typedef ap_fixed<16,3> FIX_16_3;
const int NUM_ITER = 32;

static FIX_16_3 pi = 3.14159265358979;
static FIX_16_3 pihalf = 1.570796326792;
static FIX_16_3 pifourth = 0.78539816339744;

static FIX_16_3 cordic_phase[32]={0.78539816339744828000,0.46364760900080609000,0.24497866312686414000,0.12435499454676144000,0.06241880999595735000,0.03123983343026827700,0.01562372862047683100,0.00781234106010111110,0.00390623013196697180,0.00195312251647881880,0.00097656218955931946,0.00048828121119489829,0.00024414062014936177,0.00012207031189367021,0.00006103515617420877,0.00003051757811552610,0.00001525878906131576,0.00000762939453110197,0.00000381469726560650,0.00000190734863281019,0.00000095367431640596,0.00000047683715820309,0.00000023841857910156,0.00000011920928955078,0.00000005960464477539,0.00000002980232238770,0.00000001490116119385,0.00000000745058059692,0.00000000372529029846,0.00000000186264514923,0.00000000093132257462,0.00000000046566128731};
static char scaling_factors[4]={1,2,5,10};

void cordic(bool mode, FIX_16_3 x, FIX_16_3 y, FIX_16_3 z, FIX_16_3 &a, FIX_16_3 &b, FIX_16_3 &c);

#endif