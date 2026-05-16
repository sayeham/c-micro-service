#pragma once

#include <json/json.h>

#include <string>

struct User {
  long long id{};
  std::string name;
  std::string email;
  std::string createdAt;

  Json::Value toJson() const {
    Json::Value out;
    out["id"] = Json::Int64(id);
    out["name"] = name;
    out["email"] = email;
    out["created_at"] = createdAt;
    return out;
  }
};
