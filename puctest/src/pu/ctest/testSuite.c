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

#include "testSuite.inc.h"

// CONSTRUCTORS
const TestSuite* puctest_testSuite_construct(
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
	free(testSuite);
}

// GETTERS
const char* puctest_testSuite_getName(const TestSuite* testSuite){
	return testSuite->name;
}
unsigned short puctest_testSuite_getCount(const TestSuite* testSuite){
	return testSuite->count;
}

// SETTERS
const TestSuite* puctest_testSuite_addTest(TestSuite* testSuite,
	const TestType type, const GenericTest test
){
	if(testSuite->index >= testSuite->count) return NULL;

	testSuite->tests[testSuite->index] = (Test) {type, {
		NULL
	}};
	switch(type){
		case TestType_FUNC:
			testSuite->tests[testSuite->index].test.funcTest = test.funcTest;
			break;
		default:
			break;
	}

	testSuite->index++;
	return NULL;
}