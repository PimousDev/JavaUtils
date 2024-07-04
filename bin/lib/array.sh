#!/bin/bash
# Java Utils (Build tools and Utility librairies/classes)  
# Copyright &copy; 2024 - Pimous Dev. (https://www.pimous.dev/)
# 
# These programs is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by the
# Free Software Foundation, either version 3 of the License, or (at your option)
# any later version.
# 
# The latters are distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
# details.
# 
# You should have received a copy of the GNU General Public License and the GNU
# Lesser General Public License along with the programs (COPYING &
# COPYING.LESSER). If not, see https://www.gnu.org/licenses/.
# ------------------------------------------------------------------------------
# Gives some utilities about bash arrays.
# ------------------------------------------------------------------------------

# Join each elements of an {@code array} separated by a string.
# @param 1 String that separates each elements.
# @param 2-n Elements to join.
arrayJoin(){
	sep=$1
	str=$2
	if shift 2; then
		str=$str$(printf %s "${@/#/"$sep"}")
	fi
	echo "$str"
}