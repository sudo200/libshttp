#include <string.h>

#include <sutil/hash.h>

#include "test.h"

#include "header_parser.h"

#define equals(x,y) (strcmp(x, y) == 0)
#define stra(str) (void *)str, strlen((const char *)str)

static void check_NULL(void) {
  parse_status_t pstatus = parse_headers(NULL, NULL, 0UL, NULL);
  to_string_status_t tsstatus = headers_to_string(NULL, NULL, 0UL, NULL);
  assert(tsstatus == TOSTR_ARG_ERR);
  ASSERT(pstatus == PARSE_ARG_ERR);
}

static void check_buffer_safety(void) {
  char buf[] = {
    "Accept: */*\r\n"
    "Hostname: getalife.com\r\n"
  };
  http_headers_t headers;
  parse_status_t pstatus = parse_headers(&headers, buf, sizeof(buf) - 1, NULL);
  hashmap_destroy(headers);

  headers = hashmap_new(fnv1a);
  hashmap_put(headers, stra("Server"), "AMOGUS");
  hashmap_put(headers, stra("Content-Length"), "42069");
  hashmap_put(headers, stra("Content-Type"), "application/x-sussus-amogus");
  to_string_status_t tsstatus = headers_to_string(&headers, buf, sizeof(buf), NULL);
  hashmap_destroy(headers);

  assert(tsstatus == TOSTR_BUF_OVF);
  ASSERT(pstatus == PARSE_BUF_OVF);
}

static void check_parse(void) {
  char buf[0xFFF] = {
    "Accept: */*\r\n"
    "User-Agent: Smith\r\n"
    "\r\n"
  };
  size_t offset;
  http_headers_t headers;
  parse_status_t pstatus = parse_headers(&headers, buf, sizeof(buf) - 1, &offset);
  assert(equals((const char *)hashmap_get(headers, stra("Accept")), "*/*"));
  assert(equals((const char *)hashmap_get(headers, stra("User-Agent")), "Smith"));
  hashmap_destroy(headers);

  headers = hashmap_new(fnv1a);
  hashmap_put(headers, stra("Server"), "shttp v1.1");
  hashmap_put(headers, stra("Conn"), "yes");
  to_string_status_t tsstatus = headers_to_string(&headers, buf, sizeof(buf) - 1, &offset);
  hashmap_destroy(headers);

  assert(tsstatus == TOSTR_OK);
  assert(equals(buf, "Server: shttp v1.1\r\nConn: yes\r\n\r\n"));

  ASSERT(pstatus == PARSE_OK);
}

int main(void) {
  RUN_TEST(check_NULL);
  RUN_TEST(check_buffer_safety);
  RUN_TEST(check_parse);

  return 0;
}

