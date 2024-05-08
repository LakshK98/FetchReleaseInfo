#include "command_parser.hpp"

CommandParser::CommandParser(int argc, char *argv[])
{
  parseCommands(argc, argv);
}

void CommandParser::parseCommands(int argc, char *argv[])
{
  if (argc >= 2)
  {
    selectedCommand = stringToCommand(argv[1]);
    // TODO: generalize parse options
    if (selectedCommand == Command::DISK_IMAGE_SHA256_FOR_RELEASE)
    {
      if (argc > 2)
      {
        std::string arg = argv[2];
        if (arg.substr(0, 2) == "--")
        {
          std::string::size_type pos = arg.find('=');
          if (pos != std::string::npos)
          {
            std::string key = arg.substr(2, pos - 2);
            if (key == "release")
            {
              std::string value = arg.substr(pos + 1);
              options[key] = value;
              return;
            }
          }
          else
          {
            std::cerr << "Invalid option format: " << arg << std::endl;
          }
        }
      }
      else
      {
        std::cerr << "Invalid option format" << std::endl;
      }
    }
    else if (argc == 2 && selectedCommand != Command::INVALID)
    {
      return;
    }
  }
  else
  {
    std::cerr << "No command specified." << std::endl;
  }
  handleInvalidCommand();
}

Command CommandParser::stringToCommand(const std::string &commandStr) const
{
  if (commandStr == "supported_releases")
  {
    return Command::SUPPORTED_RELEASES;
  }
  else if (commandStr == "current_lts_version")
  {
    return Command::CURRENT_LTS_VERSION;
  }
  else if (commandStr == "disk_image_sha256_for_release")
  {
    return Command::DISK_IMAGE_SHA256_FOR_RELEASE;
  }
  else
  {
    std::cerr << "Invalid Command: " << commandStr << std::endl;
    return Command::INVALID;
  }
}

Command CommandParser::getSelectedCommand() const
{
  return selectedCommand;
}

std::string CommandParser::getOptions(const std::string &key) const
{
  auto it = options.find(key);
  if (it != options.end())
  {
    return it->second;
  }
  return "";
}

void CommandParser::printAvailableCommands() const
{
  std::cout << "Available commands: " << std::endl;
  std::cout << "  supported_releases" << std::endl;
  std::cout << "  current_lts_version" << std::endl;
  std::cout << "  disk_image_sha256_for_release --release=<release_version>" << std::endl;
}

void CommandParser::handleInvalidCommand() const
{
  printAvailableCommands();
  throw std::invalid_argument("Invalid command");
}
