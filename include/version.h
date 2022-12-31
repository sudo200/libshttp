#ifndef ___VERSION_H___
#define ___VERSION_H___

#include <stddef.h>

typedef enum {
  UNKNOWN_VERSION = -1,

  HTTP_0_9,
  HTTP_ONELINE = HTTP_0_9,
  HTTP_1_0,
  HTTP_1_1,
  HTTP_2_0
} http_version_t;


/**
 * @brief Returns a string representation of the given http version.
 * @param version The version to 'stringify'.
 * @param len If not NULL, the length of the string will be written to the address pointed to by {@arg len}.
 * @returns The string representation of {@arg version}.
 */
const char *http_version_to_string(http_version_t version, size_t *len);

/**
 * @brief Returns the corresponding enum value for {@arg str}.
 * @param str The string to convert to an enum value.
 * @returns The corresponding enum value.
 */
http_version_t http_version_from_string(const char *str);

#endif  //___VERSION_H___

