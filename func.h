#pragma once

#include <stdbool.h>

bool suf(char *input,char *str);

bool pref(char *input,char *str);

bool del(char *input,char *str);

int correct_replace(char *str);

bool repl(char *input_file,char *str);
