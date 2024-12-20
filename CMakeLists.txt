################################################################################
#                                                                              #
#  CMAKELISTS.TXT                                                              #
#                                                                              #
#  This is a CMake file for building the TRUST4 command line interface.        #
#  It replicates the TRUST4 Makefile functionality using CMake to pair with    #
#  external repository. It silences all compilation warnings since it is       #
#  designed to be used as a third party utility by a user application.         #
#                                                                              #
#  Revision History:                                                           #
#      12/20/2024  Edward Speer  Initial Revision                              #
#                                                                              #
################################################################################

cmake_minimum_required(VERSION 3.10)

project(TRUST4)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -g")

# Link paths
include_directories(${CMAKE_SOURCE_DIR}/TRUST4/samtools-0.1.19)
link_directories(${CMAKE_SOURCE_DIR}/TRUST4/samtools-0.1.19)

# Libraries to link
set(LINK_LIBS pthread z)

# AddressSanitizer
option(ASAN "Enable AddressSanitizer" OFF)
if(ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address \
                                -ldl -g")
endif()

# Compile TRUST4 programs as linkable libraries
add_library(trust4_lib STATIC trust4_main.cpp)
target_link_libraries(trust4_lib ${LINK_LIBS})
target_compile_options(trust4_lib PRIVATE -w)

add_library(bam-extractor STATIC BamExtractor.cpp)
target_link_libraries(bam-extractor ${LINK_LIBS} bam)
target_compile_options(bam-extractor PRIVATE -w)

add_library(fastq-extractor STATIC FastqExtractor.cpp)
target_link_libraries(fastq-extractor ${LINK_LIBS})
target_compile_options(fastq-extractor PRIVATE -w)

add_library(annotator STATIC Annotator.cpp)
target_link_libraries(annotator ${LINK_LIBS})
target_compile_options(annotator PRIVATE -w)

# Custom command to build samtools if not already built
add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/TRUST4/samtools-0.1.19/libbam.a
    COMMAND make
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/TRUST4/samtools-0.1.19
    COMMENT "Building samtools..."
)

add_custom_target(build_samtools
    DEPENDS ${CMAKE_SOURCE_DIR}/TRUST4/samtools-0.1.19/libbam.a
)

# Make bam-extractor depend on samtools build
add_dependencies(bam-extractor build_samtools)

# Clean target
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/*.o ${CMAKE_BINARY_DIR}/*.gch trust4 bam-extractor annotator fastq-extractor
    COMMENT "Cleaning all build files..."
)
