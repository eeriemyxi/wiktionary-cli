#include "../proto/http_fetch.h"

#include <httplib.h>

#include <fmt/color.h>
#include <string>


WiktionaryHTTPFetch::WiktionaryHTTPFetch(const std::string& base_url) : client(base_url) {
}

std::string WiktionaryHTTPFetch::fetch_word_page(const std::string& word) {
    auto response = client.Get("/wiki/" + word);
    if (response->status != 200) {
        fmt::print(stderr, fg(fmt::color::orange_red), "{}: Failed to fetch word page.\n", response->status);
        return "";
    }

    fmt::print(fg(fmt::color::medium_spring_green), "{}: Successfully fetched word page!\n", response->status);
    return response->body;
}
