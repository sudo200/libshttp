#include <string.h>

#include "test.h"

#include "http_request_parser.h"

#define equals(x,y) (strcmp(x,y) == 0)
#define stra(str) (void *)str, strlen((const char *)str)

static void check_NULL(void) {
  parse_status_t status = parse_request(NULL, NULL, 0UL, NULL);
  ASSERT(status == PARSE_ARG_ERR);
}

static void check_buffer_safety(void) {
  char buf[] = {
    "GET / HTTP/1.1\r\nCo"
  };
  http_request_t req;
  parse_status_t status = parse_request(&req, buf, sizeof(buf), NULL);
  ASSERT(status == PARSE_BUF_OVF);
}

static void check_parse(void) {
  char buf[] = {
    "POST /sus?lol=true HTTP/1.0\r\n"
    "Content-Type: text/plain\r\n"
    "Content-Length: 13\r\n"
    "\r\n"
    "Hello there!\n"
  };
  http_request_t req;
  size_t offset;
  parse_status_t status = parse_request(&req, buf, sizeof(buf), &offset);
  assert(status == PARSE_OK);

  assert(req.status.method == POST);
  assert(req.status.version == HTTP_1_0);
  assert(equals(req.status.url, "/sus?lol=true"));

  assert(equals((const char *)hashmap_get(req.headers, stra("Content-Type")), "text/plain"));
  assert(equals((const char *)hashmap_get(req.headers, stra("Content-Length")), "13"));
  hashmap_destroy(req.headers);

  ASSERT(equals(buf + offset, "Hello there!\n"));
}

int main(void) {
  RUN_TEST(check_NULL);
  RUN_TEST(check_buffer_safety);
  RUN_TEST(check_parse);

  return 0;
}

