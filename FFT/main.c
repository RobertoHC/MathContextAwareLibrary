#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <time.h>
#include "vemu.h"
#include "varmathlib.h"

void sig_handler(int signo){

  if (signo == SIGUSR1){
    printf("received signal decrease level\n");
    v_pow_set_qlevel(v_pow_get_qlevel() - 1);
    v_exp_set_qlevel(v_exp_get_qlevel() - 1);
    v_log_set_qlevel(v_log_get_qlevel() - 1);
    v_cos_set_qlevel(v_cos_get_qlevel() - 1);
    v_sin_set_qlevel(v_sin_get_qlevel() - 1);
    /*printf("pow %f %f = %f", a,b, v_pow(a,b));*/
    printf("current level after decreasing: %d\n", v_pow_get_qlevel());
  }

  if (signo == SIGUSR2){
    printf("received signal increase level\n");
    v_pow_set_qlevel(v_pow_get_qlevel() + 1);
    v_exp_set_qlevel(v_exp_get_qlevel() + 1);
    v_log_set_qlevel(v_log_get_qlevel() + 1);
    v_cos_set_qlevel(v_cos_get_qlevel() + 1);
    v_sin_set_qlevel(v_sin_get_qlevel() + 1);
    /*printf("pow %f %f = %f", a,b, v_pow(a,b));*/
    printf("current level after increasing: %d\n", v_pow_get_qlevel());  
    }
}



int main(int argc, char *argv[]) {

	vemu_regs proc;
        
        if (signal(SIGUSR1, sig_handler) == SIG_ERR) 
        	printf("\ncan't catch SIGUSR1\n");

        if (signal(SIGUSR2, sig_handler) == SIG_ERR)
                printf("\ncan't catch SIGUSR2\n");



	// Send PID to monitor
	// getpid()
	// write PID to file or socket, so that monitor can read

    while(1){

        clock_t start = clock();
	/*printf("Cycles:         %llu\n", proc.total_cycles);
        printf("Active Energy:  %llu nJ\n", proc.total_act_energy);
        printf("Frequency:      %llu MHz\n", (unsigned long long)(proc.frequency/1e6));
        printf("Voltage:        %llu mV\n", proc.voltage);*/
	vemu_read(READ_PROC, &proc);
	unsigned long long last_cycles = proc.total_cycles;
	unsigned long long last_energy = proc.total_act_energy;

	unsigned MAXSIZE;
	unsigned MAXWAVES;
	unsigned i,j;
	float *RealIn;
	float *ImagIn;
	float *RealOut;
	float *ImagOut;
	float *coeff;
	float *amp;
	int invfft=0;

	if (argc<3)
	{
		printf("Usage: fft <waves> <length> -i\n");
		printf("-i performs an inverse fft\n");
		printf("make <waves> random sinusoids");
		printf("<length> is the number of samples\n");
		exit(-1);
	}
	else if (argc==4)
		invfft = !strncmp(argv[3],"-i",2);
	MAXSIZE=atoi(argv[2]);
	MAXWAVES=atoi(argv[1]);
		
 srand(1);

 RealIn=(float*)malloc(sizeof(float)*MAXSIZE);
 ImagIn=(float*)malloc(sizeof(float)*MAXSIZE);
 RealOut=(float*)malloc(sizeof(float)*MAXSIZE);
 ImagOut=(float*)malloc(sizeof(float)*MAXSIZE);
 coeff=(float*)malloc(sizeof(float)*MAXWAVES);
 amp=(float*)malloc(sizeof(float)*MAXWAVES);

 /* Makes MAXWAVES waves of random amplitude and period */
	for(i=0;i<MAXWAVES;i++) 
	{
		coeff[i] = rand()%1000;
		amp[i] = rand()%1000;
	}
 for(i=0;i<MAXSIZE;i++) 
 {
   /*   RealIn[i]=rand();*/
	 RealIn[i]=0;
	 for(j=0;j<MAXWAVES;j++) 
	 {
		 /* randomly select sin or cos */
		 if (rand()%2)
		 {
		 		RealIn[i]+=coeff[j]*v_cos(amp[j]*i);
			}
		 else
		 {
		 	RealIn[i]+=coeff[j]*v_sin(amp[j]*i);
		 }
  	 ImagIn[i]=0;
	 }
 }

 /* regular*/
 fft_float (MAXSIZE,invfft,RealIn,ImagIn,RealOut,ImagOut);
 /*
 printf("RealOut:\n");
 for (i=0;i<MAXSIZE;i++)
   printf("%f \t", RealOut[i]);
 printf("\n");

printf("ImagOut:\n");
 for (i=0;i<MAXSIZE;i++)
   printf("%f \t", ImagOut[i]);
   printf("\n");
*/
	vemu_read(READ_PROC, &proc);
/*	
	printf("Cycles:         %llu\n", proc.total_cycles);
	printf("Active Energy:  %llu nJ\n", proc.total_act_energy);
	printf("Frequency:      %llu MHz\n", (unsigned long long)(proc.frequency/1e6));
	printf("Voltage:        %llu mV\n", proc.voltage);
*/
	printf("Iteration:\n");
	printf("Cycles:		%llu	%llu	%llu\n", proc.total_cycles - last_cycles, proc.total_cycles, last_cycles);
	printf("Energy: 	%llu	%llu	%llu\n", proc.total_act_energy - last_energy, proc.total_act_energy, last_energy);
	printf("current level: %d\n", v_cos_get_qlevel());
clock_t end = clock();
float seconds = (float)(end - start) / CLOCKS_PER_SEC;
printf("%.2lf\n", seconds);
	sleep(20 - seconds); 

   free(RealIn);
 free(ImagIn);
 free(RealOut);
 free(ImagOut);
 free(coeff);
 free(amp);

}
 exit(0);



}
