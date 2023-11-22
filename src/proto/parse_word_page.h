#pragma once
#include <lexbor/css/css.h>
#include <lexbor/dom/dom.h>
#include <lexbor/html/html.h>
#include <lexbor/selectors/selectors.h>

#include "../proto/wiktionary.h"

#include <string>
#include <unordered_map>

class ParseWordPage {
    public:
        size_t MAX_TITLE_LEN = 20;
        size_t MAX_TEXT_LEN = 2048;

        std::string word;
        std::string html;
        
        lxb_html_parser_t*        html_parser;
        lxb_css_parser_t*         css_parser;
        lxb_selectors_t*          selectors;
        lxb_css_selector_list_t*  selector_list;

        lxb_html_document_t*      document;
        lxb_dom_node_t*           body_node;
        lxb_dom_collection_t*     english_collection;
        lxb_dom_collection_t*     english_main_header_collection;

        ParseWordPage(const std::string& word, const std::string& html, const SupportedLanguage& lang);
        void get_data();

    private:
        void  parse_english_headers          (lxb_dom_node_t*  h3_node);
        void  handle_header_pronunciation    (lxb_dom_node_t*  node);
        void  handle_header_etymology        (lxb_dom_node_t*  node);
        void  handle_header_references       (lxb_dom_node_t*  node);
        void  handle_header_further_reading  (lxb_dom_node_t*  node);
        void  handle_header_anagrams         (lxb_dom_node_t*  node);
};
