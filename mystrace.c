#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include "mystrace.h"

char* cmd[] = {
	"ls",
	NULL
};
int child_status;

void die(char* message){
	printf("failed with message: '%s'\n", message);
	exit(-1);
}

void tracee(){
	printf("I'm the tracee with pid=%d\n", getpid());
	if(ptrace(PTRACE_TRACEME, NULL, NULL, NULL)<0){
		die("error traceing myself");
	}
	execvp(cmd[0], cmd);
}

void show_syscall(int syscall_no, int syscall_ret){
	char * syscall_name = syscall_table[syscall_no];
	char * ox = "";
	if(syscall_ret > 15){
		ox = "0x";
	}
	printf("%-10s = %s%x\n", syscall_name, ox, syscall_ret);
}

void tracer(int child_pid){
	printf("I'm the tracer with pid=%d\n", getpid());
	printf("child_status=%d\n", child_status);
	wait(&child_status);

	int syscall_count = 0;	
	enum syscall_state syscall_state = PRE_SYSCALL;
	struct user_regs_struct tracee_regs;
	while(1){
		syscall_count += 1;

		if(ptrace(PTRACE_SYSCALL, child_pid, NULL, NULL)<0){
			die("error tracing syscalls");
		}
		wait(&child_status);

		if(WIFEXITED(child_status)){
			printf("exited in %d syscalls with status=%d\n", syscall_count, child_status);
			break;
		}

		if(ptrace(PTRACE_GETREGS, child_pid, NULL, &tracee_regs)<0){
			die("error getting registers");
		}
		if(syscall_state == POST_SYSCALL){
			int current_syscall_no = tracee_regs.orig_rax;
			int current_syscall_return = tracee_regs.rax;
			show_syscall(current_syscall_no, current_syscall_return);
			syscall_state = PRE_SYSCALL;
		}else{
			syscall_state = POST_SYSCALL;
		}

	}
}

int main(int argc, char* arg[]){
	int pid = fork();
	switch(pid){
		case -1:
			die("error forking");
			break;
		case 0:
			tracee();
			break;
		default: 
			tracer(pid);
			break;
	}
	return 0;
}
