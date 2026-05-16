#pragma once

#include "domain/User.h"
#include "repositories/UserRepository.h"

#include <optional>
#include <string>
#include <vector>

class UserService {
 public:
  std::optional<std::string> validateCreatePayload(const std::string &name,
                                                   const std::string &email) const;
  long long createUser(const std::string &name, const std::string &email) const;
  std::optional<User> getUserById(long long id) const;
  std::vector<User> getAllUsers() const;
  bool deleteUser(long long id) const;

 private:
  UserRepository repo_;
};
