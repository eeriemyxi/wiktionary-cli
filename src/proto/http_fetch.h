#pragma once
#include <string>
#include "httplib.h"

class WiktionaryHTTPFetch {
    public:
        httplib::Client client;

        WiktionaryHTTPFetch(const std::string& base_url); 
        std::string fetch_word_page(const std::string& word);
};
