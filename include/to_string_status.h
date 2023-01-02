#ifndef ___TO_STRING_STATUS_H___
#define ___TO_STRING_STATUS_H___

typedef enum {
  TOSTR_OK, // Everything went fine

  TOSTR_ARG_ERR, // Argument invalid
  TOSTR_BUF_OVF, // We went out of bounds
  TOSTR_ERR, // Generic error
} to_string_status_t;

#endif  //___TO_STRING_STATUS_H___

