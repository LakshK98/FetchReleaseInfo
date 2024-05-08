#include "cloud_image_info_provider.hpp"
#include "curl_request.hpp"
#include <iostream>

CloudImageReleaseInfoProvider::CloudImageReleaseInfoProvider(const std::string url, const std::string arch)
{
  try
  {
    CURLRequest request;
    jsonData = request.perform(url);
    getProducts();
    applyArchFilter(arch);
  }
  catch (const std::exception &e)
  {
    throw std::runtime_error("Initialization failed");
  }
}

void CloudImageReleaseInfoProvider::applyArchFilter(const std::string arch)
{
  for (auto it = products.begin(); it != products.end();)
  {
    if (!it.value().contains("arch") || it.value()["arch"] != arch)
    {
      it = products.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

void CloudImageReleaseInfoProvider::getProducts()
{
  try
  {
    products = json::parse(jsonData);
    if (products.contains("products"))
    {
      products = products["products"];
    }
    else
    {
      products = {};
    }
  }
  catch (json::parse_error &e)
  {
    std::cerr << "JSON parse error: " << e.what() << std::endl;
    throw;
  }
}

std::vector<std::string> CloudImageReleaseInfoProvider::getSupportedReleases()
{
  std::vector<std::string> releaseList;
  for (const auto &[prodKey, prod] : products.items())
  {
    if (prod.contains("supported") && prod["supported"])
    {
      releaseList.push_back(prodKey);
    }
  }
  return releaseList;
}

std::string CloudImageReleaseInfoProvider::getCurrentLTSVersion()
{
  std::string currentVersionStr;
  float currentVersion = 0;

  for (const auto &[key, value] : products.items())
  {
    if (value.contains("release_title"))
    {
      std::string releaseString = value["release_title"];
      if (releaseString.size() >= 3 && releaseString.substr(releaseString.size() - 3) == "LTS")
      {
        float version = std::stof(value["version"].get<std::string>());
        if (version > currentVersion)
        {
          currentVersion = version;
          currentVersionStr = value["version"];
        }
      }
    }
  }
  return currentVersionStr;
}

std::string CloudImageReleaseInfoProvider::getDiskImageSha256ForRelease(const std::string &release)
{
  std::string shaString;

  for (const auto &[prodKey, prodInfo] : products.items())
  {
    if (prodInfo.contains("version") && prodInfo["version"] == release && prodInfo.contains("versions"))
    {
      auto latestVersion = prodInfo["versions"].rbegin().key();
      if (prodInfo["versions"][latestVersion].contains("items") &&
          prodInfo["versions"][latestVersion]["items"].contains("disk1.img") &&
          prodInfo["versions"][latestVersion]["items"]["disk1.img"].contains("sha256"))
      {
        shaString = prodInfo["versions"][latestVersion]["items"]["disk1.img"]["sha256"];
      }
    }
  }
  return shaString;
}