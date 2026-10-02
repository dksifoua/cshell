#ifndef UTILS_H
#define UTILS_H

void disable_stdout_buffering(void);

void remove_leading_whitespace(char *user_input);
void remove_trailing_newline(char *user_input);
bool str_null_or_empty(const char *input);

#endif
