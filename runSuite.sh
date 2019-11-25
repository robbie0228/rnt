#!/bin/bash

failed=0

temp="tempfile"
for file in $(cat tests/suite.txt)
do
    if [ -e "tests/$file.args" ]; then
        if [ -e "tests/$file.in" ]; then
            cat "tests/$file.in" | ./raiinet $(cat "tests/$file.args") > $temp
        else
            ./raiinet $(cat "tests/$file.args") > $temp
        fi
    else 
        if [ -e "tests/$file.in" ]; then
            cat "tests/$file.in" | ./raiinet > $temp
        else
            ./raiinet > $temp
        fi
    fi

    if [ ! -e "tests/$file.out" ]; then
        echo "Missing tests/$file.out" >&2
        exit 2
    fi

    cat "tests/$file.out" > /dev/null

    if ! cmp -s $temp "tests/$file.out"; then
        echo "Test failed: tests/$file"
        echo "Args:"
        if [ -e "tests/$file.args" ]; then
            cat "tests/$file.args"
        fi
        echo "Input:"
        if [ -e "tests/$file.in" ]; then
            cat "tests/$file.in"
        fi
        echo "Expected:"
        cat "tests/$file.out"
        echo "Actual:"
        cat $temp
        failed=1
    fi
done

rm $temp

if [ $failed -eq 1 ]; then
    exit 1
else 
    echo "All correct"
fi