int execute_setCmd(ProcessCmd * cmd) {
    return 0;
}

int execute_initCmd(ProcessCmd * cmd) {
	cmd->cmd = "start";
	cmd->timeRef = 1000;
	cmd->option = 0;
	
	return 0;
}
