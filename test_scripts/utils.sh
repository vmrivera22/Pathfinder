cleanup() {
    for file in $@; do
        rm -r $file
    done
}

check_dir() {
    if [ ! -f pathfinder ]; then
        echo "Could not find pathfinder binary file."
        return 1
    fi
}