#ifndef ___RESPONSE_STATUS_PARSER_H__
#define ___RESPONSE_STATUS_PARSER_H__

#include "statuses.h"
#include "version.h"
#include "to_string_status.h"

typedef struct {
  http_version_t version;
  http_status_t status;
} http_response_status_t;


to_string_status_t response_status_to_string(const http_response_status_t *status, void *buf, size_t buflen, size_t *offset);

#endif  //___RESPONSE_STATUS_PARSER_H__

