#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DOC_TEXT 1
#define DOC_LINE 2
#define DOC_GROUP 3
#define DOC_END 4
#define DOC_BREAKPARENT 5

// TODO: Pack these tighter?
struct DOC {
  int type;
  int margin;
  int length;
  const char *string;
};

struct DOCBUILDER {
  int count;
  int capacity;
  int margin;
  int indent;
  struct DOC *contents;
};

void docbuilder_init(struct DOCBUILDER *docs, int capacity) {
  docs->count = 0;
  docs->capacity = capacity;
  docs->margin = 0;
  docs->indent = 4;
  docs->contents = malloc(sizeof(struct DOC) * docs->capacity);
}

struct DOCBUILDER docbuilder_new(int capacity) {
  struct DOCBUILDER result;
  docbuilder_init(&result, capacity);
  return result;
}

struct DOC *docbuilder_add(struct DOCBUILDER *builder) {
  builder->count += 1;
  if (builder->count > builder->capacity) {
    builder->capacity += (builder->capacity / 2);
    builder->contents =
        realloc(builder->contents, sizeof(struct DOC) * builder->capacity);
  }

  struct DOC *doc = builder->contents + (builder->count - 1);
  doc->margin = builder->margin;
  return doc;
}

void docbuilder_ensure(struct DOCBUILDER *builder, int more) {
  int capacity = builder->capacity;
  while (capacity < builder->count + more) {
    capacity += (capacity / 2);
  }

  if (capacity != builder->capacity) {
    builder->capacity = capacity;
    builder->contents =
        realloc(builder->contents, sizeof(struct DOC) * builder->capacity);
  }
}

void docbuilder_concat(struct DOCBUILDER *target, struct DOCBUILDER *source) {
  // TODO: Should I just steal the memory somehow?
  docbuilder_ensure(target, source->count);
  struct DOC *dest = target->contents + target->count;
  memcpy(dest, source->contents, source->count);
  target->count += source->count;
}

void doc_indent(struct DOCBUILDER *builder) {
  builder->margin += builder->indent;
}

void doc_dedent(struct DOCBUILDER *builder) {
  builder->margin -= builder->indent;
}

void doc_text(struct DOCBUILDER *builder, const char *text) {
  struct DOC *out = docbuilder_add(builder);
  out->type = DOC_TEXT;
  out->length = strlen(text);
  out->string = text;
}

void doc_line(struct DOCBUILDER *builder) {
  struct DOC *out = docbuilder_add(builder);
  out->type = DOC_LINE;
  out->length = 1;
  out->string = " ";
}

void doc_softline(struct DOCBUILDER *builder) {
  struct DOC *out = docbuilder_add(builder);
  out->type = DOC_LINE;
  out->length = 0;
  out->string = "";
}

void doc_breakparent(struct DOCBUILDER *builder) {
  struct DOC *out = docbuilder_add(builder);
  out->type = DOC_BREAKPARENT;
}

void doc_group(struct DOCBUILDER *builder) {
  struct DOC *result = docbuilder_add(builder);
  result->type = DOC_GROUP;
}

void doc_group_end(struct DOCBUILDER *builder) {
  struct DOC *result = docbuilder_add(builder);
  result->type = DOC_END;
}

void doc_bracket_open(struct DOCBUILDER *builder, const char *left) {
  doc_group(builder);
  doc_text(builder, left);

  doc_indent(builder);
  doc_softline(builder);
}

void doc_bracket_close(struct DOCBUILDER *builder, const char *right) {
  doc_dedent(builder);
  doc_softline(builder);
  doc_text(builder, right);
  doc_group_end(builder);
}

#define OUT_TEXT 1
#define OUT_LINE 2

struct OutputDoc {
  int type;
  int length;
  const char *string;
};

struct OutputBuilder {
  int count;
  int capacity;
  struct OutputDoc *contents;
};

struct OutputDoc *output_add(struct OutputBuilder *builder) {
  builder->count += 1;
  if (builder->count > builder->capacity) {
    builder->capacity += (builder->capacity / 2);
    builder->contents = realloc(builder->contents,
                                sizeof(struct OutputDoc) * builder->capacity);
  }

  return builder->contents + (builder->count - 1);
}

void ss_push_string(struct OutputBuilder *result, int length,
                    const char *string) {
  struct OutputDoc *doc = output_add(result);
  doc->type = OUT_TEXT;
  doc->length = length;
  doc->string = string;
}

void ss_push_line(struct OutputBuilder *result, int margin) {
  struct OutputDoc *doc = output_add(result);
  doc->type = OUT_LINE;
  doc->length = margin;
  doc->string = NULL;
}

void best_rep(struct OutputBuilder *result, int width, struct DOC *docs,
              int length) {
  struct DOC *saved_it = NULL;
  int saved_result_count = 0;
  int saved_used = 0;
  int group_depth = 0;

  struct DOC *end = docs + length;
  struct DOC *it = docs;
  int used = 0;
  while (it != end) {
    switch (it->type) {
    case DOC_LINE:
      if (group_depth == 0) {
        // We're not in a group, so emit a newline and margin and stuff.
        ss_push_line(result, it->margin);
        used = it->margin;
        break;
      }

      // Otherwise, we're *not* breaking lines and we should treat this as a
      // TEXT instruction, in which case...
      // fallthrough
    case DOC_TEXT:
      ss_push_string(result, it->length, it->string);
      used += it->length;
      if (used > width && group_depth > 0) {
        // Rewind output, and reset input; we're not grouped anymore.
        result->count = saved_result_count;
        it = saved_it;
        used = saved_used;
        group_depth = 0;
      }
      break;

    case DOC_BREAKPARENT:
      if (group_depth > 0) {
        // Immediately break all enclosing parents, as if we had overflowed
        // the text.
        result->count = saved_result_count;
        it = saved_it;
        used = saved_used;
        group_depth = 0;
      }
      break;

    case DOC_GROUP:
      group_depth += 1;
      if (group_depth == 1) {
        // Transition from breaking to not breaking, so capture everything we
        // need in order to rewind out of this group. Note that saved_it is it
        // + 1, so we don't revisit this 'GROUP' instruction if we have to
        // reset.
        saved_result_count = result->count;
        saved_it = it + 1;
        saved_used = used;
      }
      break;

    case DOC_END:
      group_depth -= 1;
      if (group_depth == 0) {
        // Back to breaking again; clear these for diagnostic purposes. (We
        // don't really need to, of course.)
        saved_result_count = 0;
        saved_it = NULL;
        saved_used = used;
      }
      break;
    }
    it++;
  }
}

void layout(FILE *file, struct OutputDoc *docs, int length) {
  struct OutputDoc *end = docs + length;
  struct OutputDoc *it = docs;
  while (it != end) {
    switch (it->type) {
    case OUT_TEXT:
      fwrite(it->string, 1, it->length, file);
      break;

    case OUT_LINE:
      fputs("\n", file);
      for (int i = 0; i < it->length; i++) {
        fputc(' ', file);
      }
      break;
    }
    it++;
  }
}