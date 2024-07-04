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
# Compiles .java files with the current java compiler. It shows everything
# including deprecated APIs used in the code.
#
# @param source Which source to compile. Either "project" or "test". Defaults to
# "project".
# @throw 1 The source folder doesn't exist or is empty.
# @throw 2 The java compiler returns error(s).
# ------------------------------------------------------------------------------
# TODO: Add java compiler choice.

#shellcheck source=./lib/load_envs.sh
source ./bin/lib/load_envs.sh
source ./bin/lib/array.sh
shopt -s globstar

# PARAMETERS
sourcePath=$PROJECT_SOURCE
outputPath=$PROJECT_OUTPUT
if [[ $1 = "test" ]]; then
	classPaths+=("$PROJECT_OUTPUT")
	sourcePath=$PROJECT_TEST
	outputPath=$PROJECT_TEST_OUTPUT
elif [[ $1 != "project" ]]; then
	echo "INVALID \"$1\" SOURCE; DEFAULTING TO \"project\""
fi

# COMPILATION
echo "COMPILING WITH $JAVA_VERSION_SHORT ..."
if [[ -d $sourcePath && $(ls -A "$sourcePath") ]]; then
	echo "FOUND $(find "$sourcePath"/**/*.java | wc -l) java file(s)."

	# Args
	args="-deprecation -d $outputPath $sourcePath/**/*.java"
	if [[ ${#classPaths[@]} -gt 0 ]]; then
		args="-cp $(arrayJoin ':' "${classPaths[@]}") $args"
	fi

	if eval "javac $args"; then
		echo "COMPILED $(find "$outputPath"/**/*.class | wc -l) java file(s)."
	else
		exit 2
	fi
else
	echo "No \"$sourcePath\" directory or is empty; Cannot compile."
	exit 1
fi