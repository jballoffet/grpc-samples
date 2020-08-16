#ifndef AUTHENTICATION_HELPER_H_
#define AUTHENTICATION_HELPER_H_

#include <string>

namespace authentication {

std::string GetCredentialFileContent(const std::string& path);

}  // namespace authentication

#endif  // AUTHENTICATION_HELPER_H_
