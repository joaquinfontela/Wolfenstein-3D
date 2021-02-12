#ifndef __CPPUNIT_H__
#define __CPPUNIT_H__
#include <string>

#define Test(name) 												void name()

#define TEST_ASSERT_TRUE(x) 									CUNIT_ASSERT_TRUE(x, __func__, __LINE__)
#define TEST_ASSERT_FALSE(x) 									CUNIT_ASSERT_FALSE(x, __func__, __LINE__)
#define TEST_ASSERT_EQUAL_INT(x, y) 							CUNIT_ASSERT_EQUAL_INT(x, y, __func__, __LINE__)
#define TEST_ASSERT_NOT_EQUAL_INT(x, y) 						CUNIT_ASSERT_NOT_EQUAL_INT(x, y, __func__, __LINE__)
#define TEST_ASSERT_INT_WITHIN(x, y, z) 						CUNIT_ASSERT_INT_WITHIN(x, y, z, __func__, __LINE__)
#define TEST_ASSERT_EQUAL_STRING(x, y) 							CUNIT_ASSERT_EQUAL_STRING(x, y, __func__, __LINE__)
#define TEST_ASSERT_NOT_EQUAL_STRING(x, y)						CUNIT_ASSERT_NOT_EQUAL_STRING(x, y, __func__, __LINE__)
#define TEST_ASSERT_NULL(x)										CUNIT_ASSERT_NULL(x, __func__, __LINE__)
#define TEST_ASSERT_EQUAL_POINTER(x, y)							CUNIT_ASSERT_EQUAL_POINTER(x, y, __func__, __LINE__)
#define TEST_ASSERT_EQUAL_INT_ARRAY(x, y, z, j)					CUNIT_ASSERT_EQUAL_INT_ARRAY(x, y, z, j, __func__, __LINE__)
#define TEST_ASSERT_EQUAL_CHAR_ARRAY(x, y, z, j)				CUNIT_ASSERT_EQUAL_CHAR_ARRAY(x, y, z, j, __func__, __LINE__)
#define TEST_ASSERT_EQUAL_STRING_ARRAY(x, y, z, j)				CUNIT_ASSERT_EQUAL_STRING_ARRAY(x, y, z, j, __func__, __LINE__)

#define TEST_ASSERT_THROWS(function, exception)                 try{RUN_TEST(function);}catch(exception& e){PRINT_SUCCESS(__func__, __LINE__);}

class TestSuit{

private:
    std::string name;
    void (*tests[256])(void);
    unsigned int testAmount;

public:

    TestSuit(std::string suitName);
    void addTest(void (*test)(void));
    void run();
};

void RUN_TEST(void (*test)());

void PRINT_SUCCESS(const char* test, int line);
void PRINT_FAILURE(const char* test, int line);

void TEST_PRINT_OVERALL();

void CUNIT_ASSERT_TRUE(bool condition, const char* test, int line);

void CUNIT_ASSERT_FALSE(bool condition, const char* test, int line);

void CUNIT_ASSERT_EQUAL_INT(int x, int y, const char* test, int line);

void CUNIT_ASSERT_NOT_EQUAL_INT(int x, int y, const char* test, int line);

void CUNIT_ASSERT_INT_WITHIN(unsigned int delta, int expected, int num, const char* test, int line);

void CUNIT_ASSERT_EQUAL_STRING(const char* expected, const char* actual, const char* test, int line);

void CUNIT_ASSERT_EQUAL_POINTER(void* expected, void* actual, const char* test, int line);

void CUNIT_ASSERT_NULL(void* pointer, const char* test, int line);

void CUNIT_ASSERT_EQUAL_INT_ARRAY(int* expected, int* actual, int lengthExpected, int lengthActual, const char* test, int line);

void CUNIT_ASSERT_EQUAL_CHAR_ARRAY(char* expected, char* actual, int lengthExpected, int lengthActual, const char* test, int line);

void CUNIT_ASSERT_EQUAL_STRING_ARRAY(char** expected, char** actual, int lengthExpected, int lengthActual, const char* test, int line);


#endif