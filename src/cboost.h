#ifndef CBOOST_H_
#define CBOOST_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include "test.h"
#inclide "mock.h"

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b)) 
#endif

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b)) 
#endif

#ifdef	__cplusplus
}
#endif

#endif
