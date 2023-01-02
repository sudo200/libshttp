#ifndef ___HEADER_PARSER_H___
#define ___HEADER_PARSER_H___

#include <sutil/hashmap.h>

#include "parse_status.h"
#include "to_string_status.h"

typedef hashmap_t * http_headers_t;

/**
 * @brief Parses headers in requests and responses.
 * @param headers The hashmap to place the headers into.
 * @param buf The receive buffer, which will get modified.
 * @param buflen The length of the receive buffer.
 * @param offset When not NULL, the offset at which the body starts will be stored at the specified address.
 * @returns The result of the parse.
 */
parse_status_t parse_headers(http_headers_t *headers, void *buf, size_t buflen, size_t *offset);

/**
 * @brief Reverse of parse_headers.
 * @param headers The hashmap to get headers from.
 * @param buf The buffer to write into.
 * @param buflen  The length of the buffer.
 * @param offset  When not NULL, the length of the written info is written into memory at address.
 * @return  The result of the stringification.
 */
to_string_status_t headers_to_string(const http_headers_t *headers, void *buf, size_t buflen, size_t *offset);

#endif  //___HEADER_PARSER_H___

