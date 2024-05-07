#include <iostream>
#include "curl_request.hpp"
#include <string>

const std::string releaseUrl = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";

int main()
{
  CURLRequest request;

  std::string responseData = request.perform(releaseUrl);

  if (responseData.empty())
  {
    std::cerr << "error in curl." << std::endl;
    return 1;
  }

  std::cout << "response: " << responseData << std::endl;
  return 0;
}
