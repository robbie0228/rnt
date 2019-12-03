#!/bin/bash
set -e

if [ "$#" -ne 2 ]; then
	>&2 echo "produceOutputs must take 2 arguments"
	exit 1
fi

# posuite, ./poprogram
for s in $(cat ${1}); do
	if [ -e "tests/$s.args" ]; then
		${2} $(cat "tests/$s.args") < "tests/$s.in" > "tests/$s.out"
	else
		${2} < "tests/$s.in" > "tests/$s.out"
	fi
done
