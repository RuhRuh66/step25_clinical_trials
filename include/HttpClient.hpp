#pragma once
#include <string>
#include <curl/curl.h>

struct HttpResponse {
    long status_code = 0;
    std::string data;
};

CURLcode Http_get(
    const std::string& url,
    HttpResponse& response
);