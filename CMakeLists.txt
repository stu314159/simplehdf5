cmake_minimum_required (VERSION 3.5)
project (hdf5_testing VERSION 0.1
               LANGUAGES CXX)

find_package(MPI REQUIRED)
find_package(HDF5 REQUIRED COMPONENTS CXX)


#[==[
this is a multi-line comment put here for the hell of it.
so, here is a second line of comments...
#]==]

#include_directories ("${PROJECT_SOURCE_DIR}/include")

add_executable(h5test src/h5test.cpp)

target_compile_options(h5test PUBLIC -Wall -Wextra -Wpedantic -std=c++11)
target_include_directories(h5test PUBLIC include
	                            PRIVATE src ${MPI_CXX_INCLUDE_PATH} ${HDF5_INCLUDE_DIRS})

target_link_libraries(h5test ${MPI_CXX_LIBRARIES} ${HDF5_CXX_LIBRARIES} ${HDF5_LIBRARIES})

 
