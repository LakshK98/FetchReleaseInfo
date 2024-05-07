#include "curl_request.hpp"

CURLRequest::CURLRequest() : curl(curl_easy_init(), &curl_easy_cleanup)
{
  curl_global_init(CURL_GLOBAL_ALL);
}

CURLRequest::~CURLRequest()
{
  curl_global_cleanup();
}

std::string CURLRequest::perform(const std::string &url)
{
  if (!curl)
  {
    return "";
  }

  curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, WriteCallback);

  std::string responseData;
  curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &responseData);

  CURLcode res = curl_easy_perform(curl.get());
  if (res != CURLE_OK)
  {
    return "";
  }

  return responseData;
}

size_t CURLRequest::WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response)
{
  size_t totalSize = size * nmemb;
  response->append(static_cast<char *>(contents), totalSize);
  return totalSize;
}