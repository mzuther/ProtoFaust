#! /usr/bin/env bash

#  ----------------------------------------------------------------------------
#
#  ProtoFaust
#  ==========
#  DSP prototyping in Faust for VCV Rack
#
#  Copyright (c) 2019-2020 Martin Zuther (http://www.mzuther.de/) and
#  contributors
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#  Thank you for using free software!
#
#  ----------------------------------------------------------------------------


###############################################################################
#
#  WARNING: this file is auto-generated, please do not edit!
#
###############################################################################

project_home=$(pwd)/..


function lint_file
{
    filename="$1"
    dirname=$(dirname "$1")
    project_home="$2"

    printf "%s\n" "$filename"

    clang \
        -x c++ - \
        -include "$project_home/src/Amalgamated.hpp" \
        -I "$project_home/../Rack-SDK/dep/include" \
        -I "$project_home/../Rack-SDK/include" \
        -I "$dirname" \
        -fsyntax-only \
        -fno-caret-diagnostics \
        -fcolor-diagnostics \
        -std=c++14 \
        -Wall \
        < "$filename"

    cppcheck \
        --template=gcc \
        --enable=style \
        --inline-suppr \
        --language=c++ \
        --force \
        --quiet \
        "$filename" 2>&1 | \
    sed -Ee 's/[^:]+://' | \
    GREP_COLORS="mt=01;31" grep --extended-regexp --colour=always \
                                --label "$filename" --with-filename \
               '[^0-9:].*'

    # find error-like codetags
    GREP_COLORS="mt=01;31" grep --extended-regexp --colour=always \
                                --with-filename --line-number \
               '\<(BUG|FIXME|XXX)\>' \
               "$filename"

    # find warning-like codetags
    GREP_COLORS="mt=01;33" grep --extended-regexp --colour=always \
                                --with-filename --line-number \
               '\<(HACK|TODO|@todo)\>' \
               "$filename"
}


export -f lint_file
printf "\n"

find . -maxdepth 1 \( -iname "*.cpp" -or -iname "*.hpp" \) \
                   ! -name "Amalgamated.hpp" \
                   ! -name "faust_generated.cpp" -print | \
    sort | \
    parallel --will-cite --group \
             lint_file {} "$project_home"

printf "\n"
