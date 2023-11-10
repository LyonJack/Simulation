cmake_minimum_required(VERSION 3.5)

IF(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   /MD")	# Debug		 编译条件
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")	# Release	 编译条件
ENDIF()

# 添加子项目
add_subdirectory (Utils)	    # 公共模块
add_subdirectory (business)	    # 业务模块
add_subdirectory (App)          # App
