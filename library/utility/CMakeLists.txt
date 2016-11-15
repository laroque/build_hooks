# CMakeLists.txt for Scarab/library/utility
# Author: N. Oblath
# Created: Jan 1, 2016

set( dir ${CMAKE_CURRENT_SOURCE_DIR} )

set( Scarab_HEADERS ${Scarab_HEADERS}
    ${dir}/cancelable.hh
    ${dir}/concurrent_queue.hh
    ${dir}/destroyer.hh
    ${dir}/digital.hh
    ${dir}/error.hh
    ${dir}/factory.hh
    ${dir}/lock_guard.hh
    ${dir}/member_variables.hh
    ${dir}/mutex.hh
    ${dir}/path.hh
    ${dir}/scarab_api.hh
    ${dir}/scarab_version.hh
    ${dir}/singleton.hh
    ${dir}/time.hh
    ${dir}/typename.hh
    PARENT_SCOPE )

set( Scarab_SOURCES ${Scarab_SOURCES}
    ${dir}/cancelable.cc
    ${dir}/digital.cc
    ${dir}/error.cc
    ${dir}/lock_guard.cc
    ${dir}/mutex.cc
    ${dir}/path.cc
    ${dir}/time.cc
    ${dir}/typename.cc
)

configure_file( ${dir}/scarab_version.cc.in ${CMAKE_CURRENT_BINARY_DIR}/scarab_version.cc )
set( Scarab_SOURCES
    ${Scarab_SOURCES}
    ${CMAKE_CURRENT_BINARY_DIR}/scarab_version.cc
    PARENT_SCOPE )
    