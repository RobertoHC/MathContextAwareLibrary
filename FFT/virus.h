#ifndef VIRUS_H
#define VIRUS_H

#include "fastonebigheader.h"
#include <math.h>


#ifndef VIRUS_LEVEL
#define VIRUS_LEVEL 1
#endif


#if VIRUS_LEVEL==4
#define v_exp(x) fasterexp(x)
#define v_sin(x) fastersin(x)
#define v_log(x) fasterlog(x)
#define v_cos(x) fastercos(x)

#elif VIRUS_LEVEL==3
#define v_exp(x) fastexp(x)
#define v_sin(x) fastsin(x)
#define v_log(x) fastlog(x)
#define v_cos(x) fastcos(x)

#elif VIRUS_LEVEL==2
#define v_exp(x) expf(x)
#define v_sin(x) sinf(x)
#define v_cos(x) cosf(x)
#define v_log(x) logf(x)

#else
#define v_exp(x) exp(x)
#define v_sin(x) sin(x)
#define v_log(x) log(x)
#define v_cos(x) cos(x)

#endif



#endif
