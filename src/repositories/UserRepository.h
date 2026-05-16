#pragma once

#include "domain/User.h"

#include <optional>
#include <vector>

class UserRepository {
 public:
  long long create(const std::string &name, const std::string &email) const;
  std::optional<User> findById(long long id) const;
  std::vector<User> findAll() const;
  bool removeById(long long id) const;
};
