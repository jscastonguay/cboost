#ifndef TEST_H_
#define TEST_H_

#ifdef	__cplusplus
extern "C" {
#endif

#define TEST_PRINT  printf

#define TEST_EXPECTED(real, expected) do { \
	TEST_PRINT("test (line %d) %s\r\n", __LINE__, real == expected ? "passed" : "*** FAILED ***"); \
} while (0);

#define TEST_STRING(real, expected) do { \
	TEST_PRINT("test (line %d) %s\r\n", __LINE__, strcmp(real, expected) == 0 ? "passed" : "*** FAILED ***"); \
} while (0);

#define TEST_MEM(real, expected, nbBytes) do { \
	TEST_PRINT("test (line %d) %s\r\n", __LINE__, memcmp(real, expected, nbBytes) == 0 ? "passed" : "*** FAILED ***"); \
} while (0);

#define TEST_TRUE(test) do { \
	TEST_PRINT("test (line %d) %s\r\n", __LINE__, test ? "passed" : "*** FAILED ***"); \
} while (0);


#ifdef	__cplusplus
}
#endif

#endif
