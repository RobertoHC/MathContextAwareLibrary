#ifndef VARMATH_H
#define VARMATH_H

#include "v_common.h"

// v_* functions match standard API
#ifdef __cplusplus
extern "C" {
#endif
	F_DECLARATIONS_ONE(exp, double, double)
	F_DECLARATIONS_ONE(log, double, double)
	F_DECLARATIONS_ONE(cos, double, double)
	F_DECLARATIONS_ONE(sin, double, double)
	F_DECLARATIONS_ONE(tan, double, double)
	F_DECLARATIONS_TWO(pow, double, double, double)
#ifdef __cplusplus
}
#endif




#endif
