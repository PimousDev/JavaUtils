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

#include "funcTest.h"

#include <stdlib.h>
#include <stdio.h>

#include "../puctest.inc.h"
#include "funcTest.inc.h"
#include "../util/util.inc.h"

static const char* const FUNCTEST_HEADER_FORMAT = "%s| %s function test... ";
static const char* const FUNCTEST_FOOTER_FORMAT = "%s (%d)\n";

// CONSTRUCTORS
FuncTest* puctest_funcTest_construct(
   const char* const name,
   const FuncTestFunction func,
   const bool withValgrind
){
    FuncTest* funcTest = malloc(sizeof(struct _FuncTest));
	if(funcTest == NULL) return NULL;

    funcTest->name = name;
    funcTest->func = func;
	funcTest->withValgrind = withValgrind;

    return funcTest;
}

// DESTRUCTORS
void puctest_funcTest_destruct(FuncTest* funcTest){
	free((FuncTest*) funcTest);
}

// SETTERS
const char* puctest_funcTest_getName(const FuncTest* funcTest){
	return funcTest->name;
}

// FUNCTIONS
bool puctest_funcTest_run(const FuncTest* funcTest,
	const char* path,
	const unsigned char level
){
	printf(FUNCTEST_HEADER_FORMAT,
		puctest_util_chrRep(INDENTATION_CHAR, level),
		puctest_funcTest_getName(funcTest)
	);

	const unsigned char exitCode = funcTest->func(NULL);
	const bool passed = exitCode == EXIT_SUCCESS;

	printf(FUNCTEST_FOOTER_FORMAT,
		passed ? PUCTEST_PASSED_FORMAT : PUCTEST_FAILED_FORMAT,
		exitCode
	);

	return passed;
}