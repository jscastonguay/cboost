#ifndef MOCK_H_
#define MOCK_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include "test.h"

#define MOCK_CLEAR(functionName) do { \
		functionName##_init();\
	} while (0)


// nbCall starts at 1.
#define MOCK_SET_RETURN(functionName, callNb, value) do {\
		if (callNb == 0) {\
			STEST_PRINT("Error - MOCK_SET_RETURN callNb must start to 1.\n\r");\
		} else if (callNb - 1 >= functionName##_nbOfCallsMax) {\
			STEST_PRINT("Error - MOCK_SET_RETURN callNb must be lower than the max value.\n\r");\
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


#define MOCK_CREATE_0(returnType, functionName, nbOfCallsMax, code) \
	unsigned int functionName##_nbCalls = 0; \
	unsigned int functionName##_nbOfCallsMax = nbOfCallsMax; \
	returnType functionName##_return[nbOfCallsMax]; \
	void functionName##_init() {\
		functionName##_nbCalls = 0;\
	}\
	returnType functionName() { \
		functionName##_nbCalls++;\
		if (functionName##_nbCalls > functionName##_nbOfCallsMax) {\
			char * f = #functionName; \
			STEST_PRINT("Error - ");\
			STEST_PRINT(f);\
			STEST_PRINT(" nb of calls is higher than the max value.\n\r");\
			return functionName##_return[0];\
		}\
		code; \
		return functionName##_return[functionName##_nbCalls - 1];\
	}


#define MOCK_CREATE_1(returnType, functionName, typeP1, nbOfCallsMax, code) \
	unsigned int functionName##_nbCalls = 0; \
	unsigned int functionName##_nbOfCallsMax = nbOfCallsMax; \
	returnType functionName##_return[nbOfCallsMax]; \
	typeP1 functionName##_p1[nbOfCallsMax]; \
	void functionName##_init() {\
		functionName##_nbCalls = 0;\
	}\
	returnType functionName( typeP1 p1) { \
		functionName##_nbCalls++;\
		if (functionName##_nbCalls > functionName##_nbOfCallsMax) {\
			char * f = #functionName; \
			STEST_PRINT("Error - ");\
			STEST_PRINT(f);\
			STEST_PRINT(" nb of calls is higher than the max value.\n\r");\
			return functionName##_return[0];\
		}\
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
			STEST_PRINT("Error - ");\
			STEST_PRINT(f);\
			STEST_PRINT(" nb of calls is higher than the max value.\n\r");\
			return;\
		}\
		code; \
		functionName##_##p1[functionName##_nbCalls - 1] = p1;\
	}


#ifdef	__cplusplus
}
#endif

#endif
