#ifndef ___PARSE_STATUS_H___
#define ___PARSE_STATUS_H___

typedef enum {
  PARSE_OK, // Everything went fine

  PARSE_ARG_ERR, // Argument invalid
  PARSE_BUF_OVF, // We went out of bounds
  PARSER_ERR, // Error while parsing
} parse_status_t;

#endif  //___PARSE_STATUS_H___

