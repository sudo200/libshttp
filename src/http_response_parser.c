#include <stdio.h>

#include "http_response_parser.h"

to_string_status_t http_response_to_string(const http_response_t *res, void *buf, size_t buflen, size_t *offset) {
  if(res == NULL || buf == NULL)
    return TOSTR_ARG_ERR;

  if(offset == NULL) {
    size_t dummy;
    offset = &dummy;
  }

  size_t status_offset;
  to_string_status_t status = response_status_to_string(&res->status, buf, buflen, &status_offset);
  if(status != TOSTR_OK)
    return status;

  buf = status_offset + (char *)buf;
  buflen -= status_offset;

  size_t header_offset;
  to_string_status_t header = headers_to_string(&res->headers, buf, buflen, &header_offset);
  if(header != TOSTR_OK)
    return header;

  *offset = status_offset + header_offset;

  return TOSTR_OK;
}

