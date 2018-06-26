#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include "test.h"
#include "mock.h"

// Code Under Test
#include "process.c"

MOCK_CREATE_0(bool, EUSART1_is_tx_ready, 5,);
MOCK_CREATE_V1(EUSART1_Write, uint8_t, 5,);
ProcessCmd execute_initCmd_Cmd = {.cmd = "", .timeRef = 0, .option = 0};
MOCK_CREATE_1(int, execute_initCmd, ProcessCmd *, 5, *p1 = execute_initCmd_Cmd);
MOCK_CREATE_1(int, execute_setCmd, ProcessCmd *, 5,);

int main(void) {

	// process_init() -> When the Tx is NOT ready to send.
	MOCK_CLEAR(EUSART1_is_tx_ready);
	MOCK_CLEAR(EUSART1_Write);
	MOCK_SET_RETURN(EUSART1_is_tx_ready, 1, false);

	process_init();

	TEST_EXPECTED(MOCK_NB_CALLS(EUSART1_is_tx_ready), 1);
	TEST_EXPECTED(state, ERROR);


	// process_init() -> When the Tx is ready to send.
	MOCK_CLEAR(EUSART1_is_tx_ready);
	MOCK_CLEAR(EUSART1_Write);
	MOCK_SET_RETURN(EUSART1_is_tx_ready, 1, true);

	process_init();

	TEST_EXPECTED(MOCK_NB_CALLS(EUSART1_is_tx_ready), 1);
	TEST_EXPECTED(MOCK_NB_CALLS(EUSART1_Write), 1);
	TEST_EXPECTED(P1(EUSART1_Write, 1), '@');
	TEST_EXPECTED(state, IDLE);


	// send() -> When data is NULL
	MOCK_CLEAR(EUSART1_Write);
	send(NULL, 3);
	TEST_EXPECTED( MOCK_NB_CALLS(EUSART1_Write), 0);


	// send() -> When "test" is send.
	MOCK_CLEAR(EUSART1_Write);

	send((uint8_t *)"test", strlen("test"));

	TEST_EXPECTED( MOCK_NB_CALLS(EUSART1_Write), 4);
	TEST_EXPECTED( P1(EUSART1_Write, 1), 't');
	TEST_EXPECTED( P1(EUSART1_Write, 2), 'e');
	TEST_EXPECTED( P1(EUSART1_Write, 3), 's');
	TEST_EXPECTED( P1(EUSART1_Write, 4), 't');

	// process_setCmd() -> execute_initCmd returns INVALID cmd.
	ProcessCmd cmd = {.cmd = "", .timeRef = 0, .option = 0};
	MOCK_CLEAR(execute_initCmd);
	execute_initCmd_Cmd.cmd = "toto";
	MOCK_SET_RETURN(execute_setCmd, 1, 1);
	TEST_EXPECTED(process_setCmd(&cmd), false);
	TEST_EXPECTED( MOCK_NB_CALLS(execute_setCmd), 0);

	// process_setCmd() -> execute_initCmd returns VALID cmd.
	MOCK_CLEAR(execute_initCmd);
	MOCK_CLEAR(execute_setCmd);
	execute_initCmd_Cmd.cmd = "start";
	execute_initCmd_Cmd.timeRef = 1000;
	execute_initCmd_Cmd.option = 0;
	MOCK_SET_RETURN(execute_setCmd, 1, 1);

	TEST_TRUE(process_setCmd(&cmd));

	TEST_EXPECTED( MOCK_NB_CALLS(execute_initCmd), 1);
	TEST_EXPECTED( MOCK_NB_CALLS(execute_setCmd), 1);
	TEST_STRING( P1(execute_setCmd, 1)->cmd, "start");
	TEST_EXPECTED( P1(execute_setCmd, 1)->timeRef, 1000);
	TEST_EXPECTED( P1(execute_setCmd, 1)->option, 0);
}
