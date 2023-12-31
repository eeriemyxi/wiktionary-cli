#include <httplib.h>
#include <loguru.hpp>
#include <fmt/color.h>

#include "../proto/wiktionary_http_fetch.h"
#include "../proto/util/url_encode.h"
#include "../proto/exceptions.h"

#include <string>
#include <format>


WiktionaryHTTPFetch::WiktionaryHTTPFetch(const std::string& base_url) : client(base_url) {
}

std::string WiktionaryHTTPFetch::fetch_word_page(const std::string& word) {
    std::string url = "/wiki/" + util::url_encode(word);
    LOG_F(INFO, "Fetching word page URL: %s", url.data());

    auto response = client.Get(url);

    LOG_F(INFO, "Response status for word page fetch request of word \"%s\": %d", word.data(), response->status);
    if (response->status != 200) {
        throw AppException(301, std::format("Failed to fetch word page of word \"{}\".", word));
    }

    LOG_F(INFO, "Successfully fetched word page of word \"%s\".", word.data());

    return response->body;
}
