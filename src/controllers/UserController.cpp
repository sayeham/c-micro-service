#include "controllers/UserController.h"

#include <drogon/orm/Exception.h>
#include <json/json.h>

namespace {

drogon::HttpResponsePtr jsonError(drogon::HttpStatusCode code,
                                  const std::string &message) {
  Json::Value body;
  body["error"] = message;
  auto resp = drogon::HttpResponse::newHttpJsonResponse(body);
  resp->setStatusCode(code);
  return resp;
}

}  // namespace

void UserController::create(
    const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
  const auto &json = req->jsonObject();
  if (!json) {
    callback(jsonError(drogon::k400BadRequest, "invalid json body"));
    return;
  }

  const auto name = (*json).get("name", "").asString();
  const auto email = (*json).get("email", "").asString();

  if (auto err = userService_.validateCreatePayload(name, email); err.has_value()) {
    callback(jsonError(drogon::k400BadRequest, *err));
    return;
  }

  try {
    const auto id = userService_.createUser(name, email);
    Json::Value body;
    body["id"] = Json::Int64(id);
    body["message"] = "user created";

    auto resp = drogon::HttpResponse::newHttpJsonResponse(body);
    resp->setStatusCode(drogon::k201Created);
    callback(resp);
  } catch (const drogon::orm::DrogonDbException &e) {
    callback(jsonError(drogon::k409Conflict, e.base().what()));
  }
}

void UserController::getById(
    const drogon::HttpRequestPtr &,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback,
    long long id) {
  try {
    auto user = userService_.getUserById(id);
    if (!user.has_value()) {
      callback(jsonError(drogon::k404NotFound, "user not found"));
      return;
    }

    auto resp = drogon::HttpResponse::newHttpJsonResponse(user->toJson());
    resp->setStatusCode(drogon::k200OK);
    callback(resp);
  } catch (const drogon::orm::DrogonDbException &e) {
    callback(jsonError(drogon::k500InternalServerError, e.base().what()));
  }
}

void UserController::getAll(
    const drogon::HttpRequestPtr &,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
  try {
    auto users = userService_.getAllUsers();
    Json::Value body(Json::arrayValue);
    for (const auto &user : users) {
      body.append(user.toJson());
    }

    auto resp = drogon::HttpResponse::newHttpJsonResponse(body);
    resp->setStatusCode(drogon::k200OK);
    callback(resp);
  } catch (const drogon::orm::DrogonDbException &e) {
    callback(jsonError(drogon::k500InternalServerError, e.base().what()));
  }
}

void UserController::remove(
    const drogon::HttpRequestPtr &,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback,
    long long id) {
  try {
    const bool deleted = userService_.deleteUser(id);
    if (!deleted) {
      callback(jsonError(drogon::k404NotFound, "user not found"));
      return;
    }

    Json::Value body;
    body["message"] = "user deleted";

    auto resp = drogon::HttpResponse::newHttpJsonResponse(body);
    resp->setStatusCode(drogon::k200OK);
    callback(resp);
  } catch (const drogon::orm::DrogonDbException &e) {
    callback(jsonError(drogon::k500InternalServerError, e.base().what()));
  }
}
