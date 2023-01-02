#ifndef ___REQUEST_STATUS_PARSER_H___
#define ___REQUEST_STATUS_PARSER_H___

#include "methods.h"
#include "version.h"
#include "parse_status.h"
#include "to_string_status.h"

typedef struct {
  http_method_t method;
  char *url;
  http_version_t version;
} http_request_status_t;

/**
 * @brief Parses the request status line.
 * @param status The struct to put parsed info into.
 * @param buf The receive buffer, which will get modified.
 * @param buflen The length of the receive buffer,
 * @param offset When not NULL, the offset at which the headers start is written into memory at address.
 * @returns The result of the parse.
 */
parse_status_t parse_request_status(http_request_status_t *status, void *buf, size_t buflen, size_t *offset);


/**
 * @brief Reverse of parse_request_status.
 * @param status The struct to stringify info from.
 * @param buf Buffer to write into.
 * @param buflen  The length of the buffer.
 * @param offset  Of non-NULL, the length of the written info is written into memory at address.
 * @return  The result of the stringification.
 */
to_string_status_t request_status_to_string(const http_request_status_t *status, void *buf, size_t buflen, size_t *offset);

#endif  //___REQUEST_STATUS_PARSER_H___

