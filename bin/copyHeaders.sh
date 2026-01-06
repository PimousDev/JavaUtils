# Project Utils (Tools and Utility librairies/classes)
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
# @throw 1 Unkown error.
# @throw 2 Bad usage.
# @throw 3 No such file or directory.
# ------------------------------------------------------------------------------

# ---
printError(){
	echo "copyHeaders: $1" 1>&2
	return "${2:-1}"
}
printUsage(){
	echo "Usage: copyHeaders <src> <dest>" 1>&2
	return 2
}

# ---
_main(){
	if [[ $# -ne 2 ]]; then
		printUsage
		return
	fi

	src=$1
	if [[ ! -d $src ]]; then
	    printError "No such source directory ($src);" 3
	    return
	fi

	dest=$2
	if [[ ! -d $dest ]]; then
		printError "No such destination directory ($dest);" 3
		return
	fi
	dest=$(realpath -s "$dest" --relative-to="$src")

	# ---
	cd "$src" || return 1

	if [[ $(find "$dest" | wc -l) -eq 0 ]]; then
		rm -r "${dest:?}"/*
	fi
	find . -name "*.h" -and ! \( -name "*.inc.h" \) \
		-exec cp {} "$dest" --parents \;

	cd - 1>/dev/null || return 1
	#---

	return
}

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
	_main "$@"
fi