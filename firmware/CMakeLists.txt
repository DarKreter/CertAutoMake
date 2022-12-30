set(DEPENDENCIES_LIST FilesManagment StringManagment Entertainment Base64 XML)

add_executable(CertAutoMake CertAutoMake.cpp)

target_include_directories(CertAutoMake PUBLIC .)
add_dependencies(CertAutoMake ${DEPENDENCIES_LIST})
target_link_libraries(CertAutoMake PUBLIC ${DEPENDENCIES_LIST})
