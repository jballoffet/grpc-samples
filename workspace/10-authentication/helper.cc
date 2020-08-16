#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace authentication {

std::string GetCredentialFileContent(const std::string& path) {
  std::ifstream cred_file(path);
  if (!cred_file.is_open()) {
    std::cout << "Failed to open " << path << std::endl;
    return "";
  }
  std::stringstream cred;
  cred << cred_file.rdbuf();
  return cred.str();
}

}  // namespace authentication
