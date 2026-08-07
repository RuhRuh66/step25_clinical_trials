#include <iostream>
#include "HttpClient.hpp"
#include <string>
#include <nlohmann/json.hpp>
#include <vector>

namespace {
struct Study {
    std::string nct_id;
    std::string title;
    std::string start_date;
};

std::vector<Study> parse_studies(const std::string& json_text) {
    const nlohmann::json root = nlohmann::json::parse(json_text);

    const nlohmann::json& studies_json = root.at("studies");

    std::vector<Study> studies;

    for (const nlohmann::json& data: studies_json) {
        const nlohmann::json& protocol_section = data.at("protocolSection");
        const nlohmann::json& identification_module = protocol_section.at("identificationModule");
        const nlohmann::json& status_module = protocol_section.at("statusModule");

        Study study;

        study.nct_id = identification_module.at("nctId").get<std::string>();
        study.title = identification_module.at("briefTitle").get<std::string>();
        
        if (status_module.contains("startDateStruct")) {
            study.start_date = status_module.at("startDateStruct").value("date", "unknown");
        } else {
            study.start_date = "unknown";
        }

        studies.push_back(study);
    }

    return studies;
}


void print_studies(const std::vector<Study>& studies) {
    std::cout << "study count: " << studies.size() << '\n';

    for (const Study& study: studies) {
        std::cout << '\n';
        std::cout << "NCT ID: " << study.nct_id << '\n';
        std::cout << "title: " << study.title << '\n';
        std::cout << "Start date: " << study.start_date << '\n';
    }
}
}






int main() {
    HttpResponse response;
    const std::string url = "https://clinicaltrials.gov/api/v2/studies"
                            "?query.cond=interstitial+lung+disease"
                            "&pageSize=5"
                            "&format=json";
                            
    const CURLcode result = Http_get(url, response);

    if (result != CURLE_OK) {
        std::cerr << "curl failed: " << curl_easy_strerror(result) << '\n';
        return 1;
    }

    if (response.status_code != 200) {
        std::cerr << "HTTP failed: " << response.status_code << '\n';
        return 1;
    }

    std::cout << "HTTP status: " << response.status_code << '\n';

    std::cout << "received: " << response.data.size() << " bytes\n";

    const std::vector<Study> studies = parse_studies(response.data);
    print_studies(studies);

    

    return 0;
}