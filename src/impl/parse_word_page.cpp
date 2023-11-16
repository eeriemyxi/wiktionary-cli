#include <lexbor/dom/dom.h>
#include <lexbor/css/css.h>
#include <lexbor/selectors/selectors.h>
#include <lexbor/html/html.h>
#include <loguru.hpp>

#include "../proto/parse_word_page.h"
#include "../proto/wiktionary.h"
#include "lexbor/core/base.h"

#include <iostream>

// Converts `SupportedLanguage` enum to string values.
std::string support_lang_enum_to_name(SupportedLanguage lang){
    switch (lang) {
        case SupportedLanguage::ENGLISH:
            return "English";
    }
    return "English";
}

ParseWordPage::ParseWordPage(const std::string& word, const std::string& html, const SupportedLanguage& lang) {
    lxb_status_t status;

    ParseWordPage::word = word;
    LOG_F(INFO, "Word: %s.", word.data());
    ParseWordPage::html = html;
    LOG_F(INFO, "HTML Length: %d.", (int) html.length());
    std::string lang_name = support_lang_enum_to_name(lang);
    LOG_F(INFO, "Language: %s.", lang_name.data());

    auto html_parser = lxb_html_parser_create();
    status = lxb_html_parser_init(html_parser);
    if (status != LXB_STATUS_OK) {
        LOG_F(INFO, "Couldn't init html_parser.");
    }

    auto css_parser = lxb_css_parser_create();
    status = lxb_css_parser_init(css_parser, NULL);
    if (status != LXB_STATUS_OK) {
        LOG_F(INFO, "Couldn't init css_parser.");
    }

    auto selectors = lxb_selectors_create();
    status = lxb_selectors_init(selectors);
    if (status!= LXB_STATUS_OK) {
        LOG_F(INFO, "Couldn't init selectors.");
    }

    auto selectors_list = lxb_css_selectors_parse(css_parser, (lxb_char_t*) ("#" + lang_name).data(), lang_name.length() + 1);
    if (css_parser->status != LXB_STATUS_OK) {
        LOG_F(INFO, "Couldn't parse for selectors_list.");
    }

    auto document = lxb_html_parse(html_parser, (lxb_char_t*) html.data(), html.size());
    auto body_node = lxb_dom_interface_node(document->body);

    auto english_collection = lxb_dom_collection_make(&document->dom_document, 128);

    status = lxb_selectors_find(
            selectors, 
            body_node,
            selectors_list,
            [](lxb_dom_node_t *node, lxb_css_selector_specificity_t spec, void *ctx) -> lxb_status_t {
                lxb_html_serialize_cb(
                    node->parent->next->next->next->next, 
                    [](const lxb_char_t *data, size_t len, void *ctx) -> lxb_status_t {
                        std::cout << data;
                        return LXB_STATUS_OK;
                    },
                    NULL
                );
                std::cout << std::endl;
                return LXB_STATUS_OK;
            },
            NULL
    );
    if (status != LXB_STATUS_OK) {
        LOG_F(INFO, "Couldn't find selector.");
    }
}

void ParseWordPage::get_data() {
    std::cout << "Hello world!\n\t- from the parser." << std::endl;
}
