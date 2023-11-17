#include <lexbor/dom/dom.h>
#include <lexbor/css/css.h>
#include <lexbor/selectors/selectors.h>
#include <lexbor/html/html.h>
#include <loguru.hpp>

#include "../proto/parse_word_page.h"
#include "../proto/exceptions.h"
#include "../proto/wiktionary.h"
#include "lexbor/core/base.h"
#include "lexbor/dom/collection.h"

#include <iostream>

// Converts `SupportedLanguage` enum to string values.
std::string support_lang_enum_to_name(SupportedLanguage lang){
    switch (lang) {
        case SupportedLanguage::ENGLISH:
            return "English";
    }
    return "English";

}

ParseWordPage::ParseWordPage(
        const std::string& word,
        const std::string& html,
        const SupportedLanguage& lang
    ) {
    ParseWordPage::word = word;
    LOG_F(INFO, "Parsing word page of word \"%s\".", word.data());
    ParseWordPage::html = html;
    LOG_F(INFO, "HTML Length: %d.", (int) html.length());
    std::string lang_name = support_lang_enum_to_name(lang);
    LOG_F(INFO, "Page Language: %s.", lang_name.data());

    ParseWordPage::html_parser = lxb_html_parser_create();
    lxb_status_t status = lxb_html_parser_init(ParseWordPage::html_parser);
    if (status != LXB_STATUS_OK) {
        throw AppException(201, "Couldn't init html_parser.");
    }

    ParseWordPage::css_parser = lxb_css_parser_create();
    status = lxb_css_parser_init(ParseWordPage::css_parser, NULL);
    if (status != LXB_STATUS_OK) {
        throw AppException(202, "Couldn't init css_parser.");
    }

    ParseWordPage::selectors = lxb_selectors_create();
    status = lxb_selectors_init(ParseWordPage::selectors);
    if (status!= LXB_STATUS_OK) {
        throw AppException(203, "Couldn't init css selectors.");
    }

    ParseWordPage::selector_list = lxb_css_selectors_parse(
            ParseWordPage::css_parser, 
            (lxb_char_t*) ("#" + lang_name).data(),
            lang_name.length() + 1
    );
    if (ParseWordPage::css_parser->status != LXB_STATUS_OK) {
        throw AppException(204, "Couldn't parse for selector list.");
    }

    ParseWordPage::document = lxb_html_parse(ParseWordPage::html_parser,
            (lxb_char_t*) html.data(),
            html.size()
    );
    ParseWordPage::body_node = lxb_dom_interface_node(ParseWordPage::document->body);

    ParseWordPage::english_collection = lxb_dom_collection_make(
            &ParseWordPage::document->dom_document, 128
    );
}

void ParseWordPage::get_data() {
    std::cout << "Hello world!\n\t- from the parser." << '\n';
    auto status = lxb_selectors_find(
            this->selectors,
            this->body_node,
            this->selector_list,
            [](lxb_dom_node_t *node, lxb_css_selector_specificity_t spec, void *ctx) -> lxb_status_t {
                ParseWordPage* word_page_parser = (ParseWordPage*) ctx;

                word_page_parser->populate_english_headers(node->parent);
                
                return LXB_STATUS_OK;
            },
            this
    );
    if (status != LXB_STATUS_OK) {
        throw AppException(205, "Couldn't find selector.");
    }
}

void ParseWordPage::populate_english_headers(lxb_dom_node_t* initial_node) {
    ParseWordPage::english_main_header_collection = lxb_dom_collection_make(&this->document->dom_document, 128);

    lxb_status_t status = lxb_dom_node_by_tag_name(initial_node->parent, this->english_main_header_collection, (const lxb_char_t *) "h3", 2);
    if (status != LXB_STATUS_OK) {
        throw AppException(206, "Couldn't find English main header's sub-headers.");
    }

    std::cout << lxb_dom_collection_length(this->english_main_header_collection) << std::endl;

    for (int i = 0; i < lxb_dom_collection_length(this->english_main_header_collection); ++i) {
        auto element = lxb_dom_collection_element(this->english_main_header_collection, i);
        size_t len = 2;
        std::cout << lxb_dom_element_tag_name(element, &len) << std::endl;
    }
}
