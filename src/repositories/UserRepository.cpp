#include "repositories/UserRepository.h"

#include <drogon/drogon.h>

long long UserRepository::create(const std::string &name,
                                 const std::string &email) const {
  auto db = drogon::app().getDbClient();
  auto result = db->execSqlSync(
      "INSERT INTO users(name, email) VALUES($1, $2) RETURNING id", name,
      email);
  return result[0]["id"].as<long long>();
}

std::optional<User> UserRepository::findById(long long id) const {
  auto db = drogon::app().getDbClient();
  auto result = db->execSqlSync(
      "SELECT id, name, email, created_at::text AS created_at FROM users "
      "WHERE id = $1",
      id);

  if (result.empty()) {
    return std::nullopt;
  }

  User user;
  user.id = result[0]["id"].as<long long>();
  user.name = result[0]["name"].as<std::string>();
  user.email = result[0]["email"].as<std::string>();
  user.createdAt = result[0]["created_at"].as<std::string>();
  return user;
}

std::vector<User> UserRepository::findAll() const {
  auto db = drogon::app().getDbClient();
  auto result = db->execSqlSync(
      "SELECT id, name, email, created_at::text AS created_at FROM users "
      "ORDER BY id ASC");

  std::vector<User> users;
  users.reserve(result.size());
  for (const auto &row : result) {
    User user;
    user.id = row["id"].as<long long>();
    user.name = row["name"].as<std::string>();
    user.email = row["email"].as<std::string>();
    user.createdAt = row["created_at"].as<std::string>();
    users.push_back(std::move(user));
  }
  return users;
}

bool UserRepository::removeById(long long id) const {
  auto db = drogon::app().getDbClient();
  auto result = db->execSqlSync("DELETE FROM users WHERE id = $1", id);
  return result.affectedRows() > 0;
}
