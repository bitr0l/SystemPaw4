#
# Copyright (c) 2026, Chloe M., et al.
# Provided under the BSD-3 clause
#

MAKE=make

#
# Check if a list of deps are installed on the host system
#
# $@:  Dep list to check
#
check_deps() {
    for dep in $@
    do
        printf "Checking if %s is installed... " $dep
        which $dep &>/dev/null
        if [ $? -ne 0 ]
        then
            echo "no"
            echo "fatal: Please install '$dep'!"
            exit 1
        fi

        echo "yes"
    done
}

#
# Prepare the build environment
#
build_prep() {
    check_deps     \
        xorriso    \
        git        \
        make       \
        rsync      \
        clang

    pushd src/
        source env/build.env
    popd

    mkdir -p out
}

#
# Build a directory with MAKE
#
# $1: Directory to build
#
make_dir() {
    pushd $1
        $MAKE
    popd
}

#
# Begin the build process
#
build() {
    make_dir            \
        src/paw/stos
    make_dir            \
        src/paw/boot
}

build_prep
build
