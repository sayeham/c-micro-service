#include "services/UserService.h"

std::optional<std::string> UserService::validateCreatePayload(
    const std::string &name, const std::string &email) const {
  if (name.empty()) {
    return "name is required";
  }
  if (email.empty()) {
    return "email is required";
  }
  if (email.find('@') == std::string::npos) {
    return "email is invalid";
  }
  return std::nullopt;
}

long long UserService::createUser(const std::string &name,
                                  const std::string &email) const {
  return repo_.create(name, email);
}

std::optional<User> UserService::getUserById(long long id) const {
  return repo_.findById(id);
}

std::vector<User> UserService::getAllUsers() const { return repo_.findAll(); }

bool UserService::deleteUser(long long id) const { return repo_.removeById(id); }
