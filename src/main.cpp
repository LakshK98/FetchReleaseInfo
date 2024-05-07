#include <iostream>
#include "cloud_image_info_provider.hpp"
#include <string>

const std::string releaseUrl = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";

int main()
{
  //testing interface
  std::unique_ptr<ReleaseInfoProvider> releaseInfoProvider(new CloudImageReleaseInfoProvider(releaseUrl, "amd64"));
  std::cout << releaseInfoProvider->getCurrentLTSVersion() << std::endl;
  std::cout << releaseInfoProvider->getDiskImageSha256ForRelease("14.04") << std::endl;
  std::cout << releaseInfoProvider->getSupportedReleases().size() << std::endl;
  return 0;
}
