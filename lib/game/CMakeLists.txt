
add_library(game
  src/Game.cpp
)

find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(game
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${Boost_INCLUDE_DIR}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
   
)

target_link_libraries(game
  PRIVATE
    ${Boost_LIBRARIES}
)

set_target_properties(game
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS game
  ARCHIVE DESTINATION lib
)

