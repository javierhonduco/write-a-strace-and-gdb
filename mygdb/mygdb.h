enum debugging_state {
  SINGLE_STEP,
  NON_STOP
};

void show_registers(struct user_regs_struct *regs){
  printf("%s=%lli ", "r15", regs->r15);
  printf("%s=%lli ", "r14", regs->r14);
  printf("%s=%lli ", "r13", regs->r13);
  printf("%s=%lli ", "r12", regs->r12);
  printf("%s=%lli ", "rbp", regs->rbp);
  printf("%s=%lli ", "rbx", regs->rbx);
  printf("%s=%lli ", "r11", regs->r11);
  printf("%s=%lli ", "r10", regs->r10);
  printf("%s=%lli ", "r9", regs->r9);
  printf("%s=%lli ", "r8", regs->r8);
  printf("%s=%lli ", "rax", regs->rax);
  printf("%s=%lli ", "rcx", regs->rcx);
  printf("%s=%lli ", "rdx", regs->rdx);
  printf("%s=%lli ", "rsi", regs->rsi);
  printf("%s=%lli ", "orig_rax", regs->orig_rax);
  printf("%s=%lli ", "rip", regs->rip);
  printf("%s=%lli ", "cs", regs->cs);
  printf("%s=%lli ", "eflags", regs->eflags);
  printf("%s=%lli ", "rsp", regs->rsp);
  printf("%s=%lli ", "ss", regs->ss);
  printf("%s=%lli ", "fs_base", regs->fs_base);
  printf("%s=%lli ", "gs_base", regs->gs_base);
  printf("%s=%lli ", "ds", regs->ds);
  printf("%s=%lli ", "es", regs->es);
  printf("%s=%lli ", "fs", regs->fs);
  printf("%s=%lli ", "gs", regs->gs);
  printf("\n");
}
