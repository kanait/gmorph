cmake_minimum_required(VERSION 3.10)
project(gmorph)

# Enable MFC for Visual Studio
set(CMAKE_MFC_FLAG 2)

set(CMAKE_CXX_STANDARD 14)

# Collect source files
file(GLOB SRC_FILES
    "*.cpp"
    "*.rc"
)
file(GLOB HEADER_FILES
    "*.h"
)

add_executable(gmorph WIN32 ${SRC_FILES} ${HEADER_FILES})
# Define _AFXDLL for MFC application
target_compile_definitions(gmorph PRIVATE _AFXDLL)

# Specify the output directory for PDB files
set_target_properties(gmorph PROPERTIES
    COMPILE_PDB_NAME gmorph
    COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/pdb"
)

# Add include path for Eigen
target_include_directories(gmorph PRIVATE "${CMAKE_SOURCE_DIR}/../external/eigen")

# Link OpenGL library
target_link_libraries(gmorph PRIVATE opengl32)

# Link GLU library
target_link_libraries(gmorph PRIVATE glu32)

# Add libraries or additional settings if necessary
# Example: find_package(OpenGL REQUIRED)
# target_link_libraries(gmorph OpenGL::GL)
