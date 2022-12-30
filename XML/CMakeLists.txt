set(HEADER_LIST inc/XMLfile.hpp)
set(SRC_LIST src/XMLfile.cpp)
set(DEPENDENCIES_LIST FilesManagment StringManagment)

add_library(XML STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(XML PUBLIC . inc src)

add_dependencies(XML ${DEPENDENCIES_LIST})
target_link_libraries(XML PUBLIC ${DEPENDENCIES_LIST})
