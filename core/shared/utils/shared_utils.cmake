# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

set (UTILS_SHARED_DIR ${CMAKE_CURRENT_LIST_DIR})

include_directories(${UTILS_SHARED_DIR})
<<<<<<< HEAD
include_directories(${UTILS_SHARED_DIR}/../include)


file (GLOB_RECURSE source_all ${UTILS_SHARED_DIR}/*.c)
=======

file (GLOB source_all ${UTILS_SHARED_DIR}/*.c)
>>>>>>> intel/internal/feature

set (UTILS_SHARED_SOURCE ${source_all})

LIST (APPEND RUNTIME_LIB_HEADER_LIST "${UTILS_SHARED_DIR}/runtime_timer.h")
