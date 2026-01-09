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

#include "testSuite.h"

// TYPES
/** Represents a testing system. It contains a bunch of tests and is run by
 * giving a program to test. It may also execute only one test or `TestSuite` if
 * its full path is given.
 */
typedef struct _Tester Tester;

// CONSTRUCTORS
/** Constructs a new `Tester` with given values.
 * @param name `Tester`'s name.
 * @param count `Tester` top-level tests' count.
 * @return Pointer to allocated memory or NULL if there is an error.
 *
 * @see puctest_tester_destruct
 */
extern Tester* puctest_tester_construct(
	const char* const name,
	const unsigned short count
);

// DESTRUCTORS
/** Destructs a `Tester` and all associated tests.
 * @param tester Pointer to the `Tester`.
 *
 * @see puctest_tester_construct
 */
extern void puctest_tester_destruct(Tester* tester);

// GETTERS
/** Retrieves `Tester`'s name.
 * @param tester Pointer to the `Tester`.
 * @return `Tester`'s name.
*/
extern const char* puctest_tester_getName(const Tester* tester);
/** Retrieves `Tester`'s top-level test count.
 * @param tester Pointer to the `TestSuite`.
 * @return `Tester`'s top-level test count.
 */
extern unsigned short puctest_tester_getCount(const Tester* tester);

/** Counts deeply the total number of tests associated to a `Tester`. The count
 * is recursive, so it goes deeply into every `TestSuite`s.
 * @param tester Pointer to the `Tester`.
 * @return `Tester`'s total number of tests.
 *
 * @see puctest_tester_getCount
 * @see puctest_testSuite_getTotalCount
 * @see puctest_funcTest_getTotalCount
 */
extern unsigned int puctest_tester_getTotalCount(const Tester* tester);

// SETTERS
/** Adds a `test` to `Tester` top-level tests if there is still enough room for.
 * @param tester Pointer to the `Tester`.
 * @param type Test's type.
 * @param test Test to add.
 * @return Pointer to the `Tester` or `NULL` if the group is full.
 */
extern Tester* puctest_tester_addTest(Tester* tester,
	const TestType type,
	const void* test
);

// FUNCTIONS
/** Runs a `Tester` by executing all associated tests or selected ones.
 * Specifically, it prints a header and call `puctest_testSuite_runTests`.
 * @param tester Pointer to the `Tester`.
 * @param path Path of selected test(s) to execute, or NULL.
 * @return Total count of passed tests.
 */
extern unsigned int puctest_tester_run(const Tester* tester,
	const char* path
);