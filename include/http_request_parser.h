#ifndef ___HTTP_REQUEST_PARSER_H___
#define ___HTTP_REQUEST_PARSER_H___

#include "request_status_parser.h"
#include "header_parser.h"

typedef struct {
  http_request_status_t status;
  http_headers_t headers;
} http_request_t;

parse_status_t parse_request(http_request_t *req, void *buf, size_t buflen, size_t *offset);

#endif  //___HTTP_REQUEST_PARSER_H___

