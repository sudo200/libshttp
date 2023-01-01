#include <string.h>

#include "test.h"

#include "request_status_parser.h"

#define equals(x,y) (strcmp(x,y) == 0)

static void check_NULL(void) {
  parse_status_t status = parse_request_status(NULL, NULL, 0UL, NULL);
  ASSERT(status == PARSE_ARG_ERR);
}

static void check_buffer_safety(void) {
  char buffer[] = {"nhkodnbh0i geghehte\r\n"};
  buffer[sizeof(buffer) - 1] = 'C';

  http_request_status_t req;
  parse_status_t status = parse_request_status(&req, buffer, sizeof(buffer), NULL);

  ASSERT(status == PARSE_BUF_OVF);
}

static void check_parse(void) {
  char buffer[] = {"POST /sus?lol=true HTTP/1.1\r\n"};

  http_request_status_t req;
  size_t offset;
  parse_status_t status = parse_request_status(&req, buffer, sizeof(buffer) - 1, &offset);

  assert(status == PARSE_OK);
  assert(req.method == POST);
  assert(equals(req.url, "/sus?lol=true"));
  assert(req.version == HTTP_1_1);
  ASSERT(offset == sizeof(buffer) - 1);
}

int main(void) {
  RUN_TEST(check_NULL);
  RUN_TEST(check_buffer_safety);
  RUN_TEST(check_parse);

  return 0;
}

