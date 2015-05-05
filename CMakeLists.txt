cmake_minimum_required(VERSION 3.2)
project(hidapi-test)

################ hidapi

set(HIDAPI_ROOT ${CMAKE_BINARY_DIR}/thirdparty/hidapi)
set(HIDAPI_LIB_DIR ${HIDAPI_ROOT}/bin/lib)
set(HIDAPI_INCLUDE_DIR ${HIDAPI_ROOT}/bin/include)

include(ExternalProject)

ExternalProject_Add(hidapi_external
                    PREFIX ${HIDAPI_ROOT}
                    GIT_REPOSITORY "https://github.com/signal11/hidapi.git"
                    GIT_TAG "40cf516139b5b61e30d9403a48db23d8f915f52c"
                    UPDATE_COMMAND ""
                    PATCH_COMMAND ""
                    BINARY_DIR ${HIDAPI_ROOT}/src/hidapi
                    SOURCE_DIR ${HIDAPI_ROOT}/src/hidapi
                    INSTALL_DIR ${HIDAPI_ROOT}/bin
                    CONFIGURE_COMMAND ./configure --prefix=<INSTALL_DIR>
                    BUILD_COMMAND make
                    BUILD_BYPRODUCTS ${HIDAPI_LIB_DIR}/libhidapi.a)

# hidapi requires an initial execution of "./bootstrap" to run autoreconf
ExternalProject_Add_Step(hidapi_external
                         bootstrap
                         COMMAND ./bootstrap
                         DEPENDEES download
                         DEPENDERS configure
                         WORKING_DIRECTORY ${HIDAPI_ROOT}/src/hidapi)

add_library(libhidapi STATIC IMPORTED)
set_target_properties(libhidapi PROPERTIES IMPORTED_LOCATION ${HIDAPI_LIB_DIR}/libhidapi.a)
add_dependencies(libhidapi hidapi_external)

################ test app

include_directories(${HIDAPI_INCLUDE_DIR})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework IOKit -framework CoreFoundation")
add_executable(hidapi-test src/main.cpp)
target_link_libraries(hidapi-test libhidapi)

