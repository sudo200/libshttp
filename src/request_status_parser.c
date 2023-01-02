#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <sutil/dmem.h>

#include "request_status_parser.h"

parse_status_t parse_request_status(http_request_status_t *status, void *buf, size_t buflen, size_t *offset) {
  if(status == NULL || buf == NULL)
    return PARSE_ARG_ERR;

  if(offset == NULL) {
    size_t dummy;
    offset = &dummy;
  }
  *offset = 0UL;

  char *buf_ptr = (char *) buf;
  size_t i = *offset;

  // Parse method
  char *method = NULL;
  size_t method_len = 0;
  while (i < buflen && buf_ptr[i] != ' ') {
    i++;
    method_len++;
  }
  if (i == buflen) {
    return PARSE_BUF_OVF;
  }
  method = ualloc(method_len + 1);
  strncpy(method, buf_ptr + *offset, method_len);
  method[method_len] = '\0';
  status->method = http_method_from_string(method);
  ufree(method);

  // Parse URI
  i++; // Skip the space character
  *offset = i;
  char *url = NULL;
  size_t url_len = 0;
  while (i < buflen && buf_ptr[i] != ' ') {
    i++;
    url_len++;
  }
  if (i == buflen) {
    return PARSE_BUF_OVF;
  }
  url = buf_ptr + *offset;
  url[url_len] = '\0';
  status->url = url;

  // Parse version
  i++; // Skip the space character
  *offset = i;
  char *version = NULL;
  size_t version_len = 0;
  while (i < buflen && buf_ptr[i] != '\r') {
    i++;
    version_len++;
  }
  if (i == buflen || buf_ptr[i] != '\r') {
    return PARSE_BUF_OVF;
  }
  version = ualloc(version_len + 1);
  strncpy(version, buf_ptr + *offset, version_len);
  version[version_len] = '\0';
  status->version = http_version_from_string(version);
  ufree(version);

  *offset = i + 2; // skip \r\n

  return PARSE_OK;
}

to_string_status_t request_status_to_string(const http_request_status_t *status, void *buf, size_t buflen, size_t *offset) {
  if(status == NULL || buf == NULL)
    return TOSTR_ARG_ERR;

  if(offset == NULL) {
    size_t dummy;
    offset = &dummy;
  }

  const char *const format = "%s %s %s\r\n";

  int len = snprintf(NULL, 0, format,
      http_method_to_string(status->method, NULL),
      status->url,
      http_version_to_string(status->version, NULL)
      );

  if(len >= buflen)
    return TOSTR_BUF_OVF;

  *offset = len + 1;
  if(snprintf((char *)buf, buflen, format,
      http_method_to_string(status->method, NULL),
      status->url,
      http_version_to_string(status->version, NULL)
      ) < 0)
    return TOSTR_ERR;

  return TOSTR_OK;
}

