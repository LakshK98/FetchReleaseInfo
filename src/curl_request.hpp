#ifndef CURL_REQUEST_HPP
#define CURL_REQUEST_HPP

#include <string>
#include <memory>
#include <curl/curl.h>

class CURLRequest
{
public:
  CURLRequest();
  ~CURLRequest();
  std::string perform(const std::string &url);

private:
  std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl;
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response);
};

#endif // CURL_REQUEST_HPP
