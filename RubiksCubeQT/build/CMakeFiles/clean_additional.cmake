# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\rubikscubeqt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\rubikscubeqt_autogen.dir\\ParseCache.txt"
  "rubikscubeqt_autogen"
  )
endif()
