cmake_minimum_required(VERSION 3.5)
project(FetchReleaseInfo
        VERSION 0.0.1
        LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  nlohmann_json
  URL https://github.com/nlohmann/json/archive/v3.11.3.tar.gz
)

FetchContent_MakeAvailable(nlohmann_json)

set(SRCS
    src/main.cpp
    src/cloud_image_info_provider.cpp
    src/curl_request.cpp
)
add_executable(FetchReleaseInfoBin ${SRCS})

target_compile_features(FetchReleaseInfoBin PRIVATE cxx_std_17)

target_include_directories(FetchReleaseInfoBin PRIVATE src)

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})

target_link_libraries(FetchReleaseInfoBin PRIVATE ${CURL_LIBRARIES})

target_link_libraries(FetchReleaseInfoBin PRIVATE nlohmann_json::nlohmann_json)