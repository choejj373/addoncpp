cmake_minimum_required(VERSION 2.8.12.2)
set (CMAKE_CXX_STANDARD 11)



# 프로젝트의 이름입니다.
# 이 예제에서는 my_addon.node라는 이름으로 DLL이 생성됩니다.
project (my_addon)
include_directories(${CMAKE_JS_INC})



# 타겟 소스파일을 지정합니다.
file(GLOB SOURCE_FILES "hello_world.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})



# N-API 래퍼를 불러옵니다.
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})



# N-API 버전을 설정합니다.
# 이후버전은 이전버전도 지원하니 최신버전으로 설정해주세요.
# 2020년 3월 기준으로 5가 최신입니다.
#
# (2020-03-13 수정)
# 이전버전은 이후버전에서 안정적으로 동작하므로,
# 안정성을 원한다면 낮은 버전이 더 좋은 선택일 수 있습니다.
# 단 1, 2는 초창기에 사용된 실험용 버전이므로 사용하면 안됩니다.
add_definitions(-DNAPI_VERSION=3)