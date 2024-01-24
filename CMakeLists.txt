# Copyright (c) 2021-present André Luiz Alvares
# Nene is licensed under the Zlib license.
# Please refer to the LICENSE file for details
# SPDX-License-Identifier: Zlib

# This version should match the interval of nene's root CMakeLists.txt
cmake_minimum_required(VERSION 3.23-3.26)

add_subdirectory(nene)

# Set the project name, version and language
project(
  make-me-laugh-prototype
  VERSION 0.1
  LANGUAGES C
)

# finally, the examples
add_executable(make_me_laugh WIN32 main.c)

target_link_libraries(make_me_laugh PRIVATE nene)
target_compile_options(make_me_laugh PRIVATE -fsanitize=address,undefined)
target_link_options(make_me_laugh PRIVATE -fsanitize=address,undefined)

# set the C standard properties, 
# be sure to follow the same standard of nene (see the src/CMakeLists.txt file)
set_target_properties(make_me_laugh PROPERTIES
  C_STANDARD 99
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO
)
