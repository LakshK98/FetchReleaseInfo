// release_info_provider.hpp
#ifndef RELEASE_INFO_PROVIDER_HPP
#define RELEASE_INFO_PROVIDER_HPP

#include <string>
#include <vector>

class ReleaseInfoProvider {
  public:
    virtual std::vector<std::string> getSupportedReleases() = 0;
    virtual std::string getCurrentLTSVersion() = 0;
    virtual std::string getDiskImageSha256ForRelease(const std::string& release) = 0;
    virtual ~ReleaseInfoProvider() {}
};

#endif // RELEASE_INFO_PROVIDER_HPP
