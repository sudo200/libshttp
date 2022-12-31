#include "version.h"

#include <string.h>

#define equals(x,y) (strcasecmp(x, y) == 0)

const char *http_version_to_string(http_version_t version, size_t *len) {
  size_t dummy;
  if(len == NULL)
    len = &dummy;

  switch (version) {
    case HTTP_0_9: *len = 8UL; return "HTTP/0.9";
    case HTTP_1_0: *len = 8UL; return "HTTP/1.0";
    case HTTP_1_1: *len = 8UL; return "HTTP/1.1";
    case HTTP_2_0: *len = 8UL; return "HTTP/2.0";

    case UNKNOWN_VERSION:
    default:
      *len = 15UL;
      return "UNKNOWN_VERSION";
  }
}

http_version_t http_version_from_string(const char *str) {
  if(str == NULL)
    return UNKNOWN_VERSION;

  if(equals(str, "HTTP_0_9"))
    return HTTP_0_9;
  if(equals(str, "HTTP_1_0"))
    return HTTP_1_0;
  if(equals(str, "HTTP_1_1"))
    return HTTP_1_1;
  if(equals(str, "HTTP_2_0"))
    return HTTP_2_0;

  return UNKNOWN_VERSION;
}

