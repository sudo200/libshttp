#include <string.h>

#include "test.h"

#include "request_status_parser.h"

#define equals(x,y) (strcmp(x,y) == 0)

static void check_NULL(void) {
  parse_status_t pstatus = parse_request_status(NULL, NULL, 0UL, NULL);
  to_string_status_t tsstatus = request_status_to_string(NULL, NULL, 0UL, NULL);

  assert(tsstatus == TOSTR_ARG_ERR);
  ASSERT(pstatus == PARSE_ARG_ERR);
}

static void check_buffer_safety(void) {
  char buffer[] = {"nhkodnbh0i geghehte\r\n"};
  buffer[sizeof(buffer) - 1] = 'C';

  http_request_status_t req;
  parse_status_t pstatus = parse_request_status(&req, buffer, sizeof(buffer), NULL);

  req = (http_request_status_t) {
    GET,
    "/static/ghuiodnuebneuobonbu/nhjtenhnonruonbguobuobuwuogrbourw?q=bnewugbubguogbrougbduosbgubguowbgu4bguosbowbguogb",
    HTTP_2_0
  };

  to_string_status_t tsstatus = request_status_to_string(&req, buffer, sizeof(buffer), NULL);

  assert(tsstatus == TOSTR_BUF_OVF);
  ASSERT(pstatus == PARSE_BUF_OVF);
}

static void check_parse(void) {
  char buffer[] = {"POST /sus?lol=true HTTP/1.1\r\n"};

  http_request_status_t req;
  size_t offset;
  parse_status_t pstatus = parse_request_status(&req, buffer, sizeof(buffer) - 1, &offset);

  assert(pstatus == PARSE_OK);
  assert(req.method == POST);
  assert(equals(req.url, "/sus?lol=true"));
  assert(req.version == HTTP_1_1);
  assert(offset == sizeof(buffer) - 1);

  req = (http_request_status_t) {
    GET,
    "/lol",
    HTTP_1_1
  };

  to_string_status_t tsstatus = request_status_to_string(&req, buffer, sizeof(buffer), &offset);

  assert(tsstatus == TOSTR_OK);
  assert(equals(buffer, "GET /lol HTTP/1.1\r\n"));

  ASSERT(1);
}

int main(void) {
  RUN_TEST(check_NULL);
  RUN_TEST(check_buffer_safety);
  RUN_TEST(check_parse);

  return 0;
}

