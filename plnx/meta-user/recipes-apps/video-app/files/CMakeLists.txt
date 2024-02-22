cmake_minimum_required(VERSION 3.12)

project(video-app)

find_package(PkgConfig)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-video-1.0)

add_executable(${PROJECT_NAME} main.c)

target_include_directories(${PROJECT_NAME} 
	PRIVATE ${GSTREAMER_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
	PRIVATE ${GSTREAMER_LIBRARIES}
	PRIVATE mediactl;v4l2subdev
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
