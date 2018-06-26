/* 
 * File:   process.h
 * Author: Proprietaire
 *
 * Created on June 18, 2018, 9:45 AM
 */

#ifndef PROCESS_H
#define	PROCESS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "general.h"

typedef struct {
	char const * cmd;
	unsigned long timeRef;
	uint8_t option;
} ProcessCmd;

typedef enum {
	IDLE,
	RUN,
	ERROR
} State;

    void process_init();
    void process_task();
    bool process_setCmd(ProcessCmd * cmd);

#ifdef UNIT_TEST
    void send(uint8_t * data, uint8_t len);
    extern State state;
    extern ProcessCmd currentCmd;
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* PROCESS_H */

