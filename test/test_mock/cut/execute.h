/* 
 * File:   execute.h
 * Author: Proprietaire
 *
 * Created on June 18, 2018, 2:31 PM
 */

#ifndef EXECUTE_H
#define	EXECUTE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "process.h"

    int execute_setCmd(ProcessCmd * cmd);
    int execute_initCmd(ProcessCmd * cmd);

#ifdef	__cplusplus
}
#endif

#endif	/* EXECUTE_H */

