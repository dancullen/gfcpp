#!/usr/bin/env bash
# run.sh provides handy commands to set up your development environment, build and deploy the code, run the tests, etc.

set -euf -o pipefail
SCRIPTNAME=${BASH_SOURCE[0]}
SCRIPTDIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
SUCCESS=0
FAILURE=1

DEPDIR=$SCRIPTDIR/deps
BUILDDIR=$SCRIPTDIR/build

do-help()
{
    echo
    echo "Usage: ./run.sh COMMAND [ARG...]"
    echo
    echo "Every do-COMMAND function in this script implements a COMMAND."
    echo "Functions are prefixed with 'do-' to prevent conflict with Bash"
    echo "keywords ('test', 'help', etc.) or other programs (e.g., 'cmake')."
    echo
    echo "Tip: Add this directory to your PATH or define 'alias run=./run.sh'"
    echo "in your bashrc to avoid having to type the leading './' every time."
    echo
    echo "This script is designed for an AMD64/x86-64 Ubuntu 20.04 development machine."
    echo
    echo "See README.md for more instructions."
    echo
    echo "  OSTYPE:              $OSTYPE"
    echo "  PATH:                $PATH"
    echo "  SHELL:               $SHELL"
    echo "  PWD:                 $PWD"
    echo "  SCRIPTNAME:          $SCRIPTNAME"
    echo "  SCRIPTDIR:           $SCRIPTDIR"
    echo "  DEPDIR:              $DEPDIR"
    echo "  BUILDDIR:            $BUILDDIR"
    echo
    echo "Software version: $(git describe --match=DoNotMatchAnyTags --always --abbrev=40 --dirty)"
    echo
    echo "Date and time: $(date +%Y-%m-%d-%H%M)"
    echo
}

do-all()
{
    do-help
}

do-clean()
{
    echo "$SCRIPTNAME: clean: Deleting build directory."
    rm -fr "$BUILDDIR"
}

do-distclean()
{
    echo "$SCRIPTNAME: distclean: Deleting all generated files from Git tree, including both the build and deps directories."
    git clean -d -f -x
}

do-deps()
{
    echo "$SCRIPTNAME: Downloading and install dependencies."

    sudo apt install -y build-essential cmake ninja-build curl git

    mkdir -p $DEPDIR

    cd $DEPDIR
    if test -d Catch2 ; then
        echo "Found Catch2; no need to download."
    else
        git clone https://github.com/catchorg/Catch2.git
        cd Catch2
        git fetch --tags --force
        git checkout 7727c15290ce2d289c1809d0eab3cceb88384ad6
    fi
}

do-cmake()
{
    echo "$SCRIPTNAME: Generating CMake files for amd64."
    mkdir -p "$BUILDDIR"
    cmake -B "$BUILDDIR" -DCMAKE_TOOLCHAIN_FILE=cmake/Toolchain-amd64.cmake -DCMAKE_BUILD_TYPE=Debug -GNinja .
}

do-build()
{
    echo "$SCRIPTNAME: Building unit tests for amd64."
    # Pipe to cat so that each line of Ninja output will persist in to terminal rather than overwritten (Ninja tries to be too cute with ncurses stuff).
    cmake --build "$BUILDDIR" -- -j8 | cat
}

do-tests()
{
    echo "$SCRIPTNAME: Running unit tests on amd64."
    (
        cd "$BUILDDIR"
        ./tests
    )
}

if [ $# -lt 1 ] ; then
    echo "$SCRIPTNAME: Error: No COMMAND given."
    exit $FAILURE
fi
cmd=$1
shift

echo "$SCRIPTNAME: Running: $cmd $@"
do-$cmd "$@"
exit $?
