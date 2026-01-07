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
	FuncTest* funcTest;
	TestSuite* testSuite;
} GenericTest;

// CONSTRUCTORS
/** Constructs a new `TestSuite` with given values.
 * @param name Test suite's name.
 * @param count Test suite's size, greater than 0.
 * @return Pointer to allocated memory or NULL if there is an error.
 *
 * @see puctest_testSuite_destruct
 */
extern const TestSuite* puctest_testSuite_construct(
	const char* const name, const unsigned short count
);

// DESTRUCTORS
/** Destructs a `TestSuite` and all associated tests.
 * @param testSuite Pointer to be freed.
 *
 * @see puctest_testSuite_construct
 */
extern void puctest_testSuite_destruct(TestSuite* testSuite);

// GETTERS
/** Retrieves `TestSuite`'s name.
 * @param testSuite Pointer to the `TestSuite`.
 * @return `TestSuite`'s name.
 */
extern const char* puctest_testSuite_getName(const TestSuite* testSuite);
/** Retrieves `TestSuite`'s count.
 * @param testSuite Pointer to the `TestSuite`.
 * @return `TestSuite`'s count.
 */
extern unsigned short puctest_testSuite_getCount(const TestSuite* testSuite);

// SETTERS
/** Adds a `test` to `testSuite` if there is still enough room for.
 * @param testSuite Pointer to the `TestSuite`.
 * @param type Test's type.
 * @param test Test to add.
 * @return Pointer to `testSuite` or `NULL` if the group is full.
 */
extern const TestSuite* puctest_testSuite_addTest(TestSuite* testSuite,
	const TestType type,
	const GenericTest test
);