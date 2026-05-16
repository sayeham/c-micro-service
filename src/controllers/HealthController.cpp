#include "controllers/HealthController.h"

#include <json/json.h>

void HealthController::health(
    const drogon::HttpRequestPtr &,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
  Json::Value body;
  body["status"] = "ok";

  auto resp = drogon::HttpResponse::newHttpJsonResponse(body);
  resp->setStatusCode(drogon::k200OK);
  callback(resp);
}
