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
# Executes .class files with the current JVM.
#
# @param source Which source to execute. Either "project" or "test". Defaults to
# "project".
# @throw 1 The output folder doesn't exist.
# @throw 2 The JVM returns error(s).
# @throw 3 Cannot change directory to temp folder.
# ------------------------------------------------------------------------------
# TODO: Add jvm choice.

#shellcheck source=./lib/load_envs.sh
source ./bin/lib/load_envs.sh
source ./bin/lib/array.sh

# PARAMETERS
outputPath=$PROJECT_OUTPUT
tmpPath=$PROJECT_SOURCE_TEMP
mainClass=$MAIN_CLASS
if [[ $1 = "test" ]]; then
	outputPath=$PROJECT_TEST_OUTPUT
	tmpPath=$PROJECT_TEST_TEMP
	classPaths+=("$PROJECT_OUTPUT")
	mainClass=$MAIN_TEST_CLASS
elif [[ $1 != "project" ]]; then
	echo "INVALID \"$1\" SOURCE; DEFAULTING TO \"project\""
fi

# EXECUTION
echo "EXECUTING WITH $JAVA_VERSION_SHORT ..."
if [[ -d $outputPath ]]; then
	# Reverse temp path
	mkdir -p "$tmpPath"
	
	reversePath=""
	cd "$tmpPath" || exit 3
	while test ! -d "$outputPath"; do
		reversePath=$reversePath"../"
		cd ../
	done

	# Resolve paths
	outputPath=$reversePath$outputPath
	classPaths=("${classPaths[@]/#/$reversePath}")

	# Arguments
	args="-cp $(arrayJoin ':' "$outputPath" "${classPaths[@]}") $mainClass"

	# Executing
	if (cd "$tmpPath"; eval "$JAVA_SHELL $JAVA_FLAGS $args"); then
		echo "TERMINATED."
	else
		exit 2
	fi
else
	echo "No \"$outputPath\" directory; Cannot execute."
	exit 1
fi