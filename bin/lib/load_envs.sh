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
# Declare a procedure to load properties files and load a .env file. Before
# that, it loads a default.env file to define default values. After, it
# declares dynamic variables : $JAVA_VERSION_SHORT (First line of {@code
# java --version}).
# ------------------------------------------------------------------------------

# Load {@code file} as a definition of project properties. It trims and parses
# its content and declare each constants as global variables.
# @param file Properties file path (Usually with the extension .env).
# @param silent Boolean indicating if the procedure has to be silent. Defaults
# to false.
loadEnvs(){
	if [[ -f $1 ]]; then
		# SAVE EXTGLOB STATUS AND SET IT
		# (See http://mywiki.wooledge.org/glob#extglob)
		shopt -q extglob; EXTGLOB_SETTED=$?
		((EXTGLOB_SETTED)) && shopt -s extglob

		while IFS="=" read -d $'\n' -r var value; do
			spaceTab=$'\t\v'

			var=${var##*([[:space:]])} # Start trim
			var=${var%%*(["$spaceTab"])} # End trim

			value=${value##*(["$spaceTab"])} # Start trim
			value=${value%%*([[:space:]])} # End trim

			# Ignoring empty lines and comments.
			if [[ -z $var || $var = //* ]]; then continue; fi

			if [[ $var = +([[:upper:]_-]) ]]; then
				if [[ $value = *([!$'\r\v\f']) ]]; then
					if [[ $2 = false || -z $2 ]]; then
						declare -grx "$var=$value"
						echo "] LOADED ENV. VAR $var WITH THE VALUE \"$value\"."
					else
						declare -grx "$var=$value" 2>/dev/null
					fi
				elif [[ $2 = false || -z $2 ]]; then
					echo "] INVALID ENV. VAR $var VALUE \"$value\"."
				fi
			elif [[ $2 = false || -z $2 ]]; then
				echo "] INVALID ENV. VAR \"$var\"."
			fi
		done < "$1"

		# RESET EXTGLOB
		((EXTGLOB_SETTED)) && shopt -u extglob
	fi
}

loadEnvs .env
loadEnvs ./bin/etc/default.env true

# DYNAMIC VARIABLES
javaVer="$(java --version)"
declare -rx "JAVA_VERSION_SHORT=${javaVer%%$'\n'*}"