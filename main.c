//sin,0,temperature,60,100,2,4
#include <stdio.h>
#include "varmathlib.h"

double a = 1.1f;
double b = 1.12f;

int main() {

	printf("pow %f %f = %f", a,b, v_pow(a,b));
	v_pow_set_qlevel(3);
	printf("pow %f %f = %f", a,b, v_pow(a,b));
	v_pow_set_qlevel(2);
	return 0;

}
