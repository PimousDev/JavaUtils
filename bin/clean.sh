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
# Removes all output .class files and folders.
#
# @param source Which source output to clean. Either "project" or "test".
# Defaults to "project".
# ------------------------------------------------------------------------------
shopt -s globstar

#shellcheck source=./lib/load_envs.sh
source ./bin/lib/load_envs.sh

# PARAMETERS
outputPath=$PROJECT_OUTPUT
if [[ $1 = "test" ]]; then
	outputPath=$PROJECT_TEST_OUTPUT
elif [[ $1 != "project" ]]; then
	echo "INVALID \"$1\" SOURCE; DEFAULTING TO \"project\""
fi

# DELETION
echo "REMOVING ..."
if [[ -d $outputPath && $(ls -A "$outputPath") ]]; then
	echo "FOUND $(find "$outputPath" -type f | wc -l) file(s) and folder(s)."
	rm -frv "$outputPath"/**/*.*
	rm -dfr "${outputPath:?}"/**/*
	echo "REMOVED."
else
	echo "No such \"$outputPath\" directory or is empty; Aborting."
fi