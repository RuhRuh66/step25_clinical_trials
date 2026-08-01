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



}