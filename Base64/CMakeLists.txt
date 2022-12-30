set(HEADER_LIST inc/cdecode.hpp inc/cencode.hpp inc/decode.hpp inc/encode.hpp)
set(SRC_LIST src/cdecode.cpp src/cencode.cpp)

add_library(Base64 STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(Base64 PUBLIC . inc src)
