#include "JsonCtrl.h"

using namespace std;

void JsonCtrl::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    if (!json)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(HttpStatusCode::k400BadRequest);
        callback(resp);
        return;
    }

    if (req->getMethod() == Get)
    {
        int value = cache_.get((*json)["key"].asInt());
        Json::Value json_answ;
        json_answ["requested_value"] = to_string(value);
        // auto id = std::this_thread::get_id();
        {
            std::ostringstream id;
            id << std::this_thread::get_id();
            json_answ["thread_id"] = id.str();
        }
        json_answ["cache"] = cache_.getCache();
        std::ostringstream address;
        address << (void const *)(&cache_);
        std::string name = address.str();
        json_answ["cache_address"] = name;
        auto resp = HttpResponse::newHttpJsonResponse(json_answ);
        callback(resp);
        // resp->setBody(to_string(value).c_str());
    }
    else if (req->getMethod() == Post)
    {
        cache_.refer((*json)["key"].asInt(), (*json)["value"].asInt());
        Json::Value json_answ;
        {
            std::ostringstream id;
            id << std::this_thread::get_id();
            json_answ["thread_id"] = id.str();
        }
        std::ostringstream address;
        address << (void const *)(&cache_);
        std::string name = address.str();
        json_answ["cache_address"] = name;
        json_answ["cache"] = cache_.getCache();
        auto resp = HttpResponse::newHttpJsonResponse(json_answ);
        callback(resp);
    }
}

void JsonCtrl::initCache(int capacity)
{
    cache_.setCapacity(capacity);
}
