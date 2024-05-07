#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

enum class Command
{
  SUPPORTED_RELEASES,
  CURRENT_LTS_VERSION,
  DISK_IMAGE_SHA256_FOR_RELEASE,
  INVALID
};

class CommandParser
{
private:
  Command selectedCommand;
  std::unordered_map<std::string, std::string> options;

public:
  CommandParser(int argc, char *argv[]);
  Command getSelectedCommand() const;
  std::string getOptions(const std::string &key) const;
  void parseCommands(int argc, char *argv[]);

private:
  Command stringToCommand(const std::string &commandStr) const;
  void printAvailableCommands() const;
  void handleInvalidCommand() const;
};

#endif // COMMAND_PARSER_HPP
