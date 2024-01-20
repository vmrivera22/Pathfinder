#!/bin/bash

source_dir=`dirname ${BASH_SOURCE}`
source "$source_dir/utils.sh"

if [[ `check_dir` -eq 1 ]]; then
    exit 1
fi

touch "original.txt" "error.txt" "output.txt"
original="original.txt"
file="test_files/simple_path.txt"

chmod 777 $original "error.txt" "output.txt"

new_files="$original error.txt output.txt"

cp $file $original

rc=$!
if [[ $rc -ne 0 ]]; then
    echo "Input test file does not exist."
    cleanup $new_files
    exit $rc;
fi

./pathfinder -i $original >> output.txt 2>> error.txt

rc=0
msg=""

expected_paths=2
found_paths="`grep -o -E [1-9]+ output.txt`"

if [[ $expected_paths -ne $found_paths ]]; then
    msg=$"${msg}The number of paths ($found_paths) differed from the expected paths ($expected_paths)."
    rc=1
fi

if [[ $rc -eq 0 ]]; then
    echo "All paths were found Successfully"
else
    echo "--------------------------------------------------------------------------------"
    echo "$msg"
    echo "--------------------------------------------------------------------------------"
    echo "Error:"
    cat error.txt
    echo "--------------------------------------------------------------------------------"
    echo "Input:"
    cat original.txt
    echo "--------------------------------------------------------------------------------"
    echo "STDOUT:"
    cat output.txt
fi

cleanup $new_files

exit $rc