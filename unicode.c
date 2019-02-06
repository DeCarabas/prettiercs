#include "unicode.h"

bool decode_utf8(const char **position, uint32_t *result) {
  const char *current = *position;

  if ((*current & 0x80) == 0x00) {
    if (current[0] == 0) {
      return false;
    }

    // 1 byte:  0xxxxxxx
    *result = current[0];
    *position = current + 1;
    return true;
  } else if ((*current & 0xE0) == 0xC0) {
    if (current[1] == 0) {
      return false;
    }

    // 2 bytes: 110xxxxx 10xxxxxx
    uint32_t a = (current[0] & 0x1F);
    uint32_t b = (current[1] & 0x3F);
    *result = (a << 6) | b;
    *position = current + 2;
    return true;
  } else if ((*current & 0xF0) == 0xE0) {
    if (current[1] == 0 || current[2] == 0) {
      return false;
    }

    // 3 bytes: 1110xxxx 10xxxxxx 10xxxxxx
    uint32_t a = (current[0] & 0x0F);
    uint32_t b = (current[1] & 0x3F);
    uint32_t c = (current[2] & 0x3F);
    *result = (a << 12) | (b << 6) | c;
    *position = current + 3;
    return true;
  } else if ((*current & 0xF8) == 0xF0) {
    if (current[1] == 0 || current[2] == 0 || current[3] == 0) {
      return false;
    }

    // 4 bytes: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    uint32_t a = (current[0] & 0x07);
    uint32_t b = (current[1] & 0x3F);
    uint32_t c = (current[2] & 0x3F);
    uint32_t d = (current[3] & 0x3F);
    *result = (a << 18) | (b << 12) | (c << 6) | d;
    *position = current + 4;
    return true;
  } else {
    // Bad encoding of some kind; invalid prefix byte.
    return false;
  }
}

bool is_identifier_start_rune(uint32_t rune) {
  // Any code point in Lo, Lm, Ll, Nl, Lt, Lu, or '_'
  return rune == '_' || (rune >= 65 && rune <= 90) ||
         (rune >= 97 && rune <= 122) || (rune >= 170 && rune <= 170) ||
         (rune >= 181 && rune <= 181) || (rune >= 186 && rune <= 186) ||
         (rune >= 192 && rune <= 214) || (rune >= 216 && rune <= 246) ||
         (rune >= 248 && rune <= 705) || (rune >= 710 && rune <= 721) ||
         (rune >= 736 && rune <= 740) || (rune >= 748 && rune <= 748) ||
         (rune >= 750 && rune <= 750) || (rune >= 880 && rune <= 884) ||
         (rune >= 886 && rune <= 887) || (rune >= 890 && rune <= 893) ||
         (rune >= 895 && rune <= 895) || (rune >= 902 && rune <= 902) ||
         (rune >= 904 && rune <= 906) || (rune >= 908 && rune <= 908) ||
         (rune >= 910 && rune <= 929) || (rune >= 931 && rune <= 1013) ||
         (rune >= 1015 && rune <= 1153) || (rune >= 1162 && rune <= 1327) ||
         (rune >= 1329 && rune <= 1366) || (rune >= 1369 && rune <= 1369) ||
         (rune >= 1376 && rune <= 1416) || (rune >= 1488 && rune <= 1514) ||
         (rune >= 1519 && rune <= 1522) || (rune >= 1568 && rune <= 1610) ||
         (rune >= 1646 && rune <= 1647) || (rune >= 1649 && rune <= 1747) ||
         (rune >= 1749 && rune <= 1749) || (rune >= 1765 && rune <= 1766) ||
         (rune >= 1774 && rune <= 1775) || (rune >= 1786 && rune <= 1788) ||
         (rune >= 1791 && rune <= 1791) || (rune >= 1808 && rune <= 1808) ||
         (rune >= 1810 && rune <= 1839) || (rune >= 1869 && rune <= 1957) ||
         (rune >= 1969 && rune <= 1969) || (rune >= 1994 && rune <= 2026) ||
         (rune >= 2036 && rune <= 2037) || (rune >= 2042 && rune <= 2042) ||
         (rune >= 2048 && rune <= 2069) || (rune >= 2074 && rune <= 2074) ||
         (rune >= 2084 && rune <= 2084) || (rune >= 2088 && rune <= 2088) ||
         (rune >= 2112 && rune <= 2136) || (rune >= 2144 && rune <= 2154) ||
         (rune >= 2208 && rune <= 2228) || (rune >= 2230 && rune <= 2237) ||
         (rune >= 2308 && rune <= 2361) || (rune >= 2365 && rune <= 2365) ||
         (rune >= 2384 && rune <= 2384) || (rune >= 2392 && rune <= 2401) ||
         (rune >= 2417 && rune <= 2432) || (rune >= 2437 && rune <= 2444) ||
         (rune >= 2447 && rune <= 2448) || (rune >= 2451 && rune <= 2472) ||
         (rune >= 2474 && rune <= 2480) || (rune >= 2482 && rune <= 2482) ||
         (rune >= 2486 && rune <= 2489) || (rune >= 2493 && rune <= 2493) ||
         (rune >= 2510 && rune <= 2510) || (rune >= 2524 && rune <= 2525) ||
         (rune >= 2527 && rune <= 2529) || (rune >= 2544 && rune <= 2545) ||
         (rune >= 2556 && rune <= 2556) || (rune >= 2565 && rune <= 2570) ||
         (rune >= 2575 && rune <= 2576) || (rune >= 2579 && rune <= 2600) ||
         (rune >= 2602 && rune <= 2608) || (rune >= 2610 && rune <= 2611) ||
         (rune >= 2613 && rune <= 2614) || (rune >= 2616 && rune <= 2617) ||
         (rune >= 2649 && rune <= 2652) || (rune >= 2654 && rune <= 2654) ||
         (rune >= 2674 && rune <= 2676) || (rune >= 2693 && rune <= 2701) ||
         (rune >= 2703 && rune <= 2705) || (rune >= 2707 && rune <= 2728) ||
         (rune >= 2730 && rune <= 2736) || (rune >= 2738 && rune <= 2739) ||
         (rune >= 2741 && rune <= 2745) || (rune >= 2749 && rune <= 2749) ||
         (rune >= 2768 && rune <= 2768) || (rune >= 2784 && rune <= 2785) ||
         (rune >= 2809 && rune <= 2809) || (rune >= 2821 && rune <= 2828) ||
         (rune >= 2831 && rune <= 2832) || (rune >= 2835 && rune <= 2856) ||
         (rune >= 2858 && rune <= 2864) || (rune >= 2866 && rune <= 2867) ||
         (rune >= 2869 && rune <= 2873) || (rune >= 2877 && rune <= 2877) ||
         (rune >= 2908 && rune <= 2909) || (rune >= 2911 && rune <= 2913) ||
         (rune >= 2929 && rune <= 2929) || (rune >= 2947 && rune <= 2947) ||
         (rune >= 2949 && rune <= 2954) || (rune >= 2958 && rune <= 2960) ||
         (rune >= 2962 && rune <= 2965) || (rune >= 2969 && rune <= 2970) ||
         (rune >= 2972 && rune <= 2972) || (rune >= 2974 && rune <= 2975) ||
         (rune >= 2979 && rune <= 2980) || (rune >= 2984 && rune <= 2986) ||
         (rune >= 2990 && rune <= 3001) || (rune >= 3024 && rune <= 3024) ||
         (rune >= 3077 && rune <= 3084) || (rune >= 3086 && rune <= 3088) ||
         (rune >= 3090 && rune <= 3112) || (rune >= 3114 && rune <= 3129) ||
         (rune >= 3133 && rune <= 3133) || (rune >= 3160 && rune <= 3162) ||
         (rune >= 3168 && rune <= 3169) || (rune >= 3200 && rune <= 3200) ||
         (rune >= 3205 && rune <= 3212) || (rune >= 3214 && rune <= 3216) ||
         (rune >= 3218 && rune <= 3240) || (rune >= 3242 && rune <= 3251) ||
         (rune >= 3253 && rune <= 3257) || (rune >= 3261 && rune <= 3261) ||
         (rune >= 3294 && rune <= 3294) || (rune >= 3296 && rune <= 3297) ||
         (rune >= 3313 && rune <= 3314) || (rune >= 3333 && rune <= 3340) ||
         (rune >= 3342 && rune <= 3344) || (rune >= 3346 && rune <= 3386) ||
         (rune >= 3389 && rune <= 3389) || (rune >= 3406 && rune <= 3406) ||
         (rune >= 3412 && rune <= 3414) || (rune >= 3423 && rune <= 3425) ||
         (rune >= 3450 && rune <= 3455) || (rune >= 3461 && rune <= 3478) ||
         (rune >= 3482 && rune <= 3505) || (rune >= 3507 && rune <= 3515) ||
         (rune >= 3517 && rune <= 3517) || (rune >= 3520 && rune <= 3526) ||
         (rune >= 3585 && rune <= 3632) || (rune >= 3634 && rune <= 3635) ||
         (rune >= 3648 && rune <= 3654) || (rune >= 3713 && rune <= 3714) ||
         (rune >= 3716 && rune <= 3716) || (rune >= 3719 && rune <= 3720) ||
         (rune >= 3722 && rune <= 3722) || (rune >= 3725 && rune <= 3725) ||
         (rune >= 3732 && rune <= 3735) || (rune >= 3737 && rune <= 3743) ||
         (rune >= 3745 && rune <= 3747) || (rune >= 3749 && rune <= 3749) ||
         (rune >= 3751 && rune <= 3751) || (rune >= 3754 && rune <= 3755) ||
         (rune >= 3757 && rune <= 3760) || (rune >= 3762 && rune <= 3763) ||
         (rune >= 3773 && rune <= 3773) || (rune >= 3776 && rune <= 3780) ||
         (rune >= 3782 && rune <= 3782) || (rune >= 3804 && rune <= 3807) ||
         (rune >= 3840 && rune <= 3840) || (rune >= 3904 && rune <= 3911) ||
         (rune >= 3913 && rune <= 3948) || (rune >= 3976 && rune <= 3980) ||
         (rune >= 4096 && rune <= 4138) || (rune >= 4159 && rune <= 4159) ||
         (rune >= 4176 && rune <= 4181) || (rune >= 4186 && rune <= 4189) ||
         (rune >= 4193 && rune <= 4193) || (rune >= 4197 && rune <= 4198) ||
         (rune >= 4206 && rune <= 4208) || (rune >= 4213 && rune <= 4225) ||
         (rune >= 4238 && rune <= 4238) || (rune >= 4256 && rune <= 4293) ||
         (rune >= 4295 && rune <= 4295) || (rune >= 4301 && rune <= 4301) ||
         (rune >= 4304 && rune <= 4346) || (rune >= 4348 && rune <= 4680) ||
         (rune >= 4682 && rune <= 4685) || (rune >= 4688 && rune <= 4694) ||
         (rune >= 4696 && rune <= 4696) || (rune >= 4698 && rune <= 4701) ||
         (rune >= 4704 && rune <= 4744) || (rune >= 4746 && rune <= 4749) ||
         (rune >= 4752 && rune <= 4784) || (rune >= 4786 && rune <= 4789) ||
         (rune >= 4792 && rune <= 4798) || (rune >= 4800 && rune <= 4800) ||
         (rune >= 4802 && rune <= 4805) || (rune >= 4808 && rune <= 4822) ||
         (rune >= 4824 && rune <= 4880) || (rune >= 4882 && rune <= 4885) ||
         (rune >= 4888 && rune <= 4954) || (rune >= 4992 && rune <= 5007) ||
         (rune >= 5024 && rune <= 5109) || (rune >= 5112 && rune <= 5117) ||
         (rune >= 5121 && rune <= 5740) || (rune >= 5743 && rune <= 5759) ||
         (rune >= 5761 && rune <= 5786) || (rune >= 5792 && rune <= 5866) ||
         (rune >= 5870 && rune <= 5880) || (rune >= 5888 && rune <= 5900) ||
         (rune >= 5902 && rune <= 5905) || (rune >= 5920 && rune <= 5937) ||
         (rune >= 5952 && rune <= 5969) || (rune >= 5984 && rune <= 5996) ||
         (rune >= 5998 && rune <= 6000) || (rune >= 6016 && rune <= 6067) ||
         (rune >= 6103 && rune <= 6103) || (rune >= 6108 && rune <= 6108) ||
         (rune >= 6176 && rune <= 6264) || (rune >= 6272 && rune <= 6276) ||
         (rune >= 6279 && rune <= 6312) || (rune >= 6314 && rune <= 6314) ||
         (rune >= 6320 && rune <= 6389) || (rune >= 6400 && rune <= 6430) ||
         (rune >= 6480 && rune <= 6509) || (rune >= 6512 && rune <= 6516) ||
         (rune >= 6528 && rune <= 6571) || (rune >= 6576 && rune <= 6601) ||
         (rune >= 6656 && rune <= 6678) || (rune >= 6688 && rune <= 6740) ||
         (rune >= 6823 && rune <= 6823) || (rune >= 6917 && rune <= 6963) ||
         (rune >= 6981 && rune <= 6987) || (rune >= 7043 && rune <= 7072) ||
         (rune >= 7086 && rune <= 7087) || (rune >= 7098 && rune <= 7141) ||
         (rune >= 7168 && rune <= 7203) || (rune >= 7245 && rune <= 7247) ||
         (rune >= 7258 && rune <= 7293) || (rune >= 7296 && rune <= 7304) ||
         (rune >= 7312 && rune <= 7354) || (rune >= 7357 && rune <= 7359) ||
         (rune >= 7401 && rune <= 7404) || (rune >= 7406 && rune <= 7409) ||
         (rune >= 7413 && rune <= 7414) || (rune >= 7424 && rune <= 7615) ||
         (rune >= 7680 && rune <= 7957) || (rune >= 7960 && rune <= 7965) ||
         (rune >= 7968 && rune <= 8005) || (rune >= 8008 && rune <= 8013) ||
         (rune >= 8016 && rune <= 8023) || (rune >= 8025 && rune <= 8025) ||
         (rune >= 8027 && rune <= 8027) || (rune >= 8029 && rune <= 8029) ||
         (rune >= 8031 && rune <= 8061) || (rune >= 8064 && rune <= 8116) ||
         (rune >= 8118 && rune <= 8124) || (rune >= 8126 && rune <= 8126) ||
         (rune >= 8130 && rune <= 8132) || (rune >= 8134 && rune <= 8140) ||
         (rune >= 8144 && rune <= 8147) || (rune >= 8150 && rune <= 8155) ||
         (rune >= 8160 && rune <= 8172) || (rune >= 8178 && rune <= 8180) ||
         (rune >= 8182 && rune <= 8188) || (rune >= 8305 && rune <= 8305) ||
         (rune >= 8319 && rune <= 8319) || (rune >= 8336 && rune <= 8348) ||
         (rune >= 8450 && rune <= 8450) || (rune >= 8455 && rune <= 8455) ||
         (rune >= 8458 && rune <= 8467) || (rune >= 8469 && rune <= 8469) ||
         (rune >= 8473 && rune <= 8477) || (rune >= 8484 && rune <= 8484) ||
         (rune >= 8486 && rune <= 8486) || (rune >= 8488 && rune <= 8488) ||
         (rune >= 8490 && rune <= 8493) || (rune >= 8495 && rune <= 8505) ||
         (rune >= 8508 && rune <= 8511) || (rune >= 8517 && rune <= 8521) ||
         (rune >= 8526 && rune <= 8526) || (rune >= 8544 && rune <= 8584) ||
         (rune >= 11264 && rune <= 11310) || (rune >= 11312 && rune <= 11358) ||
         (rune >= 11360 && rune <= 11492) || (rune >= 11499 && rune <= 11502) ||
         (rune >= 11506 && rune <= 11507) || (rune >= 11520 && rune <= 11557) ||
         (rune >= 11559 && rune <= 11559) || (rune >= 11565 && rune <= 11565) ||
         (rune >= 11568 && rune <= 11623) || (rune >= 11631 && rune <= 11631) ||
         (rune >= 11648 && rune <= 11670) || (rune >= 11680 && rune <= 11686) ||
         (rune >= 11688 && rune <= 11694) || (rune >= 11696 && rune <= 11702) ||
         (rune >= 11704 && rune <= 11710) || (rune >= 11712 && rune <= 11718) ||
         (rune >= 11720 && rune <= 11726) || (rune >= 11728 && rune <= 11734) ||
         (rune >= 11736 && rune <= 11742) || (rune >= 11823 && rune <= 11823) ||
         (rune >= 12293 && rune <= 12295) || (rune >= 12321 && rune <= 12329) ||
         (rune >= 12337 && rune <= 12341) || (rune >= 12344 && rune <= 12348) ||
         (rune >= 12353 && rune <= 12438) || (rune >= 12445 && rune <= 12447) ||
         (rune >= 12449 && rune <= 12538) || (rune >= 12540 && rune <= 12543) ||
         (rune >= 12549 && rune <= 12591) || (rune >= 12593 && rune <= 12686) ||
         (rune >= 12704 && rune <= 12730) || (rune >= 12784 && rune <= 12799) ||
         (rune >= 13312 && rune <= 13312) || (rune >= 19893 && rune <= 19893) ||
         (rune >= 19968 && rune <= 19968) || (rune >= 40943 && rune <= 40943) ||
         (rune >= 40960 && rune <= 42124) || (rune >= 42192 && rune <= 42237) ||
         (rune >= 42240 && rune <= 42508) || (rune >= 42512 && rune <= 42527) ||
         (rune >= 42538 && rune <= 42539) || (rune >= 42560 && rune <= 42606) ||
         (rune >= 42623 && rune <= 42653) || (rune >= 42656 && rune <= 42735) ||
         (rune >= 42775 && rune <= 42783) || (rune >= 42786 && rune <= 42888) ||
         (rune >= 42891 && rune <= 42937) || (rune >= 42999 && rune <= 43009) ||
         (rune >= 43011 && rune <= 43013) || (rune >= 43015 && rune <= 43018) ||
         (rune >= 43020 && rune <= 43042) || (rune >= 43072 && rune <= 43123) ||
         (rune >= 43138 && rune <= 43187) || (rune >= 43250 && rune <= 43255) ||
         (rune >= 43259 && rune <= 43259) || (rune >= 43261 && rune <= 43262) ||
         (rune >= 43274 && rune <= 43301) || (rune >= 43312 && rune <= 43334) ||
         (rune >= 43360 && rune <= 43388) || (rune >= 43396 && rune <= 43442) ||
         (rune >= 43471 && rune <= 43471) || (rune >= 43488 && rune <= 43492) ||
         (rune >= 43494 && rune <= 43503) || (rune >= 43514 && rune <= 43518) ||
         (rune >= 43520 && rune <= 43560) || (rune >= 43584 && rune <= 43586) ||
         (rune >= 43588 && rune <= 43595) || (rune >= 43616 && rune <= 43638) ||
         (rune >= 43642 && rune <= 43642) || (rune >= 43646 && rune <= 43695) ||
         (rune >= 43697 && rune <= 43697) || (rune >= 43701 && rune <= 43702) ||
         (rune >= 43705 && rune <= 43709) || (rune >= 43712 && rune <= 43712) ||
         (rune >= 43714 && rune <= 43714) || (rune >= 43739 && rune <= 43741) ||
         (rune >= 43744 && rune <= 43754) || (rune >= 43762 && rune <= 43764) ||
         (rune >= 43777 && rune <= 43782) || (rune >= 43785 && rune <= 43790) ||
         (rune >= 43793 && rune <= 43798) || (rune >= 43808 && rune <= 43814) ||
         (rune >= 43816 && rune <= 43822) || (rune >= 43824 && rune <= 43866) ||
         (rune >= 43868 && rune <= 43877) || (rune >= 43888 && rune <= 44002) ||
         (rune >= 44032 && rune <= 44032) || (rune >= 55203 && rune <= 55203) ||
         (rune >= 55216 && rune <= 55238) || (rune >= 55243 && rune <= 55291) ||
         (rune >= 63744 && rune <= 64109) || (rune >= 64112 && rune <= 64217) ||
         (rune >= 64256 && rune <= 64262) || (rune >= 64275 && rune <= 64279) ||
         (rune >= 64285 && rune <= 64285) || (rune >= 64287 && rune <= 64296) ||
         (rune >= 64298 && rune <= 64310) || (rune >= 64312 && rune <= 64316) ||
         (rune >= 64318 && rune <= 64318) || (rune >= 64320 && rune <= 64321) ||
         (rune >= 64323 && rune <= 64324) || (rune >= 64326 && rune <= 64433) ||
         (rune >= 64467 && rune <= 64829) || (rune >= 64848 && rune <= 64911) ||
         (rune >= 64914 && rune <= 64967) || (rune >= 65008 && rune <= 65019) ||
         (rune >= 65136 && rune <= 65140) || (rune >= 65142 && rune <= 65276) ||
         (rune >= 65313 && rune <= 65338) || (rune >= 65345 && rune <= 65370) ||
         (rune >= 65382 && rune <= 65470) || (rune >= 65474 && rune <= 65479) ||
         (rune >= 65482 && rune <= 65487) || (rune >= 65490 && rune <= 65495) ||
         (rune >= 65498 && rune <= 65500) || (rune >= 65536 && rune <= 65547) ||
         (rune >= 65549 && rune <= 65574) || (rune >= 65576 && rune <= 65594) ||
         (rune >= 65596 && rune <= 65597) || (rune >= 65599 && rune <= 65613) ||
         (rune >= 65616 && rune <= 65629) || (rune >= 65664 && rune <= 65786) ||
         (rune >= 65856 && rune <= 65908) || (rune >= 66176 && rune <= 66204) ||
         (rune >= 66208 && rune <= 66256) || (rune >= 66304 && rune <= 66335) ||
         (rune >= 66349 && rune <= 66378) || (rune >= 66384 && rune <= 66421) ||
         (rune >= 66432 && rune <= 66461) || (rune >= 66464 && rune <= 66499) ||
         (rune >= 66504 && rune <= 66511) || (rune >= 66513 && rune <= 66517) ||
         (rune >= 66560 && rune <= 66717) || (rune >= 66736 && rune <= 66771) ||
         (rune >= 66776 && rune <= 66811) || (rune >= 66816 && rune <= 66855) ||
         (rune >= 66864 && rune <= 66915) || (rune >= 67072 && rune <= 67382) ||
         (rune >= 67392 && rune <= 67413) || (rune >= 67424 && rune <= 67431) ||
         (rune >= 67584 && rune <= 67589) || (rune >= 67592 && rune <= 67592) ||
         (rune >= 67594 && rune <= 67637) || (rune >= 67639 && rune <= 67640) ||
         (rune >= 67644 && rune <= 67644) || (rune >= 67647 && rune <= 67669) ||
         (rune >= 67680 && rune <= 67702) || (rune >= 67712 && rune <= 67742) ||
         (rune >= 67808 && rune <= 67826) || (rune >= 67828 && rune <= 67829) ||
         (rune >= 67840 && rune <= 67861) || (rune >= 67872 && rune <= 67897) ||
         (rune >= 67968 && rune <= 68023) || (rune >= 68030 && rune <= 68031) ||
         (rune >= 68096 && rune <= 68096) || (rune >= 68112 && rune <= 68115) ||
         (rune >= 68117 && rune <= 68119) || (rune >= 68121 && rune <= 68149) ||
         (rune >= 68192 && rune <= 68220) || (rune >= 68224 && rune <= 68252) ||
         (rune >= 68288 && rune <= 68295) || (rune >= 68297 && rune <= 68324) ||
         (rune >= 68352 && rune <= 68405) || (rune >= 68416 && rune <= 68437) ||
         (rune >= 68448 && rune <= 68466) || (rune >= 68480 && rune <= 68497) ||
         (rune >= 68608 && rune <= 68680) || (rune >= 68736 && rune <= 68786) ||
         (rune >= 68800 && rune <= 68850) || (rune >= 68864 && rune <= 68899) ||
         (rune >= 69376 && rune <= 69404) || (rune >= 69415 && rune <= 69415) ||
         (rune >= 69424 && rune <= 69445) || (rune >= 69635 && rune <= 69687) ||
         (rune >= 69763 && rune <= 69807) || (rune >= 69840 && rune <= 69864) ||
         (rune >= 69891 && rune <= 69926) || (rune >= 69956 && rune <= 69956) ||
         (rune >= 69968 && rune <= 70002) || (rune >= 70006 && rune <= 70006) ||
         (rune >= 70019 && rune <= 70066) || (rune >= 70081 && rune <= 70084) ||
         (rune >= 70106 && rune <= 70106) || (rune >= 70108 && rune <= 70108) ||
         (rune >= 70144 && rune <= 70161) || (rune >= 70163 && rune <= 70187) ||
         (rune >= 70272 && rune <= 70278) || (rune >= 70280 && rune <= 70280) ||
         (rune >= 70282 && rune <= 70285) || (rune >= 70287 && rune <= 70301) ||
         (rune >= 70303 && rune <= 70312) || (rune >= 70320 && rune <= 70366) ||
         (rune >= 70405 && rune <= 70412) || (rune >= 70415 && rune <= 70416) ||
         (rune >= 70419 && rune <= 70440) || (rune >= 70442 && rune <= 70448) ||
         (rune >= 70450 && rune <= 70451) || (rune >= 70453 && rune <= 70457) ||
         (rune >= 70461 && rune <= 70461) || (rune >= 70480 && rune <= 70480) ||
         (rune >= 70493 && rune <= 70497) || (rune >= 70656 && rune <= 70708) ||
         (rune >= 70727 && rune <= 70730) || (rune >= 70784 && rune <= 70831) ||
         (rune >= 70852 && rune <= 70853) || (rune >= 70855 && rune <= 70855) ||
         (rune >= 71040 && rune <= 71086) || (rune >= 71128 && rune <= 71131) ||
         (rune >= 71168 && rune <= 71215) || (rune >= 71236 && rune <= 71236) ||
         (rune >= 71296 && rune <= 71338) || (rune >= 71424 && rune <= 71450) ||
         (rune >= 71680 && rune <= 71723) || (rune >= 71840 && rune <= 71903) ||
         (rune >= 71935 && rune <= 71935) || (rune >= 72192 && rune <= 72192) ||
         (rune >= 72203 && rune <= 72242) || (rune >= 72250 && rune <= 72250) ||
         (rune >= 72272 && rune <= 72272) || (rune >= 72284 && rune <= 72323) ||
         (rune >= 72326 && rune <= 72329) || (rune >= 72349 && rune <= 72349) ||
         (rune >= 72384 && rune <= 72440) || (rune >= 72704 && rune <= 72712) ||
         (rune >= 72714 && rune <= 72750) || (rune >= 72768 && rune <= 72768) ||
         (rune >= 72818 && rune <= 72847) || (rune >= 72960 && rune <= 72966) ||
         (rune >= 72968 && rune <= 72969) || (rune >= 72971 && rune <= 73008) ||
         (rune >= 73030 && rune <= 73030) || (rune >= 73056 && rune <= 73061) ||
         (rune >= 73063 && rune <= 73064) || (rune >= 73066 && rune <= 73097) ||
         (rune >= 73112 && rune <= 73112) || (rune >= 73440 && rune <= 73458) ||
         (rune >= 73728 && rune <= 74649) || (rune >= 74752 && rune <= 74862) ||
         (rune >= 74880 && rune <= 75075) || (rune >= 77824 && rune <= 78894) ||
         (rune >= 82944 && rune <= 83526) || (rune >= 92160 && rune <= 92728) ||
         (rune >= 92736 && rune <= 92766) || (rune >= 92880 && rune <= 92909) ||
         (rune >= 92928 && rune <= 92975) || (rune >= 92992 && rune <= 92995) ||
         (rune >= 93027 && rune <= 93047) || (rune >= 93053 && rune <= 93071) ||
         (rune >= 93760 && rune <= 93823) || (rune >= 93952 && rune <= 94020) ||
         (rune >= 94032 && rune <= 94032) || (rune >= 94099 && rune <= 94111) ||
         (rune >= 94176 && rune <= 94177) || (rune >= 94208 && rune <= 94208) ||
         (rune >= 100337 && rune <= 100337) ||
         (rune >= 100352 && rune <= 101106) ||
         (rune >= 110592 && rune <= 110878) ||
         (rune >= 110960 && rune <= 111355) ||
         (rune >= 113664 && rune <= 113770) ||
         (rune >= 113776 && rune <= 113788) ||
         (rune >= 113792 && rune <= 113800) ||
         (rune >= 113808 && rune <= 113817) ||
         (rune >= 119808 && rune <= 119892) ||
         (rune >= 119894 && rune <= 119964) ||
         (rune >= 119966 && rune <= 119967) ||
         (rune >= 119970 && rune <= 119970) ||
         (rune >= 119973 && rune <= 119974) ||
         (rune >= 119977 && rune <= 119980) ||
         (rune >= 119982 && rune <= 119993) ||
         (rune >= 119995 && rune <= 119995) ||
         (rune >= 119997 && rune <= 120003) ||
         (rune >= 120005 && rune <= 120069) ||
         (rune >= 120071 && rune <= 120074) ||
         (rune >= 120077 && rune <= 120084) ||
         (rune >= 120086 && rune <= 120092) ||
         (rune >= 120094 && rune <= 120121) ||
         (rune >= 120123 && rune <= 120126) ||
         (rune >= 120128 && rune <= 120132) ||
         (rune >= 120134 && rune <= 120134) ||
         (rune >= 120138 && rune <= 120144) ||
         (rune >= 120146 && rune <= 120485) ||
         (rune >= 120488 && rune <= 120512) ||
         (rune >= 120514 && rune <= 120538) ||
         (rune >= 120540 && rune <= 120570) ||
         (rune >= 120572 && rune <= 120596) ||
         (rune >= 120598 && rune <= 120628) ||
         (rune >= 120630 && rune <= 120654) ||
         (rune >= 120656 && rune <= 120686) ||
         (rune >= 120688 && rune <= 120712) ||
         (rune >= 120714 && rune <= 120744) ||
         (rune >= 120746 && rune <= 120770) ||
         (rune >= 120772 && rune <= 120779) ||
         (rune >= 124928 && rune <= 125124) ||
         (rune >= 125184 && rune <= 125251) ||
         (rune >= 126464 && rune <= 126467) ||
         (rune >= 126469 && rune <= 126495) ||
         (rune >= 126497 && rune <= 126498) ||
         (rune >= 126500 && rune <= 126500) ||
         (rune >= 126503 && rune <= 126503) ||
         (rune >= 126505 && rune <= 126514) ||
         (rune >= 126516 && rune <= 126519) ||
         (rune >= 126521 && rune <= 126521) ||
         (rune >= 126523 && rune <= 126523) ||
         (rune >= 126530 && rune <= 126530) ||
         (rune >= 126535 && rune <= 126535) ||
         (rune >= 126537 && rune <= 126537) ||
         (rune >= 126539 && rune <= 126539) ||
         (rune >= 126541 && rune <= 126543) ||
         (rune >= 126545 && rune <= 126546) ||
         (rune >= 126548 && rune <= 126548) ||
         (rune >= 126551 && rune <= 126551) ||
         (rune >= 126553 && rune <= 126553) ||
         (rune >= 126555 && rune <= 126555) ||
         (rune >= 126557 && rune <= 126557) ||
         (rune >= 126559 && rune <= 126559) ||
         (rune >= 126561 && rune <= 126562) ||
         (rune >= 126564 && rune <= 126564) ||
         (rune >= 126567 && rune <= 126570) ||
         (rune >= 126572 && rune <= 126578) ||
         (rune >= 126580 && rune <= 126583) ||
         (rune >= 126585 && rune <= 126588) ||
         (rune >= 126590 && rune <= 126590) ||
         (rune >= 126592 && rune <= 126601) ||
         (rune >= 126603 && rune <= 126619) ||
         (rune >= 126625 && rune <= 126627) ||
         (rune >= 126629 && rune <= 126633) ||
         (rune >= 126635 && rune <= 126651) ||
         (rune >= 131072 && rune <= 131072) ||
         (rune >= 173782 && rune <= 173782) ||
         (rune >= 173824 && rune <= 173824) ||
         (rune >= 177972 && rune <= 177972) ||
         (rune >= 177984 && rune <= 177984) ||
         (rune >= 178205 && rune <= 178205) ||
         (rune >= 178208 && rune <= 178208) ||
         (rune >= 183969 && rune <= 183969) ||
         (rune >= 183984 && rune <= 183984) ||
         (rune >= 191456 && rune <= 191456) ||
         (rune >= 194560 && rune <= 195101);
}

bool is_identifier_part_rune(uint32_t rune) {
  // Any code point in Lo, Pc, Lm, Cf, Ll, Nd, Nl, Lt, Lu, Mc, Mn
  return (rune >= 48 && rune <= 57) || (rune >= 65 && rune <= 90) ||
         (rune >= 95 && rune <= 95) || (rune >= 97 && rune <= 122) ||
         (rune >= 170 && rune <= 170) || (rune >= 173 && rune <= 173) ||
         (rune >= 181 && rune <= 181) || (rune >= 186 && rune <= 186) ||
         (rune >= 192 && rune <= 214) || (rune >= 216 && rune <= 246) ||
         (rune >= 248 && rune <= 705) || (rune >= 710 && rune <= 721) ||
         (rune >= 736 && rune <= 740) || (rune >= 748 && rune <= 748) ||
         (rune >= 750 && rune <= 750) || (rune >= 768 && rune <= 884) ||
         (rune >= 886 && rune <= 887) || (rune >= 890 && rune <= 893) ||
         (rune >= 895 && rune <= 895) || (rune >= 902 && rune <= 902) ||
         (rune >= 904 && rune <= 906) || (rune >= 908 && rune <= 908) ||
         (rune >= 910 && rune <= 929) || (rune >= 931 && rune <= 1013) ||
         (rune >= 1015 && rune <= 1153) || (rune >= 1155 && rune <= 1159) ||
         (rune >= 1162 && rune <= 1327) || (rune >= 1329 && rune <= 1366) ||
         (rune >= 1369 && rune <= 1369) || (rune >= 1376 && rune <= 1416) ||
         (rune >= 1425 && rune <= 1469) || (rune >= 1471 && rune <= 1471) ||
         (rune >= 1473 && rune <= 1474) || (rune >= 1476 && rune <= 1477) ||
         (rune >= 1479 && rune <= 1479) || (rune >= 1488 && rune <= 1514) ||
         (rune >= 1519 && rune <= 1522) || (rune >= 1536 && rune <= 1541) ||
         (rune >= 1552 && rune <= 1562) || (rune >= 1564 && rune <= 1564) ||
         (rune >= 1568 && rune <= 1641) || (rune >= 1646 && rune <= 1747) ||
         (rune >= 1749 && rune <= 1757) || (rune >= 1759 && rune <= 1768) ||
         (rune >= 1770 && rune <= 1788) || (rune >= 1791 && rune <= 1791) ||
         (rune >= 1807 && rune <= 1866) || (rune >= 1869 && rune <= 1969) ||
         (rune >= 1984 && rune <= 2037) || (rune >= 2042 && rune <= 2042) ||
         (rune >= 2045 && rune <= 2045) || (rune >= 2048 && rune <= 2093) ||
         (rune >= 2112 && rune <= 2139) || (rune >= 2144 && rune <= 2154) ||
         (rune >= 2208 && rune <= 2228) || (rune >= 2230 && rune <= 2237) ||
         (rune >= 2259 && rune <= 2403) || (rune >= 2406 && rune <= 2415) ||
         (rune >= 2417 && rune <= 2435) || (rune >= 2437 && rune <= 2444) ||
         (rune >= 2447 && rune <= 2448) || (rune >= 2451 && rune <= 2472) ||
         (rune >= 2474 && rune <= 2480) || (rune >= 2482 && rune <= 2482) ||
         (rune >= 2486 && rune <= 2489) || (rune >= 2492 && rune <= 2500) ||
         (rune >= 2503 && rune <= 2504) || (rune >= 2507 && rune <= 2510) ||
         (rune >= 2519 && rune <= 2519) || (rune >= 2524 && rune <= 2525) ||
         (rune >= 2527 && rune <= 2531) || (rune >= 2534 && rune <= 2545) ||
         (rune >= 2556 && rune <= 2556) || (rune >= 2558 && rune <= 2558) ||
         (rune >= 2561 && rune <= 2563) || (rune >= 2565 && rune <= 2570) ||
         (rune >= 2575 && rune <= 2576) || (rune >= 2579 && rune <= 2600) ||
         (rune >= 2602 && rune <= 2608) || (rune >= 2610 && rune <= 2611) ||
         (rune >= 2613 && rune <= 2614) || (rune >= 2616 && rune <= 2617) ||
         (rune >= 2620 && rune <= 2620) || (rune >= 2622 && rune <= 2626) ||
         (rune >= 2631 && rune <= 2632) || (rune >= 2635 && rune <= 2637) ||
         (rune >= 2641 && rune <= 2641) || (rune >= 2649 && rune <= 2652) ||
         (rune >= 2654 && rune <= 2654) || (rune >= 2662 && rune <= 2677) ||
         (rune >= 2689 && rune <= 2691) || (rune >= 2693 && rune <= 2701) ||
         (rune >= 2703 && rune <= 2705) || (rune >= 2707 && rune <= 2728) ||
         (rune >= 2730 && rune <= 2736) || (rune >= 2738 && rune <= 2739) ||
         (rune >= 2741 && rune <= 2745) || (rune >= 2748 && rune <= 2757) ||
         (rune >= 2759 && rune <= 2761) || (rune >= 2763 && rune <= 2765) ||
         (rune >= 2768 && rune <= 2768) || (rune >= 2784 && rune <= 2787) ||
         (rune >= 2790 && rune <= 2799) || (rune >= 2809 && rune <= 2815) ||
         (rune >= 2817 && rune <= 2819) || (rune >= 2821 && rune <= 2828) ||
         (rune >= 2831 && rune <= 2832) || (rune >= 2835 && rune <= 2856) ||
         (rune >= 2858 && rune <= 2864) || (rune >= 2866 && rune <= 2867) ||
         (rune >= 2869 && rune <= 2873) || (rune >= 2876 && rune <= 2884) ||
         (rune >= 2887 && rune <= 2888) || (rune >= 2891 && rune <= 2893) ||
         (rune >= 2902 && rune <= 2903) || (rune >= 2908 && rune <= 2909) ||
         (rune >= 2911 && rune <= 2915) || (rune >= 2918 && rune <= 2927) ||
         (rune >= 2929 && rune <= 2929) || (rune >= 2946 && rune <= 2947) ||
         (rune >= 2949 && rune <= 2954) || (rune >= 2958 && rune <= 2960) ||
         (rune >= 2962 && rune <= 2965) || (rune >= 2969 && rune <= 2970) ||
         (rune >= 2972 && rune <= 2972) || (rune >= 2974 && rune <= 2975) ||
         (rune >= 2979 && rune <= 2980) || (rune >= 2984 && rune <= 2986) ||
         (rune >= 2990 && rune <= 3001) || (rune >= 3006 && rune <= 3010) ||
         (rune >= 3014 && rune <= 3016) || (rune >= 3018 && rune <= 3021) ||
         (rune >= 3024 && rune <= 3024) || (rune >= 3031 && rune <= 3031) ||
         (rune >= 3046 && rune <= 3055) || (rune >= 3072 && rune <= 3084) ||
         (rune >= 3086 && rune <= 3088) || (rune >= 3090 && rune <= 3112) ||
         (rune >= 3114 && rune <= 3129) || (rune >= 3133 && rune <= 3140) ||
         (rune >= 3142 && rune <= 3144) || (rune >= 3146 && rune <= 3149) ||
         (rune >= 3157 && rune <= 3158) || (rune >= 3160 && rune <= 3162) ||
         (rune >= 3168 && rune <= 3171) || (rune >= 3174 && rune <= 3183) ||
         (rune >= 3200 && rune <= 3203) || (rune >= 3205 && rune <= 3212) ||
         (rune >= 3214 && rune <= 3216) || (rune >= 3218 && rune <= 3240) ||
         (rune >= 3242 && rune <= 3251) || (rune >= 3253 && rune <= 3257) ||
         (rune >= 3260 && rune <= 3268) || (rune >= 3270 && rune <= 3272) ||
         (rune >= 3274 && rune <= 3277) || (rune >= 3285 && rune <= 3286) ||
         (rune >= 3294 && rune <= 3294) || (rune >= 3296 && rune <= 3299) ||
         (rune >= 3302 && rune <= 3311) || (rune >= 3313 && rune <= 3314) ||
         (rune >= 3328 && rune <= 3331) || (rune >= 3333 && rune <= 3340) ||
         (rune >= 3342 && rune <= 3344) || (rune >= 3346 && rune <= 3396) ||
         (rune >= 3398 && rune <= 3400) || (rune >= 3402 && rune <= 3406) ||
         (rune >= 3412 && rune <= 3415) || (rune >= 3423 && rune <= 3427) ||
         (rune >= 3430 && rune <= 3439) || (rune >= 3450 && rune <= 3455) ||
         (rune >= 3458 && rune <= 3459) || (rune >= 3461 && rune <= 3478) ||
         (rune >= 3482 && rune <= 3505) || (rune >= 3507 && rune <= 3515) ||
         (rune >= 3517 && rune <= 3517) || (rune >= 3520 && rune <= 3526) ||
         (rune >= 3530 && rune <= 3530) || (rune >= 3535 && rune <= 3540) ||
         (rune >= 3542 && rune <= 3542) || (rune >= 3544 && rune <= 3551) ||
         (rune >= 3558 && rune <= 3567) || (rune >= 3570 && rune <= 3571) ||
         (rune >= 3585 && rune <= 3642) || (rune >= 3648 && rune <= 3662) ||
         (rune >= 3664 && rune <= 3673) || (rune >= 3713 && rune <= 3714) ||
         (rune >= 3716 && rune <= 3716) || (rune >= 3719 && rune <= 3720) ||
         (rune >= 3722 && rune <= 3722) || (rune >= 3725 && rune <= 3725) ||
         (rune >= 3732 && rune <= 3735) || (rune >= 3737 && rune <= 3743) ||
         (rune >= 3745 && rune <= 3747) || (rune >= 3749 && rune <= 3749) ||
         (rune >= 3751 && rune <= 3751) || (rune >= 3754 && rune <= 3755) ||
         (rune >= 3757 && rune <= 3769) || (rune >= 3771 && rune <= 3773) ||
         (rune >= 3776 && rune <= 3780) || (rune >= 3782 && rune <= 3782) ||
         (rune >= 3784 && rune <= 3789) || (rune >= 3792 && rune <= 3801) ||
         (rune >= 3804 && rune <= 3807) || (rune >= 3840 && rune <= 3840) ||
         (rune >= 3864 && rune <= 3865) || (rune >= 3872 && rune <= 3881) ||
         (rune >= 3893 && rune <= 3893) || (rune >= 3895 && rune <= 3895) ||
         (rune >= 3897 && rune <= 3897) || (rune >= 3902 && rune <= 3911) ||
         (rune >= 3913 && rune <= 3948) || (rune >= 3953 && rune <= 3972) ||
         (rune >= 3974 && rune <= 3991) || (rune >= 3993 && rune <= 4028) ||
         (rune >= 4038 && rune <= 4038) || (rune >= 4096 && rune <= 4169) ||
         (rune >= 4176 && rune <= 4253) || (rune >= 4256 && rune <= 4293) ||
         (rune >= 4295 && rune <= 4295) || (rune >= 4301 && rune <= 4301) ||
         (rune >= 4304 && rune <= 4346) || (rune >= 4348 && rune <= 4680) ||
         (rune >= 4682 && rune <= 4685) || (rune >= 4688 && rune <= 4694) ||
         (rune >= 4696 && rune <= 4696) || (rune >= 4698 && rune <= 4701) ||
         (rune >= 4704 && rune <= 4744) || (rune >= 4746 && rune <= 4749) ||
         (rune >= 4752 && rune <= 4784) || (rune >= 4786 && rune <= 4789) ||
         (rune >= 4792 && rune <= 4798) || (rune >= 4800 && rune <= 4800) ||
         (rune >= 4802 && rune <= 4805) || (rune >= 4808 && rune <= 4822) ||
         (rune >= 4824 && rune <= 4880) || (rune >= 4882 && rune <= 4885) ||
         (rune >= 4888 && rune <= 4954) || (rune >= 4957 && rune <= 4959) ||
         (rune >= 4992 && rune <= 5007) || (rune >= 5024 && rune <= 5109) ||
         (rune >= 5112 && rune <= 5117) || (rune >= 5121 && rune <= 5740) ||
         (rune >= 5743 && rune <= 5759) || (rune >= 5761 && rune <= 5786) ||
         (rune >= 5792 && rune <= 5866) || (rune >= 5870 && rune <= 5880) ||
         (rune >= 5888 && rune <= 5900) || (rune >= 5902 && rune <= 5908) ||
         (rune >= 5920 && rune <= 5940) || (rune >= 5952 && rune <= 5971) ||
         (rune >= 5984 && rune <= 5996) || (rune >= 5998 && rune <= 6000) ||
         (rune >= 6002 && rune <= 6003) || (rune >= 6016 && rune <= 6099) ||
         (rune >= 6103 && rune <= 6103) || (rune >= 6108 && rune <= 6109) ||
         (rune >= 6112 && rune <= 6121) || (rune >= 6155 && rune <= 6158) ||
         (rune >= 6160 && rune <= 6169) || (rune >= 6176 && rune <= 6264) ||
         (rune >= 6272 && rune <= 6314) || (rune >= 6320 && rune <= 6389) ||
         (rune >= 6400 && rune <= 6430) || (rune >= 6432 && rune <= 6443) ||
         (rune >= 6448 && rune <= 6459) || (rune >= 6470 && rune <= 6509) ||
         (rune >= 6512 && rune <= 6516) || (rune >= 6528 && rune <= 6571) ||
         (rune >= 6576 && rune <= 6601) || (rune >= 6608 && rune <= 6617) ||
         (rune >= 6656 && rune <= 6683) || (rune >= 6688 && rune <= 6750) ||
         (rune >= 6752 && rune <= 6780) || (rune >= 6783 && rune <= 6793) ||
         (rune >= 6800 && rune <= 6809) || (rune >= 6823 && rune <= 6823) ||
         (rune >= 6832 && rune <= 6845) || (rune >= 6912 && rune <= 6987) ||
         (rune >= 6992 && rune <= 7001) || (rune >= 7019 && rune <= 7027) ||
         (rune >= 7040 && rune <= 7155) || (rune >= 7168 && rune <= 7223) ||
         (rune >= 7232 && rune <= 7241) || (rune >= 7245 && rune <= 7293) ||
         (rune >= 7296 && rune <= 7304) || (rune >= 7312 && rune <= 7354) ||
         (rune >= 7357 && rune <= 7359) || (rune >= 7376 && rune <= 7378) ||
         (rune >= 7380 && rune <= 7417) || (rune >= 7424 && rune <= 7673) ||
         (rune >= 7675 && rune <= 7957) || (rune >= 7960 && rune <= 7965) ||
         (rune >= 7968 && rune <= 8005) || (rune >= 8008 && rune <= 8013) ||
         (rune >= 8016 && rune <= 8023) || (rune >= 8025 && rune <= 8025) ||
         (rune >= 8027 && rune <= 8027) || (rune >= 8029 && rune <= 8029) ||
         (rune >= 8031 && rune <= 8061) || (rune >= 8064 && rune <= 8116) ||
         (rune >= 8118 && rune <= 8124) || (rune >= 8126 && rune <= 8126) ||
         (rune >= 8130 && rune <= 8132) || (rune >= 8134 && rune <= 8140) ||
         (rune >= 8144 && rune <= 8147) || (rune >= 8150 && rune <= 8155) ||
         (rune >= 8160 && rune <= 8172) || (rune >= 8178 && rune <= 8180) ||
         (rune >= 8182 && rune <= 8188) || (rune >= 8203 && rune <= 8207) ||
         (rune >= 8234 && rune <= 8238) || (rune >= 8255 && rune <= 8256) ||
         (rune >= 8276 && rune <= 8276) || (rune >= 8288 && rune <= 8292) ||
         (rune >= 8294 && rune <= 8303) || (rune >= 8305 && rune <= 8305) ||
         (rune >= 8319 && rune <= 8319) || (rune >= 8336 && rune <= 8348) ||
         (rune >= 8400 && rune <= 8412) || (rune >= 8417 && rune <= 8417) ||
         (rune >= 8421 && rune <= 8432) || (rune >= 8450 && rune <= 8450) ||
         (rune >= 8455 && rune <= 8455) || (rune >= 8458 && rune <= 8467) ||
         (rune >= 8469 && rune <= 8469) || (rune >= 8473 && rune <= 8477) ||
         (rune >= 8484 && rune <= 8484) || (rune >= 8486 && rune <= 8486) ||
         (rune >= 8488 && rune <= 8488) || (rune >= 8490 && rune <= 8493) ||
         (rune >= 8495 && rune <= 8505) || (rune >= 8508 && rune <= 8511) ||
         (rune >= 8517 && rune <= 8521) || (rune >= 8526 && rune <= 8526) ||
         (rune >= 8544 && rune <= 8584) || (rune >= 11264 && rune <= 11310) ||
         (rune >= 11312 && rune <= 11358) || (rune >= 11360 && rune <= 11492) ||
         (rune >= 11499 && rune <= 11507) || (rune >= 11520 && rune <= 11557) ||
         (rune >= 11559 && rune <= 11559) || (rune >= 11565 && rune <= 11565) ||
         (rune >= 11568 && rune <= 11623) || (rune >= 11631 && rune <= 11631) ||
         (rune >= 11647 && rune <= 11670) || (rune >= 11680 && rune <= 11686) ||
         (rune >= 11688 && rune <= 11694) || (rune >= 11696 && rune <= 11702) ||
         (rune >= 11704 && rune <= 11710) || (rune >= 11712 && rune <= 11718) ||
         (rune >= 11720 && rune <= 11726) || (rune >= 11728 && rune <= 11734) ||
         (rune >= 11736 && rune <= 11742) || (rune >= 11744 && rune <= 11775) ||
         (rune >= 11823 && rune <= 11823) || (rune >= 12293 && rune <= 12295) ||
         (rune >= 12321 && rune <= 12335) || (rune >= 12337 && rune <= 12341) ||
         (rune >= 12344 && rune <= 12348) || (rune >= 12353 && rune <= 12438) ||
         (rune >= 12441 && rune <= 12442) || (rune >= 12445 && rune <= 12447) ||
         (rune >= 12449 && rune <= 12538) || (rune >= 12540 && rune <= 12543) ||
         (rune >= 12549 && rune <= 12591) || (rune >= 12593 && rune <= 12686) ||
         (rune >= 12704 && rune <= 12730) || (rune >= 12784 && rune <= 12799) ||
         (rune >= 13312 && rune <= 13312) || (rune >= 19893 && rune <= 19893) ||
         (rune >= 19968 && rune <= 19968) || (rune >= 40943 && rune <= 40943) ||
         (rune >= 40960 && rune <= 42124) || (rune >= 42192 && rune <= 42237) ||
         (rune >= 42240 && rune <= 42508) || (rune >= 42512 && rune <= 42539) ||
         (rune >= 42560 && rune <= 42607) || (rune >= 42612 && rune <= 42621) ||
         (rune >= 42623 && rune <= 42737) || (rune >= 42775 && rune <= 42783) ||
         (rune >= 42786 && rune <= 42888) || (rune >= 42891 && rune <= 42937) ||
         (rune >= 42999 && rune <= 43047) || (rune >= 43072 && rune <= 43123) ||
         (rune >= 43136 && rune <= 43205) || (rune >= 43216 && rune <= 43225) ||
         (rune >= 43232 && rune <= 43255) || (rune >= 43259 && rune <= 43259) ||
         (rune >= 43261 && rune <= 43309) || (rune >= 43312 && rune <= 43347) ||
         (rune >= 43360 && rune <= 43388) || (rune >= 43392 && rune <= 43456) ||
         (rune >= 43471 && rune <= 43481) || (rune >= 43488 && rune <= 43518) ||
         (rune >= 43520 && rune <= 43574) || (rune >= 43584 && rune <= 43597) ||
         (rune >= 43600 && rune <= 43609) || (rune >= 43616 && rune <= 43638) ||
         (rune >= 43642 && rune <= 43714) || (rune >= 43739 && rune <= 43741) ||
         (rune >= 43744 && rune <= 43759) || (rune >= 43762 && rune <= 43766) ||
         (rune >= 43777 && rune <= 43782) || (rune >= 43785 && rune <= 43790) ||
         (rune >= 43793 && rune <= 43798) || (rune >= 43808 && rune <= 43814) ||
         (rune >= 43816 && rune <= 43822) || (rune >= 43824 && rune <= 43866) ||
         (rune >= 43868 && rune <= 43877) || (rune >= 43888 && rune <= 44010) ||
         (rune >= 44012 && rune <= 44013) || (rune >= 44016 && rune <= 44025) ||
         (rune >= 44032 && rune <= 44032) || (rune >= 55203 && rune <= 55203) ||
         (rune >= 55216 && rune <= 55238) || (rune >= 55243 && rune <= 55291) ||
         (rune >= 63744 && rune <= 64109) || (rune >= 64112 && rune <= 64217) ||
         (rune >= 64256 && rune <= 64262) || (rune >= 64275 && rune <= 64279) ||
         (rune >= 64285 && rune <= 64296) || (rune >= 64298 && rune <= 64310) ||
         (rune >= 64312 && rune <= 64316) || (rune >= 64318 && rune <= 64318) ||
         (rune >= 64320 && rune <= 64321) || (rune >= 64323 && rune <= 64324) ||
         (rune >= 64326 && rune <= 64433) || (rune >= 64467 && rune <= 64829) ||
         (rune >= 64848 && rune <= 64911) || (rune >= 64914 && rune <= 64967) ||
         (rune >= 65008 && rune <= 65019) || (rune >= 65024 && rune <= 65039) ||
         (rune >= 65056 && rune <= 65071) || (rune >= 65075 && rune <= 65076) ||
         (rune >= 65101 && rune <= 65103) || (rune >= 65136 && rune <= 65140) ||
         (rune >= 65142 && rune <= 65276) || (rune >= 65279 && rune <= 65279) ||
         (rune >= 65296 && rune <= 65305) || (rune >= 65313 && rune <= 65338) ||
         (rune >= 65343 && rune <= 65343) || (rune >= 65345 && rune <= 65370) ||
         (rune >= 65382 && rune <= 65470) || (rune >= 65474 && rune <= 65479) ||
         (rune >= 65482 && rune <= 65487) || (rune >= 65490 && rune <= 65495) ||
         (rune >= 65498 && rune <= 65500) || (rune >= 65529 && rune <= 65531) ||
         (rune >= 65536 && rune <= 65547) || (rune >= 65549 && rune <= 65574) ||
         (rune >= 65576 && rune <= 65594) || (rune >= 65596 && rune <= 65597) ||
         (rune >= 65599 && rune <= 65613) || (rune >= 65616 && rune <= 65629) ||
         (rune >= 65664 && rune <= 65786) || (rune >= 65856 && rune <= 65908) ||
         (rune >= 66045 && rune <= 66045) || (rune >= 66176 && rune <= 66204) ||
         (rune >= 66208 && rune <= 66256) || (rune >= 66272 && rune <= 66272) ||
         (rune >= 66304 && rune <= 66335) || (rune >= 66349 && rune <= 66378) ||
         (rune >= 66384 && rune <= 66426) || (rune >= 66432 && rune <= 66461) ||
         (rune >= 66464 && rune <= 66499) || (rune >= 66504 && rune <= 66511) ||
         (rune >= 66513 && rune <= 66517) || (rune >= 66560 && rune <= 66717) ||
         (rune >= 66720 && rune <= 66729) || (rune >= 66736 && rune <= 66771) ||
         (rune >= 66776 && rune <= 66811) || (rune >= 66816 && rune <= 66855) ||
         (rune >= 66864 && rune <= 66915) || (rune >= 67072 && rune <= 67382) ||
         (rune >= 67392 && rune <= 67413) || (rune >= 67424 && rune <= 67431) ||
         (rune >= 67584 && rune <= 67589) || (rune >= 67592 && rune <= 67592) ||
         (rune >= 67594 && rune <= 67637) || (rune >= 67639 && rune <= 67640) ||
         (rune >= 67644 && rune <= 67644) || (rune >= 67647 && rune <= 67669) ||
         (rune >= 67680 && rune <= 67702) || (rune >= 67712 && rune <= 67742) ||
         (rune >= 67808 && rune <= 67826) || (rune >= 67828 && rune <= 67829) ||
         (rune >= 67840 && rune <= 67861) || (rune >= 67872 && rune <= 67897) ||
         (rune >= 67968 && rune <= 68023) || (rune >= 68030 && rune <= 68031) ||
         (rune >= 68096 && rune <= 68099) || (rune >= 68101 && rune <= 68102) ||
         (rune >= 68108 && rune <= 68115) || (rune >= 68117 && rune <= 68119) ||
         (rune >= 68121 && rune <= 68149) || (rune >= 68152 && rune <= 68154) ||
         (rune >= 68159 && rune <= 68159) || (rune >= 68192 && rune <= 68220) ||
         (rune >= 68224 && rune <= 68252) || (rune >= 68288 && rune <= 68295) ||
         (rune >= 68297 && rune <= 68326) || (rune >= 68352 && rune <= 68405) ||
         (rune >= 68416 && rune <= 68437) || (rune >= 68448 && rune <= 68466) ||
         (rune >= 68480 && rune <= 68497) || (rune >= 68608 && rune <= 68680) ||
         (rune >= 68736 && rune <= 68786) || (rune >= 68800 && rune <= 68850) ||
         (rune >= 68864 && rune <= 68903) || (rune >= 68912 && rune <= 68921) ||
         (rune >= 69376 && rune <= 69404) || (rune >= 69415 && rune <= 69415) ||
         (rune >= 69424 && rune <= 69456) || (rune >= 69632 && rune <= 69702) ||
         (rune >= 69734 && rune <= 69743) || (rune >= 69759 && rune <= 69818) ||
         (rune >= 69821 && rune <= 69821) || (rune >= 69837 && rune <= 69837) ||
         (rune >= 69840 && rune <= 69864) || (rune >= 69872 && rune <= 69881) ||
         (rune >= 69888 && rune <= 69940) || (rune >= 69942 && rune <= 69951) ||
         (rune >= 69956 && rune <= 69958) || (rune >= 69968 && rune <= 70003) ||
         (rune >= 70006 && rune <= 70006) || (rune >= 70016 && rune <= 70084) ||
         (rune >= 70089 && rune <= 70092) || (rune >= 70096 && rune <= 70106) ||
         (rune >= 70108 && rune <= 70108) || (rune >= 70144 && rune <= 70161) ||
         (rune >= 70163 && rune <= 70199) || (rune >= 70206 && rune <= 70206) ||
         (rune >= 70272 && rune <= 70278) || (rune >= 70280 && rune <= 70280) ||
         (rune >= 70282 && rune <= 70285) || (rune >= 70287 && rune <= 70301) ||
         (rune >= 70303 && rune <= 70312) || (rune >= 70320 && rune <= 70378) ||
         (rune >= 70384 && rune <= 70393) || (rune >= 70400 && rune <= 70403) ||
         (rune >= 70405 && rune <= 70412) || (rune >= 70415 && rune <= 70416) ||
         (rune >= 70419 && rune <= 70440) || (rune >= 70442 && rune <= 70448) ||
         (rune >= 70450 && rune <= 70451) || (rune >= 70453 && rune <= 70457) ||
         (rune >= 70459 && rune <= 70468) || (rune >= 70471 && rune <= 70472) ||
         (rune >= 70475 && rune <= 70477) || (rune >= 70480 && rune <= 70480) ||
         (rune >= 70487 && rune <= 70487) || (rune >= 70493 && rune <= 70499) ||
         (rune >= 70502 && rune <= 70508) || (rune >= 70512 && rune <= 70516) ||
         (rune >= 70656 && rune <= 70730) || (rune >= 70736 && rune <= 70745) ||
         (rune >= 70750 && rune <= 70750) || (rune >= 70784 && rune <= 70853) ||
         (rune >= 70855 && rune <= 70855) || (rune >= 70864 && rune <= 70873) ||
         (rune >= 71040 && rune <= 71093) || (rune >= 71096 && rune <= 71104) ||
         (rune >= 71128 && rune <= 71133) || (rune >= 71168 && rune <= 71232) ||
         (rune >= 71236 && rune <= 71236) || (rune >= 71248 && rune <= 71257) ||
         (rune >= 71296 && rune <= 71351) || (rune >= 71360 && rune <= 71369) ||
         (rune >= 71424 && rune <= 71450) || (rune >= 71453 && rune <= 71467) ||
         (rune >= 71472 && rune <= 71481) || (rune >= 71680 && rune <= 71738) ||
         (rune >= 71840 && rune <= 71913) || (rune >= 71935 && rune <= 71935) ||
         (rune >= 72192 && rune <= 72254) || (rune >= 72263 && rune <= 72263) ||
         (rune >= 72272 && rune <= 72323) || (rune >= 72326 && rune <= 72345) ||
         (rune >= 72349 && rune <= 72349) || (rune >= 72384 && rune <= 72440) ||
         (rune >= 72704 && rune <= 72712) || (rune >= 72714 && rune <= 72758) ||
         (rune >= 72760 && rune <= 72768) || (rune >= 72784 && rune <= 72793) ||
         (rune >= 72818 && rune <= 72847) || (rune >= 72850 && rune <= 72871) ||
         (rune >= 72873 && rune <= 72886) || (rune >= 72960 && rune <= 72966) ||
         (rune >= 72968 && rune <= 72969) || (rune >= 72971 && rune <= 73014) ||
         (rune >= 73018 && rune <= 73018) || (rune >= 73020 && rune <= 73021) ||
         (rune >= 73023 && rune <= 73031) || (rune >= 73040 && rune <= 73049) ||
         (rune >= 73056 && rune <= 73061) || (rune >= 73063 && rune <= 73064) ||
         (rune >= 73066 && rune <= 73102) || (rune >= 73104 && rune <= 73105) ||
         (rune >= 73107 && rune <= 73112) || (rune >= 73120 && rune <= 73129) ||
         (rune >= 73440 && rune <= 73462) || (rune >= 73728 && rune <= 74649) ||
         (rune >= 74752 && rune <= 74862) || (rune >= 74880 && rune <= 75075) ||
         (rune >= 77824 && rune <= 78894) || (rune >= 82944 && rune <= 83526) ||
         (rune >= 92160 && rune <= 92728) || (rune >= 92736 && rune <= 92766) ||
         (rune >= 92768 && rune <= 92777) || (rune >= 92880 && rune <= 92909) ||
         (rune >= 92912 && rune <= 92916) || (rune >= 92928 && rune <= 92982) ||
         (rune >= 92992 && rune <= 92995) || (rune >= 93008 && rune <= 93017) ||
         (rune >= 93027 && rune <= 93047) || (rune >= 93053 && rune <= 93071) ||
         (rune >= 93760 && rune <= 93823) || (rune >= 93952 && rune <= 94020) ||
         (rune >= 94032 && rune <= 94078) || (rune >= 94095 && rune <= 94111) ||
         (rune >= 94176 && rune <= 94177) || (rune >= 94208 && rune <= 94208) ||
         (rune >= 100337 && rune <= 100337) ||
         (rune >= 100352 && rune <= 101106) ||
         (rune >= 110592 && rune <= 110878) ||
         (rune >= 110960 && rune <= 111355) ||
         (rune >= 113664 && rune <= 113770) ||
         (rune >= 113776 && rune <= 113788) ||
         (rune >= 113792 && rune <= 113800) ||
         (rune >= 113808 && rune <= 113817) ||
         (rune >= 113821 && rune <= 113822) ||
         (rune >= 113824 && rune <= 113827) ||
         (rune >= 119141 && rune <= 119145) ||
         (rune >= 119149 && rune <= 119170) ||
         (rune >= 119173 && rune <= 119179) ||
         (rune >= 119210 && rune <= 119213) ||
         (rune >= 119362 && rune <= 119364) ||
         (rune >= 119808 && rune <= 119892) ||
         (rune >= 119894 && rune <= 119964) ||
         (rune >= 119966 && rune <= 119967) ||
         (rune >= 119970 && rune <= 119970) ||
         (rune >= 119973 && rune <= 119974) ||
         (rune >= 119977 && rune <= 119980) ||
         (rune >= 119982 && rune <= 119993) ||
         (rune >= 119995 && rune <= 119995) ||
         (rune >= 119997 && rune <= 120003) ||
         (rune >= 120005 && rune <= 120069) ||
         (rune >= 120071 && rune <= 120074) ||
         (rune >= 120077 && rune <= 120084) ||
         (rune >= 120086 && rune <= 120092) ||
         (rune >= 120094 && rune <= 120121) ||
         (rune >= 120123 && rune <= 120126) ||
         (rune >= 120128 && rune <= 120132) ||
         (rune >= 120134 && rune <= 120134) ||
         (rune >= 120138 && rune <= 120144) ||
         (rune >= 120146 && rune <= 120485) ||
         (rune >= 120488 && rune <= 120512) ||
         (rune >= 120514 && rune <= 120538) ||
         (rune >= 120540 && rune <= 120570) ||
         (rune >= 120572 && rune <= 120596) ||
         (rune >= 120598 && rune <= 120628) ||
         (rune >= 120630 && rune <= 120654) ||
         (rune >= 120656 && rune <= 120686) ||
         (rune >= 120688 && rune <= 120712) ||
         (rune >= 120714 && rune <= 120744) ||
         (rune >= 120746 && rune <= 120770) ||
         (rune >= 120772 && rune <= 120779) ||
         (rune >= 120782 && rune <= 120831) ||
         (rune >= 121344 && rune <= 121398) ||
         (rune >= 121403 && rune <= 121452) ||
         (rune >= 121461 && rune <= 121461) ||
         (rune >= 121476 && rune <= 121476) ||
         (rune >= 121499 && rune <= 121503) ||
         (rune >= 121505 && rune <= 121519) ||
         (rune >= 122880 && rune <= 122886) ||
         (rune >= 122888 && rune <= 122904) ||
         (rune >= 122907 && rune <= 122913) ||
         (rune >= 122915 && rune <= 122916) ||
         (rune >= 122918 && rune <= 122922) ||
         (rune >= 124928 && rune <= 125124) ||
         (rune >= 125136 && rune <= 125142) ||
         (rune >= 125184 && rune <= 125258) ||
         (rune >= 125264 && rune <= 125273) ||
         (rune >= 126464 && rune <= 126467) ||
         (rune >= 126469 && rune <= 126495) ||
         (rune >= 126497 && rune <= 126498) ||
         (rune >= 126500 && rune <= 126500) ||
         (rune >= 126503 && rune <= 126503) ||
         (rune >= 126505 && rune <= 126514) ||
         (rune >= 126516 && rune <= 126519) ||
         (rune >= 126521 && rune <= 126521) ||
         (rune >= 126523 && rune <= 126523) ||
         (rune >= 126530 && rune <= 126530) ||
         (rune >= 126535 && rune <= 126535) ||
         (rune >= 126537 && rune <= 126537) ||
         (rune >= 126539 && rune <= 126539) ||
         (rune >= 126541 && rune <= 126543) ||
         (rune >= 126545 && rune <= 126546) ||
         (rune >= 126548 && rune <= 126548) ||
         (rune >= 126551 && rune <= 126551) ||
         (rune >= 126553 && rune <= 126553) ||
         (rune >= 126555 && rune <= 126555) ||
         (rune >= 126557 && rune <= 126557) ||
         (rune >= 126559 && rune <= 126559) ||
         (rune >= 126561 && rune <= 126562) ||
         (rune >= 126564 && rune <= 126564) ||
         (rune >= 126567 && rune <= 126570) ||
         (rune >= 126572 && rune <= 126578) ||
         (rune >= 126580 && rune <= 126583) ||
         (rune >= 126585 && rune <= 126588) ||
         (rune >= 126590 && rune <= 126590) ||
         (rune >= 126592 && rune <= 126601) ||
         (rune >= 126603 && rune <= 126619) ||
         (rune >= 126625 && rune <= 126627) ||
         (rune >= 126629 && rune <= 126633) ||
         (rune >= 126635 && rune <= 126651) ||
         (rune >= 131072 && rune <= 131072) ||
         (rune >= 173782 && rune <= 173782) ||
         (rune >= 173824 && rune <= 173824) ||
         (rune >= 177972 && rune <= 177972) ||
         (rune >= 177984 && rune <= 177984) ||
         (rune >= 178205 && rune <= 178205) ||
         (rune >= 178208 && rune <= 178208) ||
         (rune >= 183969 && rune <= 183969) ||
         (rune >= 183984 && rune <= 183984) ||
         (rune >= 191456 && rune <= 191456) ||
         (rune >= 194560 && rune <= 195101) ||
         (rune >= 917505 && rune <= 917505) ||
         (rune >= 917536 && rune <= 917631) ||
         (rune >= 917760 && rune <= 917999);
}
