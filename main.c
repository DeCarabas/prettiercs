#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "core.h"
#include "csharp.h"
#include "lexer.h"

#define ERR_INVALID_ARGS 1
#define ERR_CANNOT_OPEN 2
#define ERR_CANNOT_READ 3
#define ERR_PARSE_ERROR 72

char *read_file(FILE *input) {
  const int chunk_size = 4 * 1024 * 1024;

  size_t buffer_size = chunk_size;
  char *buffer = malloc(buffer_size);
  char *end = buffer + buffer_size;
  char *cursor = buffer;

  for (;;) {
    size_t available = end - cursor;
    size_t read = fread(cursor, 1, available, input);
    cursor += read;

    if (feof(input)) {
      break;
    } else if (ferror(input)) {
      fprintf(stderr, "An error occurred reading the input file.\n");
      exit(ERR_CANNOT_READ);
    }

    if (cursor == end) {
      size_t new_buffer_size = buffer_size * 2;
      buffer = realloc(buffer, new_buffer_size);
      end = buffer + new_buffer_size;
      cursor = buffer + buffer_size;
      buffer_size = new_buffer_size;
    }
  }

  return buffer;
}

int main(int argc, const char *argv[]) {
  FILE *input;
  const char *fname = NULL;
  bool dump_tokens = false;
  bool dump_doc = false;

  for (int i = 1; i < argc; i++) {
    const char *arg = argv[i];
    if (arg[0] == '-') {
      if (strcmp(arg, "-dt") == 0) {
        dump_tokens = true;
      } else if (strcmp(arg, "-dd") == 0) {
        dump_doc = true;
      } else {
        fprintf(stderr, "Unrecognized switch: %s\n", arg);
        exit(ERR_INVALID_ARGS);
      }
    } else if (fname) {
      fprintf(stderr, "Duplicate input file: %s\n", arg);
      exit(ERR_INVALID_ARGS);
    } else {
      fname = arg;
    }
  }

  if (fname) {
    input = fopen(argv[1], "r");
    if (!input) {
      fprintf(stderr, "Unable to open input file '%s': %s", argv[1],
              strerror(errno));
      exit(ERR_CANNOT_OPEN);
    }
  } else {
    input = stdin;
  }

  int rc = ERR_PARSE_ERROR;
  char *source = read_file(input);
  if (dump_tokens) {
    dump_lex(source);
    exit(0);
  }

  struct DocBuilder builder = builder_new(16);
  if (format_csharp(&builder, source)) {
    if (dump_doc) {
      dump_docs(builder.contents, builder.count);
      exit(0);
    }

    pretty(stdout, 80, builder.contents, builder.count);
    rc = 0;
  }
  builder_free(&builder);

  free(source);
  return rc;
}
