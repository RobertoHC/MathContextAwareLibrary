#include "v_common.h"
#include "fastonebigheader.h"

double (*v_cos)( double arg );

F_ONE(cos, 0, double, double, cos)
F_ONE(cos, 1, double, double, cosf)
F_ONE(cos, 2, double, double, fastcos)
F_ONE(cos, 3, double, double, fastercos)

double (*__v_cos[])(double arg) = {__var__cos0, __var__cos1, __var__cos2, __var__cos3};

LEVELS(cos, 3)
LIB_INIT( cos, "cos" ) 


double (*v_sin)( double arg );

F_ONE(sin, 0, double, double, sin)
F_ONE(sin, 1, double, double, sinf)
F_ONE(sin, 2, double, double, fastsin)
F_ONE(sin, 3, double, double, fastersin)

double (*__v_sin[])(double arg) = {__var__sin0, __var__sin1, __var__sin2, __var__sin3};

LEVELS(sin, 3)
LIB_INIT( sin, "sin" )


double (*v_exp)( double arg );

F_ONE(exp, 0, double, double, exp)
F_ONE(exp, 1, double, double, expf)
F_ONE(exp, 2, double, double, fastexp)
F_ONE(exp, 3, double, double, fasterexp)

double (*__v_exp[])(double arg) = {__var__exp0, __var__exp1, __var__exp2, __var__exp3};

LEVELS(exp, 3)
LIB_INIT( exp, "exp" )


double (*v_log)( double arg );

F_ONE(log, 0, double, double, log)
F_ONE(log, 1, double, double, logf)
F_ONE(log, 2, double, double, fastlog)
F_ONE(log, 3, double, double, fasterlog)

double (*__v_log[])(double arg) = {__var__log0, __var__log1, __var__log2, __var__log3};

LEVELS(log, 3)
LIB_INIT( log, "log" )



double (*v_tan)( double arg );

F_ONE(tan, 0, double, double, tan)
F_ONE(tan, 1, double, double, tanf)
F_ONE(tan, 2, double, double, fasttan)
F_ONE(tan, 3, double, double, fastertan)

double (*__v_tan[])(double arg) = {__var__tan0, __var__tan1, __var__tan2, __var__tan3};


LEVELS(tan, 3)
LIB_INIT( tan, "tan" )




double (*v_pow)( double arg1, double arg2 );

F_TWO(pow, 0, double, double, double, pow)
F_TWO(pow, 1, double, double, double, powf)
F_TWO(pow, 2, double, double, double, fastpow)
F_TWO(pow, 3, double, double, double, fasterpow)

double (*__v_pow[])(double arg1, double arg2) = {__var__pow0, __var__pow1, __var__pow2, __var__pow3};

LEVELS(pow, 3)
LIB_INIT( pow, "pow" )
