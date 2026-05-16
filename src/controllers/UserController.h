#pragma once

#include "services/UserService.h"

#include <drogon/HttpController.h>

class UserController : public drogon::HttpController<UserController> {
 public:
  METHOD_LIST_BEGIN
  METHOD_ADD(UserController::create, "/api/v1/users", drogon::Post);
  METHOD_ADD(UserController::getById, "/api/v1/users/{1}", drogon::Get);
  METHOD_ADD(UserController::getAll, "/api/v1/users", drogon::Get);
  METHOD_ADD(UserController::remove, "/api/v1/users/{1}", drogon::Delete);
  METHOD_LIST_END

  void create(const drogon::HttpRequestPtr &req,
              std::function<void(const drogon::HttpResponsePtr &)> &&callback);
  void getById(const drogon::HttpRequestPtr &req,
               std::function<void(const drogon::HttpResponsePtr &)> &&callback,
               long long id);
  void getAll(const drogon::HttpRequestPtr &req,
              std::function<void(const drogon::HttpResponsePtr &)> &&callback);
  void remove(const drogon::HttpRequestPtr &req,
              std::function<void(const drogon::HttpResponsePtr &)> &&callback,
              long long id);

 private:
  UserService userService_;
};
