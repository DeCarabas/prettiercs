/*
prettysharp
Copyright (C) 2019 John Doty

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef TOKEN_H
#define TOKEN_H

#include "common.h"

enum TokenType {
#define TKN(id, txt, is_id, prefix, infix, prec) TOKEN_##id,
#include "token.inc"
#undef TKN
};

struct Token {
  enum TokenType type;
  const char *start;
  int length;
  int line;
};

const char *token_text(enum TokenType type);
bool is_identifier_token(enum TokenType type);
enum TokenType keyword_type(const char *start, int len);

const char *dbg_token_type(enum TokenType type);

#endif
