/* Project Utils (Tools and Utility librairies/classes)
	Copyright &copy; 2024 - Pimous Dev. (https://www.pimous.dev/)

	These programs is free software: you can redistribute it and/or modify it
	under the terms of the GNU Lesser General Public License as published by the
	Free Software Foundation, either version 3 of the License, or (at your
	option) any later version.

	The latters are distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
	for more details.

	You should have received a copy of the GNU General Public License and the
	GNU Lesser General Public License along with the programs (COPYING &
	COPYING.LESSER). If not, see https://www.gnu.org/licenses/.
*/

#include "testSuite.h"

#include <stdlib.h>
#include <stdio.h>

#include "puctest.inc.h"
#include "testSuite.inc.h"
#include "util/util.inc.h"

static const char* const SUITE_HEADER_FORMAT = "%s+ %s suite:\n";

// CONSTRUCTORS
TestSuite* puctest_testSuite_construct(
	const char* const name, const unsigned short count
){
	if(count <= 0) return NULL;

	TestSuite* testSuite = malloc(
		sizeof(struct _TestSuite) + sizeof(struct _Test)*count
	);
	if(testSuite == NULL) return NULL;

	testSuite->name = name;
	testSuite->count = count;
	testSuite->index = 0;

	return testSuite;
}

// DESTRUCTORS
void puctest_testSuite_destruct(TestSuite* testSuite){
	Test test;
	for(unsigned short i = 0; i < testSuite->index; i++){
		test = testSuite->tests[i];

		switch(test.type){
			case TestType_UNDEFINED:
				break;
			case TestType_SUITE:
				puctest_testSuite_destruct((TestSuite*) test.test.testSuite);
				break;
			case TestType_FUNC:
				puctest_funcTest_destruct((FuncTest*) test.test.funcTest);
				break;
		}
	}

	free(testSuite);
}

// GETTERS
const char* puctest_testSuite_getName(const TestSuite* testSuite){
	return testSuite->name;
}
unsigned short puctest_testSuite_getCount(const TestSuite* testSuite){
	return testSuite->count;
}

unsigned int puctest_testSuite_getTotalCount(const TestSuite* testSuite){
	unsigned int count = 0;

	Test test;
	for(unsigned short i = 0; i < testSuite->index; i++){
		test = testSuite->tests[i];

		switch(test.type){
			case TestType_UNDEFINED:
				break;
			case TestType_SUITE:
				count += puctest_testSuite_getTotalCount(test.test.testSuite);
				break;
			case TestType_FUNC:
				count += puctest_funcTest_getTotalCount(test.test.funcTest);
				break;
		}
	}

	return count;
}

// SETTERS
TestSuite* puctest_testSuite_addTest(TestSuite* testSuite,
	const TestType type,
	const void* test
){
	if(testSuite->index >= puctest_testSuite_getCount(testSuite)) return NULL;

	if(type != TestType_UNDEFINED){
		GenericTest gTest = {NULL};
		switch(type){
			case TestType_UNDEFINED:
				break; // Can't happen.
			case TestType_SUITE:
				gTest.testSuite = test;
				break;
			case TestType_FUNC:
				gTest.funcTest = test;
				break;
		}

		testSuite->tests[testSuite->index] = (Test) {type, gTest};
	}

	testSuite->index++;
	return testSuite;
}

// FUNCTIONS
unsigned int puctest_testSuite_run(const TestSuite* testSuite,
	const char* path,
	const unsigned char level
){
	printf(SUITE_HEADER_FORMAT,
		puctest_util_chrRep(INDENTATION_CHAR, level),
		puctest_testSuite_getName(testSuite)
	);

	return puctest_testSuite_runTests(testSuite, path, level + 1);
}
unsigned int puctest_testSuite_runTests(const TestSuite* testSuite,
	const char* path,
	const unsigned char level
){
	unsigned int passed = 0;

	Test test;
	for(unsigned short i = 0; i < puctest_testSuite_getCount(testSuite); i++){
		test = testSuite->tests[i];

		// TODO: Filter using path.

		switch(test.type){
			case TestType_UNDEFINED:
				break;
			case TestType_SUITE:
				passed += puctest_testSuite_run(test.test.testSuite,
					path, level
				);
				break;
			case TestType_FUNC:
				if(puctest_funcTest_run(test.test.funcTest, path, level))
					passed += 1;
				break;
		}
	}

	return passed;
}