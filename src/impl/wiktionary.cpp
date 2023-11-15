#include "../proto/wiktionary.h"
#include "../proto/http_fetch.h"
#include "../proto/parse_word_page.h"

#include <format>


std::string support_lang_enum_to_str(SupportedLanguage enum_t){
    switch (enum_t) {
        case SupportedLanguage::ENGLISH:
            return "en";
    }
    return "en";
}

Wiktionary::Wiktionary() : fetcher(BASE_URL) {
};

void Wiktionary::get_word_definition(const std::string& word) {
    std::string word_page_html = fetcher.fetch_word_page(word);
    ParseWordPage parser(word, word_page_html);
    parser.get_data();
};
