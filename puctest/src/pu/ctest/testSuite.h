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

#include "test/funcTest.h"

// TYPES
/** Represents a named group of tests, i.e. a test suite, passed by executing
 * all the ones it contains. A group may contain other groups.
 */
typedef struct _TestSuite TestSuite;

/** Enumerates allowed test types */
typedef enum{
	TestType_UNDEFINED,
	TestType_SUITE,
	TestType_FUNC
} TestType;

/** Union of allowed test types as a generic type. */
typedef union{
	const FuncTest *funcTest;
	const TestSuite *testSuite;
} GenericTest;

// CONSTRUCTORS
/** Constructs a new `TestSuite` with given values.
 * @param name Test suite's name.
 * @param count Test suite's size, greater than 0.
 * @return Pointer to allocated memory or NULL if there is an error.
 *
 * @see puctest_testSuite_destruct
 */
extern TestSuite *puctest_testSuite_construct(
	const char *const name,
	const unsigned short count
);

// DESTRUCTORS
/** Destructs a `TestSuite` and all associated tests.
 * @param testSuite Pointer to be freed.
 *
 * @see puctest_testSuite_construct
 */
extern void puctest_testSuite_destruct(TestSuite *testSuite);

// GETTERS
/** Retrieves `TestSuite`'s name.
 * @param testSuite Pointer to the `TestSuite`.
 * @return `TestSuite`'s name.
 */
extern const char *puctest_testSuite_getName(const TestSuite *testSuite);

/** Retrieves `TestSuite`'s test count.
 * @param testSuite Pointer to the `TestSuite`.
 * @return `TestSuite`'s test count.
 */
extern unsigned short puctest_testSuite_getCount(const TestSuite *testSuite);

/** Retrieves `TestSuite`'s `GenericTest` at `index`.
 * @param testSuite Pointer to the `TestSuite`.
 * @param index `GenericTest`'s index.
 * @return `GenericTest` at `index`, or `NULL` if out of bounds.
 */
extern GenericTest puctest_testSuite_getTest(const TestSuite *testSuite,
	const unsigned short index
);
/** Retrieves `TestSuite` test's type at `index`.
 * @param testSuite Pointer to the `TestSuite`.
 * @param index Test's index.
 * @return Test's type at `index`, or `NULL` if out of bounds.
 */
extern TestType puctest_testSuite_getTestType(const TestSuite *testSuite,
	const unsigned short index
);

/** Deeply counts the total number of tests associated to a `TestSuite`. The
 * count is recursive, so it goes deeply into every other `TestSuite`s.
 * @param testSuite Pointer to the `TestSuite`.
 * @return `TestSuite`'s total number of tests.
 *
 * @see puctest_testSuite_getCount
 * @see puctest_tester_getTotalCount
 * @see puctest_funcTest_getTotalCount
 */
extern unsigned int puctest_testSuite_getTotalCount(const TestSuite *testSuite);

// SETTERS
/** Adds a `test` to `testSuite` if there is still enough room for.
 * @param testSuite Pointer to the `TestSuite`.
 * @param type Test's type.
 * @param test Test to add.
 * @return Pointer to the `TestSuite` or `NULL` if the group is full.
 */
extern TestSuite *puctest_testSuite_addTest(TestSuite *testSuite,
	const TestType type,
	const void *test
);

// FUNCTIONS
/** Runs a `TestSuite` by executing all associated tests or selected ones.
 * Specifically, it prints a header and call `puctest_testSuite_test`.
 * @param testSuite Pointer to the `TestSuite`.
 * @param path Path of selected test(s) to execute, or NULL.
 * @param level Starting indentation level of outputs, increased in sub calls.
 * @return Total count of passed tests.
 *
 * @see puctest_testSuite_runTests
 */
extern unsigned int puctest_testSuite_run(const TestSuite *testSuite,
	const char *path,
	const unsigned char level
);

/** Runs only all associated tests or selected ones of a `TestSuite`.
 * @param testSuite Pointer to the `TestSuite`.
 * @param path Path of selected test(s) to execute, or NULL.
 * @param level Starting indentation level of outputs.
 * @return Total count of passed tests.
 *
 * @see puctest_testSuite_run
 */
extern unsigned int puctest_testSuite_runTests(const TestSuite *testSuite,
	const char *path,
	const unsigned char level
);
