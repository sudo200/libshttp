#include <stdio.h>

#include "http_request_parser.h"

parse_status_t parse_request(http_request_t *req, void *buf, size_t buflen, size_t *offset) {
  if(req == NULL || buf == NULL)
    return PARSE_ARG_ERR;

  if(offset == NULL) {
    size_t dummy;
    offset = &dummy;
  }

  size_t status_offset;
  parse_status_t status = parse_request_status(&req->status, buf, buflen, &status_offset);
  if(status != PARSE_OK)
    return status;

  buf = status_offset + (char *)buf;
  buflen -= status_offset;

  size_t header_offset;
  parse_status_t header = parse_headers(&req->headers, buf, buflen, &header_offset);
  if(header != PARSE_OK)
    return header;

  *offset = status_offset + header_offset;

  return PARSE_OK;
}

