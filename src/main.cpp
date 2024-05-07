#include <iostream>
#include "cloud_image_info_provider.hpp"
#include "command_parser.hpp"
#include <string>

const std::string releaseUrl = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";

void processGetSupportedReleaseCommand(std::unique_ptr<ReleaseInfoProvider> &provider)
{
  std::vector<std::string> supportedReleases = provider->getSupportedReleases();

  std::cout << "Supported Releases:" << std::endl;
  if (!supportedReleases.empty())
  {
    for (const auto &release : supportedReleases)
    {
      std::cout << release << std::endl;
    }
  }
  else
  {
    std::cout << "No supported releases" << std::endl;
  }
}

void processCurrentLTSCommand(std::unique_ptr<ReleaseInfoProvider> &provider)
{
  std::string currentLTSVersion = provider->getCurrentLTSVersion();
  if (!currentLTSVersion.empty())
  {
    std::cout << "Current LTS Version: " << currentLTSVersion << std::endl;
  }
  else
  {
    std::cout << "Unable to retrieve current LTS version." << std::endl;
  }
}

void processGetDiskImageCommand(std::unique_ptr<ReleaseInfoProvider> &provider, std::string release)
{
  // TODO: Move option name to CommandParser
  std::string sha256 = provider->getDiskImageSha256ForRelease(release);
  if (!sha256.empty())
  {
    std::cout << "SHA256 of disk1.img in release " << release << ": " << sha256 << std::endl;
  }
  else
  {
    std::cerr << "Error: Unable to retrieve SHA256 for release " << release << "." << std::endl;
  }
}

int main(int argc, char *argv[])
{
  try
  {

    CommandParser cmd(argc, argv);
    std::unique_ptr<ReleaseInfoProvider> releaseInfoProvider(new CloudImageReleaseInfoProvider(releaseUrl, "amd64"));

    switch (cmd.getSelectedCommand())
    {
    case Command::SUPPORTED_RELEASES:
      processGetSupportedReleaseCommand(releaseInfoProvider);
      break;

    case Command::CURRENT_LTS_VERSION:
      processCurrentLTSCommand(releaseInfoProvider);
      break;

    case Command::DISK_IMAGE_SHA256_FOR_RELEASE:
      processGetDiskImageCommand(releaseInfoProvider, cmd.getOptions("release"));
      break;
    default:
      break;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error occured: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
