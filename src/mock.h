#ifndef MOCK_H_
#define MOCK_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include "test.h"

#define MOCK_CLEAR(functionName) do { \
		functionName##_init();\
	} while (0)


// callNb starts at 1.
#define MOCK_SET_RETURN(functionName, callNb, value) do {\
		if (callNb == 0) {\
			TEST_PRINT("Error - MOCK_SET_RETURN callNb must start to 1.\n\r");\
		} else if ((callNb - 1) >= functionName##_nbOfCallsMax) {\
			TEST_PRINT("Error - MOCK_SET_RETURN callNb must be lower than the max value.\n\r");\
		} else {\
			functionName##_return[callNb - 1] = value;\
		}\
	} while (0)

#define MOCK_NB_CALLS(functionName)  functionName##_nbCalls

#define MOCK_PARAM(functionName, paramNb, callNb)  functionName##_p##paramNb[callNb - 1]
#define P1(functionName, callNb)  MOCK_PARAM(functionName, 1, callNb)
#define P2(functionName, callNb)  MOCK_PARAM(functionName, 2, callNb)
#define P3(functionName, callNb)  MOCK_PARAM(functionName, 3, callNb)
#define P4(functionName, callNb)  MOCK_PARAM(functionName, 4, callNb)
#define P5(functionName, callNb)  MOCK_PARAM(functionName, 5, callNb)
#define P6(functionName, callNb)  MOCK_PARAM(functionName, 6, callNb)
#define P7(functionName, callNb)  MOCK_PARAM(functionName, 7, callNb)
#define P8(functionName, callNb)  MOCK_PARAM(functionName, 8, callNb)
#define P9(functionName, callNb)  MOCK_PARAM(functionName, 9, callNb)
#define P10(functionName, callNb)  MOCK_PARAM(functionName, 10, callNb)




/* TODO En plein milieu de déveoppement des macros communes !!! */


/* Private macros: only used within mock.h file. */
#define PRIVATE_COMMUN_UTIL_CODE(returnType, functionName, nbOfCallsMax) \
	unsigned int functionName##_nbCalls = 0; \
	unsigned int functionName##_nbOfCallsMax = nbOfCallsMax; \
	returnType functionName##_return[nbOfCallsMax]; \
	void functionName##_init() {\
		functionName##_nbCalls = 0;\
	}

#define PRIVATE_COMMUN_UTIL_CODE_VOID(functionName, nbOfCallsMax) \
	unsigned int functionName##_nbCalls = 0; \
	unsigned int functionName##_nbOfCallsMax = nbOfCallsMax; \
	void functionName##_init() {\
		functionName##_nbCalls = 0;\
	}

#define PRIVATE_COMMUN_FUNC_CODE(functionName) \
	functionName##_nbCalls++;\
	if (functionName##_nbCalls > functionName##_nbOfCallsMax) {\
		char * f = #functionName; \
		TEST_PRINT("Error - ");\
		TEST_PRINT(f);\
		TEST_PRINT(" nb of calls is higher than the max value.\n\r");\
		return functionName##_return[0];\
	}

#define PRIVATE_COMMUN_VOID_FUNC_CODE(functionName) \
	functionName##_nbCalls++;\
	if (functionName##_nbCalls > functionName##_nbOfCallsMax) {\
		char * f = #functionName; \
		TEST_PRINT("Error - ");\
		TEST_PRINT(f);\
		TEST_PRINT(" nb of calls is higher than the max value.\n\r");\
		return;\
	}
/* End of Private macros. */



/*
 * MOCK_CREATE section
 */

#define MOCK_CREATE_V0(functionName, nbOfCallsMax, code) \
	PRIVATE_COMMUN_UTIL_CODE_VOID(functionName, nbOfCallsMax);\
	void functionName() { \
		PRIVATE_COMMUN_VOID_FUNC_CODE(functionName);\
		code; \
	}

#define MOCK_CREATE_0(returnType, functionName, nbOfCallsMax, code) \
	PRIVATE_COMMUN_UTIL_CODE(returnType, functionName, nbOfCallsMax);\
	returnType functionName() { \
		PRIVATE_COMMUN_FUNC_CODE(functionName);\
		code; \
		return functionName##_return[functionName##_nbCalls - 1];\
	}


#define MOCK_CREATE_1(returnType, functionName, typeP1, nbOfCallsMax, code) \
	PRIVATE_COMMUN_UTIL_CODE(returnType, functionName, nbOfCallsMax);\
	typeP1 functionName##_p1[nbOfCallsMax]; \
	returnType functionName( typeP1 p1) { \
		PRIVATE_COMMUN_FUNC_CODE(functionName);\
		functionName##_##p1[functionName##_nbCalls - 1] = p1;\
		code; \
		return functionName##_return[functionName##_nbCalls - 1];\
	}


#define MOCK_CREATE_V1(functionName, typeP1, nbOfCallsMax, code) \
	unsigned int functionName##_nbCalls = 0; \
	unsigned int functionName##_nbOfCallsMax = nbOfCallsMax; \
	typeP1 functionName##_p1[nbOfCallsMax]; \
	void functionName##_init() {\
		functionName##_nbCalls = 0;\
	}\
	void functionName( typeP1 p1) { \
		functionName##_nbCalls++;\
		if (functionName##_nbCalls > functionName##_nbOfCallsMax) {\
			char * f = #functionName; \
			TEST_PRINT("Error - ");\
			TEST_PRINT(f);\
			TEST_PRINT(" nb of calls is higher than the max value.\n\r");\
			return;\
		}\
		functionName##_##p1[functionName##_nbCalls - 1] = p1;\
		code; \
	}


#ifdef	__cplusplus
}
#endif

#endif
