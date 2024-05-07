cmake_minimum_required(VERSION 3.5)
project(FetchReleaseInfo
        VERSION 0.0.1
        LANGUAGES CXX)

add_executable(FetchReleaseInfoBin src/main.cpp src/curl_request.cpp)

target_compile_features(FetchReleaseInfoBin PRIVATE cxx_std_17)

target_include_directories(FetchReleaseInfoBin PRIVATE src)

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})

target_link_libraries(FetchReleaseInfoBin PRIVATE ${CURL_LIBRARIES})