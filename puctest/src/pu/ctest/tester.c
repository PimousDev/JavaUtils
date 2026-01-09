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

#include "tester.h"

#include <stdlib.h>
#include <stdio.h>

#include "puctest.inc.h"
#include "tester.inc.h"
#include "test/funcTest.h"
#include "util/util.inc.h"

static const char* const TESTER_LICENSE_NOTE_FORMAT = "\x1B[3;38;5;8m"
"Project Utils v%s is under GNU LGPL-v3 license.\n"
"Pimous Dev. (C) 2018-%d <www.pimous.dev>; Pimous Dev. is a development studio.\n"
"This program comes with ABSOLUTELY NO WARRANTY; This is free software, and you\n"
"are welcome to redistribute it under certain conditions; See license for\n"
"details.\n"
"\x1B[0m";
static const char* const TESTER_HEADER_FORMAT =
	"TESTING \x1B[38;5;214m%s\x1B[0m:\n";
static const char* const TESTER_FOOTER_FORMAT = "TOTAL: %d/%d; %s %s";
static const char* const TESTER_PASSED_STR = ":]";
static const char* const TESTER_FAILED_STR = ":[";

// CONSTRUCTORS
Tester* puctest_tester_construct(
	const char* const name,
	const unsigned short count
){
	Tester* tester = malloc(sizeof(struct _Tester));
	if(tester == NULL) return NULL;

	tester->name = name;
	tester->testSuite = puctest_testSuite_construct(NULL, count);
	if(tester->testSuite == NULL){
		free(tester);
		return NULL;
	}

	return tester;
}

// DESTRUCTORS
void puctest_tester_destruct(Tester* tester){
	puctest_testSuite_destruct((TestSuite*) tester->testSuite);
	free(tester);
}

// GETTERS
const char* puctest_tester_getName(const Tester* tester){
	return tester->name;
}

unsigned int puctest_tester_getTotalCount(const Tester* tester){
	return puctest_testSuite_getTotalCount(tester->testSuite);
}

// SETTERS
Tester* puctest_tester_addTest(Tester* tester,
	const TestType type,
	const void* test
){
	return puctest_testSuite_addTest(tester->testSuite, type, test) == NULL
		? NULL : tester;
}

// FUNCTIONS
unsigned int puctest_tester_run(const Tester* tester, const char* path){
	printf(TESTER_LICENSE_NOTE_FORMAT, SUBPROJECT_VERSION, SUBPROJECT_YEAR);
	printf(TESTER_HEADER_FORMAT, tester->name);

	unsigned int passedCount = puctest_testSuite_runTests(tester->testSuite,
		path, 1
	);
	bool passed = false;

	printf(TESTER_FOOTER_FORMAT, passedCount,
		puctest_tester_getTotalCount(tester),
		passed ? PUCTEST_PASSED_FORMAT : PUCTEST_FAILED_FORMAT,
		passed ? TESTER_PASSED_STR : TESTER_FAILED_STR
	);

	return passedCount;
}