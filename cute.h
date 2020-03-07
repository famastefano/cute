#if __STDC_VERSION__ < 199901L
#  error "C99 is required to use this library"
#endif

#include <stdlib.h>
#include <string.h>

#ifndef FS_CUTE_PRINT
#  ifdef FS_CUTE_WCHAR
#    include <wchar.h>
#    define FS_CUTE_PRINT(...) wprintf(__VA_ARGS__)
#  else
#    include <stdio.h>
#    define FS_CUTE_PRINT(...) printf(__VA_ARGS__)
#  endif
#endif

static unsigned long total = 0, fail = 0;
static char const file_name[] = __FILE__;
static char const timestamp[] = __DATE__ " " __TIME__;

#define NOTIFY_FAIL 1 << 0
#define NOTIFY_PASS 1 << 1
#define NOTIFY_EXPECT 1 << 2
#define NOTIFY_INFO 1 << 3
#define NOTIFY_ALL ~0
#define NOTIFY_SET_LEVEL(Name, Level) _scenario_level = Level;

#define PRINT_LEVEL(Level, ...) \
if ( _scenario_level & Level ) {\
  FS_CUTE_PRINT("%s:%d\t", __FILE__, __LINE__); \
  FS_CUTE_PRINT(__VA_ARGS__); \
  FS_CUTE_PRINT("\n"); \
}

#define PRINT(...) FS_CUTE_PRINT(__VA_ARGS__)

#define PRINT_DATA() PRINT("\t\t[CUTe] Data\n\tFile: '%s' built on '%s'\n\n", file_name, timestamp)

#define PRINT_RESULTS() PRINT("\n\n\t\t[CUTe] Results\n\tTotal: %lu\n\tFailed: %lu\n\tPassed: %lu\n", total, fail, total-fail)

#define SET_SCENARIO_DATA(Name, Desc, Level) \
static char const _scenario_name[] = Name; \
static char const _scenario_desc[] = Desc; \
static unsigned _scenario_level = Level; \
PRINT_LEVEL(NOTIFY_INFO, "[%s] '%s'\n", _scenario_name, _scenario_desc)

#define SET_SIMPLE_SCENARIO(Name) SET_SCENARIO_DATA(Name, "", NOTIFY_FAIL)

#define TEST_CASE() for(unsigned _ = 0, _l = _scenario_level; !_; _ = 1, _scenario_level = _l)

#define SET_CASE_DATA(Name, Desc, Level) \
static char const _case_name[] = Name; \
static char const _case_desc[] = Desc; \
_scenario_level = Level; \
PRINT_LEVEL(NOTIFY_INFO, "[%s] '%s'\n", _case_name, _case_desc)

#define SET_SIMPLE_CASE(Name) SET_CASE_DATA(Name, "", _scenario_level)

#define FAIL_A(expr) PRINT_LEVEL(NOTIFY_FAIL, "[ASSERT] Assertion failed!\n\t'%s' is false.\n", #expr); ++total; ++fail
#define PASS_A(expr) PRINT_LEVEL(NOTIFY_PASS, "[ASSERT] Assertion succeed!\n\t'%s' is true.\n", #expr); ++total

#define FAIL_E(expr) PRINT_LEVEL(NOTIFY_FAIL, "[EXPECT] Assertion failed!\n\t'%s' is false.\n", #expr)
#define PASS_E(expr) PRINT_LEVEL(NOTIFY_PASS, "[EXPECT] Assertion succeed!\n\t'%s' is true.\n", #expr)

#define ASSERT(expr) if(expr) { PASS_A(expr); } else { FAIL_A(expr); }
#define EXPECT(expr) if(expr) { PASS_E(expr); } else { FAIL_E(expr); }

/* ASSERT */

#define ASSERT_EQ(a,b) ASSERT(a == b)
#define ASSERT_NEQ(a,b) ASSERT(a != b)
#define ASSERT_LT(a,b) ASSERT(a < b)
#define ASSERT_LTE(a,b) ASSERT(a <= b)
#define ASSERT_GT(a,b) ASSERT(a > b)
#define ASSERT_GTE(a,b) ASSERT(a >= b)
#define ASSERT_FALSE(expr) ASSERT(!(expr))
#define ASSERT_NULL(expr) ASSERT((expr) == NULL)

#define ASSERT_IN_RANGE(lower, x, upper) ASSERT(lower <= x && x <= upper)
#define ASSERT_NOT_IN_RANGE(lower, x, upper) ASSERT(lower > x || upper < x)

#define ASSERT_MEM_EQ(ptr0, ptr1, count) ASSERT(memcmp(ptr0, ptr1, count) == 0)
#define ASSERT_MEM_LT(ptr0, ptr1, count) ASSERT(memcmp(ptr0, ptr1, count) < 0)
#define ASSERT_MEM_GT(ptr0, ptr1, count) ASSERT(memcmp(ptr0, ptr1, count) > 0)
#define ASSERT_MEM_LTE(ptr0, ptr1, count) ASSERT(memcmp(ptr0, ptr1, count) <= 0)
#define ASSERT_MEM_GTE(ptr0, ptr1, count) ASSERT(memcmp(ptr0, ptr1, count) >= 0)

#define ASSERT_STR_EQ_N(str0, str1, count) ASSERT(strncmp(str0, str1, count) == 0)
#define ASSERT_STR_LT_N(str0, str1, count) ASSERT(strncmp(str0, str1, count) < 0)
#define ASSERT_STR_GT_N(str0, str1, count) ASSERT(strncmp(str0, str1, count) > 0)
#define ASSERT_STR_LTE_N(str0, str1, count) ASSERT(strncmp(str0, str1, count) <= 0)
#define ASSERT_STR_GTE_N(str0, str1, count) ASSERT(strncmp(str0, str1, count) >= 0)

#define ASSERT_STR_EQ(str0, str1) ASSERT(strcmp(str0, str1) == 0)
#define ASSERT_STR_LT(str0, str1) ASSERT(strcmp(str0, str1) < 0)
#define ASSERT_STR_GT(str0, str1) ASSERT(strcmp(str0, str1) > 0)
#define ASSERT_STR_LTE(str0, str1) ASSERT(strcmp(str0, str1) <= 0)
#define ASSERT_STR_GTE(str0, str1) ASSERT(strcmp(str0, str1) >= 0)

/* EXPECT */

#define EXPECT_EQ(a,b) EXPECT(a == b)
#define EXPECT_NEQ(a,b) EXPECT(a != b)
#define EXPECT_LT(a,b) EXPECT(a < b)
#define EXPECT_LTE(a,b) EXPECT(a <= b)
#define EXPECT_GT(a,b) EXPECT(a > b)
#define EXPECT_GTE(a,b) EXPECT(a >= b)
#define EXPECT_FALSE(expr) EXPECT(!(expr))
#define EXPECT_NULL(expr) EXPECT((expr) == NULL)

#define EXPECT_IN_RANGE(lower, x, upper) EXPECT(lower <= x && x <= upper)
#define EXPECT_NOT_IN_RANGE(lower, x, upper) EXPECT(lower > x || upper < x)

#define EXPECT_MEM_EQ(ptr0, ptr1, count) EXPECT(memcmp(ptr0, ptr1, count) == 0)
#define EXPECT_MEM_LT(ptr0, ptr1, count) EXPECT(memcmp(ptr0, ptr1, count) < 0)
#define EXPECT_MEM_GT(ptr0, ptr1, count) EXPECT(memcmp(ptr0, ptr1, count) > 0)
#define EXPECT_MEM_LTE(ptr0, ptr1, count) EXPECT(memcmp(ptr0, ptr1, count) <= 0)
#define EXPECT_MEM_GTE(ptr0, ptr1, count) EXPECT(memcmp(ptr0, ptr1, count) >= 0)

#define EXPECT_STR_EQ_N(str0, str1, count) EXPECT(strncmp(str0, str1, count) == 0)
#define EXPECT_STR_LT_N(str0, str1, count) EXPECT(strncmp(str0, str1, count) < 0)
#define EXPECT_STR_GT_N(str0, str1, count) EXPECT(strncmp(str0, str1, count) > 0)
#define EXPECT_STR_LTE_N(str0, str1, count) EXPECT(strncmp(str0, str1, count) <= 0)
#define EXPECT_STR_GTE_N(str0, str1, count) EXPECT(strncmp(str0, str1, count) >= 0)

#define EXPECT_STR_EQ(str0, str1) EXPECT(strcmp(str0, str1) == 0)
#define EXPECT_STR_LT(str0, str1) EXPECT(strcmp(str0, str1) < 0)
#define EXPECT_STR_GT(str0, str1) EXPECT(strcmp(str0, str1) > 0)
#define EXPECT_STR_LTE(str0, str1) EXPECT(strcmp(str0, str1) <= 0)
#define EXPECT_STR_GTE(str0, str1) EXPECT(strcmp(str0, str1) >= 0)

#define CUTE_FAIL_COUNT() (fail)