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


static const char *const format = "%s: %s\r\n";

static void lencheck(void *k, size_t kl, void *v, void *p) {
  const char *key = (const char *)k;
  const char *value = (const char *)v;
  size_t *len = (size_t *)p;

  *len += snprintf(NULL, 0, format, key, value);
}

static void stringify(void *k, size_t kl, void *v, void *p) {
  const char *key = (const char *)k;
  const char *value = (const char *)v;
  char **buffer = (char **)p;

  *buffer += sprintf(*buffer, format, key, value);
}

to_string_status_t headers_to_string(const http_headers_t *headers, void *buf, size_t buflen, size_t *offset) {
  if(headers == NULL || buf == NULL)
    return TOSTR_ARG_ERR;

  size_t len = 3UL;
  hashmap_foreach(*headers, lencheck, &len);
  if(len >= buflen)
    return TOSTR_BUF_OVF;

  *offset = len + 1;

  hashmap_foreach(*headers, stringify, &buf);
  strcat((char *)buf, "\r\n");


  return TOSTR_OK;
}

