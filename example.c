#include <stdio.h>
#include <regex.h>

int main() {
  // Init variables
  regex_t r;
  char * pattern = "^";
  char * haystack = "\n";

  // Compile the pattern
  int ret = regcomp(&r, pattern, REG_NEWLINE); // Seems to about equate multiline mode
  if (ret != 0) {
    printf("Error compiling regex.\n");
    return 1;
  }

  // Prepare variables
  int offset = 0;
  int max_subexpr = 8;
  regmatch_t matches[max_subexpr];
  int flags = 0;
  // Match the pattern
  while (1) {
    int ret = regexec(&r, haystack + offset, max_subexpr, matches, flags);
    if (ret) { return 0; } // No match, exit
    for(int i = 0; i < max_subexpr; i++) {
      if (matches[i].rm_so == -1) { break; } // No more subexpr, break
      printf("Found match at offset %d\n", matches[i].rm_so + offset);
    }

    // Because start of line matches even if first char in sting is null
    // we need to check for the end ourselves
    if ( *(haystack + offset) == '\0') { break; }

    // Increase offset by length of matched string
    offset += matches[0].rm_eo;

    // Every run after the first the REG_NOTSOL flag should be set
    flags |= REG_NOTBOL;
  }

  // Clean up and return
  regfree(&r);
  return 0;
}
