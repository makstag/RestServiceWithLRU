#pragma once

#include <drogon/HttpSimpleController.h>
#include "../libs/lru_cache.h"

using namespace drogon;

class JsonCtrl : public drogon::HttpSimpleController<JsonCtrl, false>
{
public:
  virtual void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  // list path definitions here;
  PATH_ADD("/key", Get, Post);
  PATH_LIST_END

public:
  explicit JsonCtrl(int capacity) : cache_(capacity){};
  void initCache(int capacity);

private:
  LRUCache cache_{2};
};
