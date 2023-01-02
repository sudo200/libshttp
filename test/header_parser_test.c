#include <string.h>

#include "test.h"

#include "header_parser.h"

#define equals(x,y) (strcmp(x, y) == 0)
#define stra(str) (void *)str, strlen((const char *)str)

static void check_NULL(void) {
  parse_status_t status = parse_headers(NULL, NULL, 0UL, NULL);
  ASSERT(status == PARSE_ARG_ERR);
}

static void check_buffer_safety(void) {
  char buf[] = {
    "Accept: */*\r\n"
    "Hostname: getalife.com\r\n"
  };
  http_headers_t headers;
  parse_status_t status = parse_headers(&headers, buf, sizeof(buf) - 1, NULL);
  hashmap_destroy(headers);
  ASSERT(status == PARSE_BUF_OVF);
}

static void check_parse(void) {
  char buf[] = {
    "Accept: */*\r\n"
    "User-Agent: Smith\r\n"
    "\r\n"
  };
  size_t offset;
  http_headers_t headers;
  parse_status_t status = parse_headers(&headers, buf, sizeof(buf) - 1, &offset);
  assert(equals((const char *)hashmap_get(headers, stra("Accept")), "*/*"));
  assert(equals((const char *)hashmap_get(headers, stra("User-Agent")), "Smith"));
  hashmap_destroy(headers);
  ASSERT(status == PARSE_OK);
}

int main(void) {
  RUN_TEST(check_NULL);
  RUN_TEST(check_buffer_safety);
  RUN_TEST(check_parse);

  return 0;
}

