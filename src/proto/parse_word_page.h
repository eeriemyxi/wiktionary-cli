#pragma once
#include <lexbor/dom/dom.h>
#include <lexbor/css/css.h>
#include <lexbor/selectors/selectors.h>
#include <lexbor/html/html.h>

#include "../proto/wiktionary.h"
#include "lexbor/dom/interface.h"

#include <string>
#include <unordered_map>


class ParseWordPage {
    public:
        std::string word;
        std::string html;
        
        lxb_html_parser_t* html_parser; 
        lxb_css_parser_t* css_parser; 
        lxb_selectors_t* selectors; 
        lxb_css_selector_list_t* selector_list;

        lxb_html_document_t* document;
        lxb_dom_node_t* body_node;
        lxb_dom_collection_t* english_collection; 
        lxb_dom_collection_t* english_main_header_collection;

        ParseWordPage(const std::string& word, const std::string& html, const SupportedLanguage& lang);
        void get_data();
    private:
        void populate_english_headers(lxb_dom_node_t* initial_node);
};
