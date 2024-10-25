# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from src.pro.

target_include_directories(QsLog PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/oauth
    ${CMAKE_CURRENT_SOURCE_DIR}/oauth/private
)

add_subdirectory(oauth)
