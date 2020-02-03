
add_library(message_processing
	src/Messaging.cpp
	)

target_include_directories(message_processing
	PUBLIC
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
	)

target_link_libraries(message_processing
	PUBLIC
	json_processing
	user
	)

set_target_properties(message_processing
	PROPERTIES
	LINKER_LANGUAGE CXX
	CXX_STANDARD 17
	)

install(TARGETS message_processing
	ARCHIVE DESTINATION lib
	)

