#include <string.h>

#include "methods.h"

#define equals(x, y)  (strcasecmp(x, y) == 0)

const char *http_method_to_string(http_method_t method, size_t *len) {
  size_t dummy;
  if(len == NULL)
    len = &dummy;

  switch (method) {
    case GET:     *len = 3UL; return "GET";
    case POST:    *len = 4UL; return "POST";
    case PATCH:   *len = 5UL; return "PATCH";
    case PUT:     *len = 3UL; return "PUT";
    case DELETE:  *len = 6UL; return "DELETE";
    case HEAD:    *len = 4UL; return "HEAD";
    case CONNECT: *len = 7UL; return "CONNECT";
    case OPTIONS: *len = 7UL; return "OPTIONS";
    case TRACE:   *len = 5UL; return "TRACE";

    case UNKNOWN_METHOD:
    default:
      *len = 14UL;
      return "UNKNOWN_METHOD";
  }
}

http_method_t http_method_from_string(const char *str) {
  if(str == NULL)
    return UNKNOWN_METHOD;

  if(equals(str, "GET"))
    return GET;
  if(equals(str, "POST"))
    return POST;
  if(equals(str, "PATCH"))
    return PATCH;
  if(equals(str, "PUT"))
    return PUT;
  if(equals(str, "DELETE"))
    return DELETE;
  if(equals(str, "HEAD"))
    return HEAD;
  if(equals(str, "CONNECT"))
    return CONNECT;
  if(equals(str, "OPTIONS"))
    return OPTIONS;
  if(equals(str, "TRACE"))
    return TRACE;

  return UNKNOWN_METHOD;
}

