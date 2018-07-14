#include "process.h"
#include "eusart1.h"
#include "execute.h"
#include "functions.h"
#include <string.h>

static State state = IDLE;
static ProcessCmd currentCmd = {.cmd = NULL};

bool process_setCmd(ProcessCmd * cmd) {

	bool result = false;
	
	if (cmd != NULL) {
		execute_initCmd(cmd);
		if (strcmp(cmd->cmd, "start") == 0) {
			currentCmd = *cmd;
			if (execute_setCmd(cmd)) {
				result = true;
			}
		}
	}

	return result;
}

static void send(uint8_t * data, uint8_t len) {

	uint8_t i = 0;

	if (data != NULL) {
		while (len > 0) {
			EUSART1_Write(data[i++]);
			len--;
		}
	}
}

void process_init() {

	state = IDLE;

	if (EUSART1_is_tx_ready()) {
		EUSART1_Write('@');
	} else {
		state = ERROR;
	}
}

void process_task() {
	fun_v0();
}
