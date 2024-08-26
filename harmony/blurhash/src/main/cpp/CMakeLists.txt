cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE on)

file(GLOB rnoh_blurhash_SRC CONFIGURE_DEPENDS
*.cpp
)
add_library(rnoh_blurhash SHARED ${rnoh_blurhash_SRC})
target_include_directories(rnoh_blurhash PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(rnoh_blurhash PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/openssl/include)

target_link_libraries(rnoh_blurhash PUBLIC rnoh)
target_link_libraries(rnoh_blurhash PUBLIC libohfileuri.so)
#target_link_libraries(rnoh_blurhash PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/openssl/lib/libcrypto.a)
