// cloud_image_release_info_provider.hpp
#ifndef CLOUD_IMAGE_INFO_PROVIDER_HPP
#define CLOUD_IMAGE_INFO_PROVIDER_HPP

#include "release_info_provider.hpp"
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class CloudImageReleaseInfoProvider : public ReleaseInfoProvider
{

private:
  std::string jsonData;
  json products;
  void getProducts();
  void applyArchFilter(const std::string arch);
  json productArchFilter(json products, const std::string &arch);

public:
  CloudImageReleaseInfoProvider(std::string url, const std::string arch);
  std::vector<std::string> getSupportedReleases() override;
  std::string getCurrentLTSVersion() override;
  std::string getDiskImageSha256ForRelease(const std::string &release) override;
};

#endif // CLOUD_IMAGE_RELEASE_INFO_PROVIDER_HPP