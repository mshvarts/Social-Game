
find_package(Boost 1.66 COMPONENTS system REQUIRED)

add_executable(gameserver
  gameserver.cpp
)

set_target_properties(gameserver
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Threads REQUIRED)

target_include_directories(gameserver
	PRIVATE
	${Boost_INCLUDE_DIR}
)

target_link_libraries(gameserver
  networking
  game
  user
  server_engine
  parser
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
)

install(TARGETS gameserver
  RUNTIME DESTINATION bin
)

