#include <iostream>
#include "HttpClient.hpp"


int main() {
    HttpResponse response;
    
    std::cout << "initial HTTP status: " << response.status_code << '\n';

    return 0;
}