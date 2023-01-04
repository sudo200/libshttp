#ifndef ___HTTP_RESPONSE_PARSER_H___
#define ___HTTP_RESPONSE_PARSER_H___

#include "response_status_parser.h"
#include "header_parser.h"

typedef struct {
  http_response_status_t status;
  http_headers_t headers;
} http_response_t;

to_string_status_t http_response_to_string(const http_response_t *res, void *buf, size_t buflen, size_t *offset);

#endif  //___HTTP_RESPONSE_PARSER_H___

