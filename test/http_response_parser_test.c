#include <string.h>

#include "test.h"

#include "http_response_parser.h"

#include <sutil/hash.h>

#define equals(x,y) (strcmp(x,y) == 0)
#define stra(str) (void *)str, strlen((const char *)str)

static void check_NULL(void) {
  to_string_status_t status = http_response_to_string(NULL, NULL, 0UL, NULL);
  ASSERT(status == PARSE_ARG_ERR);
}

static void check_buffer_safety(void) {
  char buf[32];
  http_response_t res;
  size_t offset;
  
  res.status = (http_response_status_t) {
    .status = OK,
    .version = HTTP_1_1
  };

  res.headers = hashmap_new(fnv1a);

  hashmap_put(res.headers, stra("Content-Type"), "text/html");
  hashmap_put(res.headers, stra("Server"), "AMOGUS");

  to_string_status_t status = http_response_to_string(&res, buf, sizeof(buf), &offset);
  hashmap_destroy(res.headers);
  ASSERT(status == TOSTR_BUF_OVF);
}

static void check_parse(void) {
  char buf[0xFFFF] = {'\0'};
  http_response_t res = {
    .status = (http_response_status_t) {
      .status = OK,
      .version = HTTP_1_1
    },
    .headers = hashmap_new(fnv1a)
  };

  hashmap_put(res.headers, stra("Content-Type"), "text/plain");
  hashmap_put(res.headers, stra("Server"), "AMOGUS");
  hashmap_put(res.headers, stra("Content-Length"), "13");

  size_t offset;
  to_string_status_t status = http_response_to_string(&res, buf, sizeof(buf), &offset);
  hashmap_destroy(res.headers);

  assert(status == TOSTR_OK);

  strcpy(buf + offset - 2, "Hello there!\n");

  ASSERT(equals(buf,
        "HTTP/1.1 200\r\n"
        "Content-Type: text/plain\r\n"
        "Server: AMOGUS\r\n"
        "Content-Length: 13\r\n"
        "\r\n"
        "Hello there!\n"
        ));
}

int main(void) {
  RUN_TEST(check_NULL);
  RUN_TEST(check_buffer_safety);
  RUN_TEST(check_parse);

  return 0;
}

