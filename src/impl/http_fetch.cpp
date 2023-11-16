#include "../proto/http_fetch.h"

#include <httplib.h>
#include <loguru.hpp>
#include <fmt/color.h>

#include <string>


WiktionaryHTTPFetch::WiktionaryHTTPFetch(const std::string& base_url) : client(base_url) {
}

std::string WiktionaryHTTPFetch::fetch_word_page(const std::string& word) {
    auto response = client.Get("/wiki/" + word);
    if (response->status != 200) {
        LOG_F(ERROR, "%d: Failed to fetch word page.", response->status);
        return "";
    }

    LOG_F(INFO, "%d: Successfully fetched word page.", response->status);
    return response->body;
}
