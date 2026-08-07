#include "HttpClient.hpp"
#include <string>
#include <curl/curl.h>



namespace {

std::size_t save_to_data(
    char* ptr,
    std::size_t size,
    std::size_t nmemb,
    void* userdata
) {
    const std::size_t total_size = size * nmemb;
    auto* data = static_cast<std::string*>(userdata);
    data->append(ptr, total_size);
    return total_size;
}

class CurlGlobal {
private:
    CURLcode result_;
public:
    CurlGlobal():result_(curl_global_init(CURL_GLOBAL_DEFAULT)){}

    ~CurlGlobal() {
        if (result_ == CURLE_OK) {
            curl_global_cleanup();
        }
    }

    CurlGlobal(const CurlGlobal&) = delete;
    CurlGlobal& operator=(const CurlGlobal&) = delete;
    
    CURLcode result() const {
        return result_;
    }

};

class CurlEasy{
private: CURL* handle_;

public:
    CurlEasy():handle_(curl_easy_init()){}

    ~CurlEasy(){
        if (handle_ != nullptr) {
            curl_easy_cleanup(handle_);
        }
    }

    bool is_ok() const {
        return handle_ != nullptr;
    }

    CURL* get() const {
        return handle_;
    }

    CurlEasy(const CurlEasy&) = delete;
    CurlEasy& operator=(const CurlEasy&) = delete;

};


}

CURLcode Http_get(const std::string& url, HttpResponse& response){
    response.status_code = 0;
    response.data.clear();

    static CurlGlobal global;
    if (global.result() != CURLE_OK) {
        return global.result();
    }

    CurlEasy easy;
    if (!easy.is_ok()) {
        return CURLE_FAILED_INIT;
    }

    CURL* handle = easy.get();

    CURLcode result = curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, save_to_data);
    if (result == CURLE_OK) {
        result = curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response.data);
    }
    if (result == CURLE_OK) {
        result = curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    }
    if (result == CURLE_OK) {
        result = curl_easy_perform(handle);
    }
    if (result == CURLE_OK) {
        result = curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &response.status_code);
    }

    return result;
}

    