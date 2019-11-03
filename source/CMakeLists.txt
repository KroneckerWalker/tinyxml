message("Message from source")
aux_source_directory(. DIR_LIB_SRCS)
#include_directories(${CMAKE_CURRNET_SOURCE_DIR}/include)
add_library(tinyxml STATIC ${DIR_LIB_SRCS})

