#!/bin/sh


TEST_SRC=./src
MAIN_SRC=../src
BC=bc
CALC=$MAIN_SRC/calc
BUILD=$TEST_SRC/build
COMP=$TEST_SRC/comp


if test "x$1" == "x-h"
then
	echo "usage: $0 [option]"
	echo "option: -h  Print this messsage"
	echo "        xx  where xx is number of tests executed"
	exit
fi

echo
echo "Building environment"
echo
make -C ../src all || exit $?
make -C src all    || exit $?

echo
echo "Testing correctness of calculating programs, bc and calc."
echo

TEST_NUM=100
if test $# -ge 1 && test "$1" -gt 0 2>/dev/null
then
	TEST_NUM=$1
fi

set -- "" "simple expressions" "-f" "expressions with math functions" \
	"-v" "expressions with variables"

while [ $# -gt 1 ]; do
	echo
	echo "Testing $2..."
	echo
	j=0
	while test $j -lt $TEST_NUM; do
		j=`expr $j + 1`
		printf "%04d/%04d: " $j $TEST_NUM

		"$BUILD" $1 > test.txt
		"$CALC" -v -q < testcalc > cal1
		"$BC" -l < testbc | \
			perl -pe '$_ = substr $_, 0, -2 if m/\\\n$/' > cal2

		if "$COMP" cal1 cal2; then
			echo ok.
		else
			exit 1
		fi
	done

	shift 2
done
