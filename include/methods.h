#ifndef ___METHODS_H___
#define ___METHODS_H___

#include <stddef.h>

typedef enum {
  UNKNOWN_METHOD = -1,

  GET,
  POST,
  PATCH,
  PUT,
  DELETE,
  HEAD,
  CONNECT,
  OPTIONS,
  TRACE
} http_method_t;

/**
 * @brief Returns a string representation of the given http method.
 * @param method  The method to 'stringify'.
 * @param len If not NULL, the length of the string will be written to the address pointed to by {@arg len}.
 * @returns The string representation of {@arg method}.
 */
const char *http_method_to_string(http_method_t method, size_t *len);

/**
 * @brief Returns the corresponding enum value for {@arg str}.
 * @param str The string to convert to an enum value.
 * @returns The corresponding enum value.
 */
http_method_t http_method_from_string(const char *str);

#endif  //___METHODS_H___

