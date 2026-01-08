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

#pragma once

#if !defined (_PUCTEST_INSIDE) && !defined (PUCTEST_COMPILATION)
	#error "Only <pu/ctest/puctest.h> can be included directly;"
#endif

#include <stdbool.h>

// MACROS
#ifndef TESTFUNC_MEMORY_EXECUTABLE
	/** Defines the binary used to check memory calls when `FuncTest` should,
	 * with `"valgrind"` by default.
	 */
	#define TESTFUNC_MEMORY_EXECUTABLE "valgrind"
#endif

// TYPES
/** A function accepted by `FuncTest`.
 * @param context `Tester` context, currently always NULL.
 * @return Whether the test passed, like exit codes (0 means a success, more
 * than 0 means a failure).
 */
typedef unsigned char (*FuncTestFunction)(const void* context);
/** Represents a named test passed by executing a C function. It may be
 * virtually divided into two tests to also check memory calls using a binary
 * given at TESTFUNC_MEMORY_EXECUTABLE.
 */
typedef struct _FuncTest FuncTest;

// CONSTRUCTORS
/** Constructs a new `FuncTest` with given values.
 * @param name Test's name.
 * @param func Function to be executed.
 * @param withValgrind Whether a test using valgrind should be done.
 * @return Pointer to allocated memory or NULL if there is an error.
 *
 * @see puctest_funcTest_construct
 */
extern FuncTest* puctest_funcTest_construct(
	const char* const name,
	const FuncTestFunction func,
	const bool withValgrind
);

// DESTRUCTORS
/** Destructs a `FuncTest`.
 * @param funcTest Pointer to be freed.
 *
 * @see puctest_funcTest_construct
 */
extern void puctest_funcTest_destruct(FuncTest* funcTest);

// GETTERS
/** Retrieves `FuncTest`'s name.
 * @param funcTest Pointer to the `FuncTest`.
 * @return `FuncTest`'s name.
 */
extern const char* puctest_funcTest_getName(const FuncTest* funcTest);

// FUNCTIONS
/** Runs a `FuncTest` by executing its function. It may also reexecutes the
 * tester in another process using a specific path to this test in order to
 * check memory calls.
 * @param funcTest Pointer to the `FuncTest`.
 * @param path Path of selected subtest to execute, like whether to check memory
 * calls, or NULL.
 * @param level Starting indentation level of outputs.
 * @return Whether the test passed.
 */
extern bool puctest_funcTest_run(const FuncTest* funcTest,
	const char* path,
	const unsigned char level
);