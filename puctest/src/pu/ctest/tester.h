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

// TYPES
/** Represents a testing system. It contains a bunch of tests and is run by
 * giving a program to test. It may also execute only one test or `TestSuite` if
 * its full path is given.
 */
typedef struct _Tester Tester;

// CONSTRUCTORS
/** Constructs a new `Tester` with given values.
 * @param name `Tester`'s name.
 * @param count `Tester`'s test count.
 * @return Pointer to allocated memory or NULL if there is an error.
 *
 * @see puctest_tester_destruct
 */
extern const Tester* puctest_tester_construct(
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
 */
extern const char* puctest_tester_getName(const Tester* tester);