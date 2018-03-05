#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include "vemu.h"
#include <unistd.h>
#include <time.h>

typedef unsigned long long uint64_t;

int main(int argc, char **argv){
	if(argc >= 4){

		printf("%s\n", argv[1]);
		vemu_regs proc;		
	
		uint64_t energy_goal = 0, error = 5000000, average_energy_spent, average_time_spent;
		int pdi, i, iterations = 2, test_number, sleep_time, sum_test_number;
		double factor = 0.5;

		sscanf(argv[1], "%d", &pdi);
		sscanf(argv[2], "%d", &sleep_time);
		sscanf(argv[3], "%lf", &factor);
		/*Increasing quality*/
		printf("Calculating energy consumption at the highest quality\n");
		kill(pdi, 10);
		kill(pdi, 10);
		kill(pdi, 10);
		kill(pdi, 10);		
		
		/*Getting highest energy consumption*/
		
		uint64_t most_consuming_energy = 0;

		for(i = 0; i < iterations; i++){
			
			vemu_read(READ_HW, &proc);

                        sleep(sleep_time);
                        uint64_t last_energy = proc.total_act_energy;
                       
                        vemu_read(READ_HW, &proc);

                        uint64_t energy_diff = proc.total_act_energy - last_energy;
                        printf("Energy spent:  %llu nJ\n", (unsigned long long)energy_diff);

			most_consuming_energy += energy_diff;

		}
		most_consuming_energy /= iterations;

		energy_goal = most_consuming_energy * factor;
		printf("most consuming energy: %llu   energy goal %llu\n", most_consuming_energy, energy_goal);

		average_energy_spent = 0;
		average_time_spent = 0;
		test_number = 0;
		sum_test_number = 0;
		/*Testing - measuring energy consumption varying quality*/
		while(1){
			
       			vemu_read(READ_HW, &proc);
        		/*printf("\033[2J");
       			printf("\033[%d;%dH", 0, 0);
        		printf("Cycles:         %llu\n", proc.total_cycles);
        		printf("Active Energy:  %llu nJ\n", proc.total_act_energy);
        		printf("Frequency:      %llu MHz\n", (unsigned long long)(proc.frequency/1e6));
        		printf("Voltage:        %llu mV\n", proc.voltage);*/			
			
			sleep(sleep_time);
			uint64_t last_energy = proc.total_act_energy + proc.slp_energy;
			uint64_t last_time = proc.total_act_time + proc.slp_time;
			/*printf("After 10 sec..\n");*/
			vemu_read(READ_HW, &proc);

			uint64_t energy_diff = (proc.total_act_energy + proc.slp_energy) - last_energy;
			uint64_t time_diff = (proc.total_act_time + proc.slp_time) - last_time;
			average_energy_spent = (average_energy_spent * sum_test_number + energy_diff * (test_number + 1) ) / (sum_test_number + test_number + 1);
			average_time_spent = (average_time_spent * sum_test_number + time_diff * (test_number + 1) ) / (sum_test_number + test_number + 1);
			test_number++;
			sum_test_number += test_number;

                        printf("Test number: %d   Average energy spent: %llu nJ   Average time spent: %llu   Energy goal: %llu   Energy diff: %llu\n", test_number, (unsigned long long)average_energy_spent, (unsigned long long)average_time_spent, energy_goal, energy_diff);
			

			if(energy_goal + error < energy_diff){
				kill(pdi, 12);
				printf("Signals sent to process %d to decrease quality - SIGUSR1\n", pdi);

			}
			else{
				if( energy_goal - error > energy_diff){
					kill(pdi, 10);
					printf("Signals sent to process %d to increase quality - SIGUSR2\n", pdi);
				}
				else{
					kill(pdi, 12);
                                	printf("Signals sent to process %d to decrease quality - SIGUSR1\n", pdi);

				}
			}
			
			printf("\n");
		}

		/*int pdi;
		sscanf(argv[1], "%d", &pdi);
		printf("Signals sent to process %d\n", pdi);
		kill(pdi, 10);*/

		return 0;

	}
	else{
		printf("NEED AT LEAST THREE ARGUMENT\n");

	}

	return 0;
}
