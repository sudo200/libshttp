#include <stdio.h>

#include "response_status_parser.h"

to_string_status_t response_status_to_string(const http_response_status_t *status, void *buf, size_t buflen, size_t *offset) {
  if(status == NULL || buf == NULL)
    return TOSTR_ARG_ERR;

  if(offset == NULL) {
    size_t dummy;
    offset = &dummy;
  }

  *offset = 0UL;

  const char *const format = "%s %u\r\n";

  int len = snprintf(NULL, 0, format,
      http_version_to_string(status->version, NULL),
      status->status
  );
  if(len < 0)
    return TOSTR_ERR;

  if(len >= buflen)
    return TOSTR_BUF_OVF;

  *offset = len;

  if(snprintf((char *)buf, buflen, format, http_version_to_string(status->version, NULL), status->status) < 0)
    return TOSTR_ERR;

  return TOSTR_OK;
}

