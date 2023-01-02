#include <string.h>

#include <sutil/hash.h>
#include <sutil/mstring.h>

#include "header_parser.h"

#include <stdio.h>

parse_status_t parse_headers(http_headers_t *headers, void *buf, size_t buflen, size_t *offset) {
  if(headers == NULL || buf == NULL)
    return PARSE_ARG_ERR;

  if(offset == NULL) {
    size_t dummy;
    offset = &dummy;
  }

  *headers = NULL;

  char *heads = strnstr((char *)buf, "\r\n\r\n", buflen);
  if(heads == NULL)
    return PARSE_BUF_OVF;
  *heads = '\0';

  *offset = heads - (char *)buf + 4;

  *headers = hashmap_new(fnv1a);

  char *save;
  char *h = strtok_r((char *)buf, "\r\n", &save);
  while(h != NULL) {
    char *key = h;
    char *value = strchr(key, ':');
    if(value == NULL)
      return PARSER_ERR;
    *value = '\0';
    value += 2;

    hashmap_put(*headers, key, strlen(key), value);

    h = strtok_r(NULL, "\r\n", &save);
  }

  return PARSE_OK;
}

