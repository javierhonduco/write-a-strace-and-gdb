enum debugging_state {
	SINGLE_STEP,
	NON_STOP	
};

void show_registers(struct user_regs_struct *regs){
	printf("%s=%d ", "r15", regs->r15);
	printf("%s=%d ", "r14", regs->r14);
	printf("%s=%d ", "r13", regs->r13);
	printf("%s=%d ", "r12", regs->r12);
	printf("%s=%d ", "rbp", regs->rbp);
	printf("%s=%d ", "rbx", regs->rbx);
	printf("%s=%d ", "r11", regs->r11);
	printf("%s=%d ", "r10", regs->r10);
	printf("%s=%d ", "r9", regs->r9);
	printf("%s=%d ", "r8", regs->r8);
	printf("%s=%d ", "rax", regs->rax);
	printf("%s=%d ", "rcx", regs->rcx);
	printf("%s=%d ", "rdx", regs->rdx);
	printf("%s=%d ", "rsi", regs->rsi);
	printf("%s=%d ", "orig_rax", regs->orig_rax);
	printf("%s=%d ", "rip", regs->rip);
	printf("%s=%d ", "cs", regs->cs);
	printf("%s=%d ", "eflags", regs->eflags);
	printf("%s=%d ", "rsp", regs->rsp);
	printf("%s=%d ", "ss", regs->ss);
	printf("%s=%d ", "fs_base", regs->fs_base);
	printf("%s=%d ", "gs_base", regs->gs_base);
	printf("%s=%d ", "ds", regs->ds);
	printf("%s=%d ", "es", regs->es);
	printf("%s=%d ", "fs", regs->fs);
	printf("%s=%d ", "gs", regs->gs);
	printf("\n");
}
