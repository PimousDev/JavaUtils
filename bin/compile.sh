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
javaCount=$(find "$sourcePath" -name "*.java" -type f 2>/dev/null | wc -l)
if [[ -d $sourcePath && $javaCount -gt 0 ]]; then
	resCount=$(find "$PROJECT_RESOURCE"/* 2>/dev/null | wc -l)
	echo "FOUND $javaCount java file(s) and $resCount resource file(s)."

	# Arguments
	args="-deprecation -d $outputPath $sourcePath/**/*.java"
	if [[ ${#classPaths[@]} -gt 0 ]]; then
		args="-cp $(arrayJoin ':' "${classPaths[@]}") $args"
	fi

	# Compiling
	if eval "javac $args"; then
		classCount=$(find "$outputPath" -name "*.class" -type f | wc -l)
		echo "COMPILED $classCount java file(s)."
	else
		exit 2
	fi

	# Copy project resources
	if [[ -d $PROJECT_RESOURCE \
		&& $(ls -A "$PROJECT_RESOURCE") \
		&& ! $(cp -r "$PROJECT_RESOURCE"/. "$PROJECT_OUTPUT") \
	]]; then
		resCount=$(find "$PROJECT_OUTPUT" ! -name "*.class" -type f | wc -l)
		echo "COPIED $resCount resource file(s)."
	fi
else
	echo "No such \"$sourcePath\" directory or does not contains files; Cannot compile."
	exit 1
fi 