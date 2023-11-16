#include "../proto/wiktionary_http_fetch.h"

#include <httplib.h>
#include <loguru.hpp>
#include <fmt/color.h>

#include <string>


WiktionaryHTTPFetch::WiktionaryHTTPFetch(const std::string& base_url) : client(base_url) {
}

std::string WiktionaryHTTPFetch::fetch_word_page(const std::string& word) {
    auto response = client.Get("/wiki/" + word);

    LOG_F(INFO, "Response status for word page fetch request of word \"%s\": %d", word.data(), response->status);
    if (response->status != 200) {
        throw 301;
    }

    LOG_F(INFO, "Successfully fetched word page of word \"%s\".", word.data());

    return response->body;
}
