#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include "mygdb.h"


void die(char* message){
  printf("failed with message: '%s'\n", message);
  exit(-1);
}

void tracee(char* cmd[]){
  printf("I'm the tracee with pid=%d\n", getpid());
  if(ptrace(PTRACE_TRACEME, NULL, NULL, NULL)<0){
    die("error traceing myself");
  }
  execvp(cmd[0], cmd);
}

void tracee_with_pid(int pid){
  // todo: detach later
  if(ptrace(PTRACE_ATTACH, pid, NULL, NULL)<0){
    die("error attaching to a pid\n does the pid exist? are you root?");
  }
}

int prompt_user(struct user_regs_struct *regs){
  const char* prompt_symbol = "=> ";
  int prompt_buffer = 200;

  for(;;){
    puts(prompt_symbol);
    char action[prompt_buffer];
    scanf("%s", action);

    if(strcmp("regs", action)==0){
      show_registers(regs);
      continue;
    }
    if(strcmp("step", action)==0 || strcmp("s", action)==0){
      return 's';
    }
    if(strcmp("finish", action)==0 || strcmp("f", action)==0){
      return 'f';
    }

    printf("action not found\n");
  }
}

void tracer(int child_pid){
  int child_status;

  printf("I'm the tracer with pid=%d\n", getpid());
  printf("child_status=%d\n", child_status);

  wait(&child_status);

  int steps_count = 0;
  struct user_regs_struct tracee_regs;
  enum debugging_state debugging_state = SINGLE_STEP;
  while(1){
    if(debugging_state == SINGLE_STEP){
      if(ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL)<0){
        die("error tracing syscalls");
      }
    }else{
      if(ptrace(PTRACE_CONT, child_pid, NULL, NULL)<0){
        die("error continuing tracee");
      }

    }
    wait(&child_status);
    steps_count += 1;

    if(WIFEXITED(child_status)){
      printf("exited in %d steps with status=%d\n", steps_count, child_status);
      break;
    }

    if(ptrace(PTRACE_GETREGS, child_pid, NULL, &tracee_regs)<0){
      die("error getting registers");
    }

    char user_action = prompt_user(&tracee_regs);
    switch(user_action){
      case 'f':
        debugging_state = NON_STOP;
        break;
    }
  }
}

int main(int argc, char* argv[]){
  char* usage_banner = "usage: ./mygdb [<cmd>|-p <pid>]";

  if(argc < 2){
    die(usage_banner);
  }

  // really simple parsing
  if(strcmp(argv[1], "-p")==0){
    if(argc < 3){
      die(usage_banner);
    }
    int pid = atoi(argv[2]);
    tracee_with_pid(pid);
    tracer(pid);
  }else{
    int pid = fork();
    switch(pid){
      case -1:
        die("error forking");
        break;
      case 0:
        tracee(argv+1);
        break;
      default:
        tracer(pid);
        break;
    }
  }
  return 0;
}
