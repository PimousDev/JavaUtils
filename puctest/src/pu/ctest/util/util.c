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

#include <limits.h>

#include "util.inc.h"

// VARIABLES
const char* const PUCTEST_PASSED_FORMAT = "\x1B[1;38;5;2mPASSED\x1B[0m";
const char* const PUCTEST_FAILED_FORMAT = "\x1B[1;38;5;1mFAILED\x1B[0m";

// FUNCTIONS
const char* puctest_util_chrRep(
	const char character, const unsigned char count
){
	static char repetition[UCHAR_MAX + 1];

	for(unsigned char i = 0; i < count; i++)
		repetition[i] = character;

	repetition[count] = '\0';
	return (const char*) &repetition;
}