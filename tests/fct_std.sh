#!/usr/bin/env bash

EOC="\e[0m"
BOLD="\e[1m"
RED="\e[91m"
GREEN="\e[92m"
YELLOW="\e[93m"
DBLUE="\e[94m"
PURPLE="\e[95m"
CYAN="\e[96m"
DGREY="\e[1;90m"

include_path="../"
srcs="srcs"

CC="clang++"
CFLAGS="-Wall -Wextra -Werror -std=c++98"
# CFLAGS+=" -fsanitize=address -g3"

ft_compile_output="/dev/null"
std_compile_output="/dev/null"

function pheader () {
printf "${EOC}${BOLD}${DBLUE}\
# ****************************************************************************** #
#                                                                                #
#                                :::   :::   :::                                 #
#                              :+:+: :+:+:  :+: :+:                              #
#                            +:+ +:+:+ +:+ +:+                                   #
#                           +#+  +:+  +#+ +#+ +#+                                #
#                          +#+       +#+ +#+ #+#                                 #
#                         #+#       #+# #+# #+#                                  #
#                        ###       ### ### ###  containers_test                  #
#                                                                                #
# ****************************************************************************** #
${EOC}"
}

compile () {
	# 1=file 2=define used {ft/std} 3=output_file 4?=compile_log
	macro_name=$(echo "USING_${2}" | awk '{ print toupper($0) }')
	compile_cmd="$CC $CFLAGS -o ${3} -I./$include_path -D ${macro_name} ${1}"
	if [ -n "$4" ]; then
		compile_cmd+=" &>${4}"
	fi
	eval "${compile_cmd}"
	return $?
}

cmp_one () {
	# 1=path/to/file

	deepdir="deepthought"; logdir="logs"
	mkdir -p $deepdir $logdir
	container=$(echo $1 | cut -d "/" -f 2)
	file=$(echo $1 | cut -d "/" -f 3)
	testname=$(echo $file | cut -d "." -f 1)
	ft_bin="ft.$container.out"; ft_log="$logdir/ft.$testname.$container.log"
	std_bin="std.$container.out"; std_log="$logdir/std.$testname.$container.log"
	diff_file="$deepdir/$testname.$container.diff"

	clean_trailing_files () {
		rm -f $ft_bin $std_bin
		[ -s "$diff_file" ] || rm -f $diff_file $ft_log $std_log &>/dev/null
		rmdir $deepdir $logdir &>/dev/null
	}

	compile "$1" "std"  "$ft_bin"  $ft_compile_output; ft_ret=$?
	compile "$1" "std" "$std_bin" $std_compile_output; std_ret=$?
}

do_test () {
	# 1=container_name
	test_files=$(find "${srcs}/${1}" -type f -name '*.cpp' | sort)

	for file in ${test_files[@]}; do
		cmp_one "${file}"
	done
}

function main () {
	pheader
	containers=(vector map stack set)
	# containers=(vector list map stack queue deque multimap set multiset)
	if [ $# -ne 0 ]; then
		containers=($@);
	fi

	for container in ${containers[@]}; do
		printf "%40s\n" $container
		do_test $container 2>/dev/null
	done
}
