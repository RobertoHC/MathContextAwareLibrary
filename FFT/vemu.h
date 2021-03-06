#ifndef vemu_h
#define vemu_h

#include <unistd.h>

#define VAR_SYSCALL_READ 	378
#define VAR_SYSCALL_WRITE 	379

typedef unsigned long long uuint64_t;
typedef unsigned long uuint32_t;

#define 	MAX_INSTR_CLASSES	4


#define SET_FAULTS			(0x000)
#define SET_FREQUENCY		(SET_FAULTS+8)	
#define SET_VOLTAGE			(SET_FREQUENCY+8)
#define READ_CMD       		(0xD00)
#define EXIT_CMD           	(0xF00)

#define	READ_HW				(0x1000000)
#define	READ_SYS			(0x0100000)
#define	READ_PROC			(0x0010000)

typedef struct {
	uuint64_t act_time[MAX_INSTR_CLASSES];
	uuint64_t act_energy[MAX_INSTR_CLASSES];
	uuint64_t cycles[MAX_INSTR_CLASSES];    
	uuint64_t total_act_time;
	uuint64_t total_act_energy;
	uuint64_t total_cycles;  
	uuint64_t slp_time;
	uuint64_t slp_energy;  
	uuint64_t fault_status;
	uuint64_t frequency;
	uuint64_t voltage;
} vemu_regs;

#define VEMU_STATE_N_VARS	(MAX_INSTR_CLASSES*3+8)

typedef union {
	vemu_regs variables;
	uuint32_t array32[VEMU_STATE_N_VARS*2];
	uuint64_t array64[VEMU_STATE_N_VARS];
} vemu_state;

void vemu_write(uuint32_t reg, unsigned long long val) {
	unsigned long long int tempv;
	tempv = val;
	syscall(VAR_SYSCALL_WRITE, reg, &tempv);
}

void vemu_read(uuint32_t regtype, vemu_regs * regs) {
	syscall(VAR_SYSCALL_READ, regtype, regs);
}

void vemu_delta(vemu_regs * target, vemu_regs * newb, vemu_regs * old)
{
	int i;
	for (i = 0; i < VEMU_STATE_N_VARS - 1; i++) 
	{
		((vemu_state*)target)->array64[i] = ((vemu_state*)newb)->array64[i] - ((vemu_state*)old)->array64[i];
	}
} 

void vemu_enable_errors(unsigned long long idx) {
	vemu_write(SET_FAULTS, idx);
}

void vemu_disable_errors() {
	vemu_write(SET_FAULTS, 0);
}

void vemu_dvfs(uuint64_t freq, uuint64_t voltagemv)
{
	vemu_write(SET_FREQUENCY, freq);
	vemu_write(SET_VOLTAGE, voltagemv);
}

void vemu_kill() {
	vemu_write(EXIT_CMD, 1);
}



#endif
