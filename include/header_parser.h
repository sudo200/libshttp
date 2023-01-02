#ifndef ___HEADER_PARSER_H___
#define ___HEADER_PARSER_H___

#include <sutil/hashmap.h>

#include "parse_status.h"

typedef hashmap_t * http_headers_t;

/**
 * @brief Parses headers in requests and responses.
 * @param headers The struct to place the headers into.
 * @param buf The receive buffer, which will get modified.
 * @param buflen The length of the receive buffer.
 * @param offset When not NULL, the offset at which the body starts will be stored at the specified address.
 * @returns The result of the parse.
 */
parse_status_t parse_headers(http_headers_t *headers, void *buf, size_t buflen, size_t *offset);

#endif  //___HEADER_PARSER_H___

