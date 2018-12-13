#include <stdio.h>

#define FS_CUTE_PRINT(...) fprintf(fd, __VA_ARGS__)

#include "../cute.h"

FILE* fd;

static void f( void )
{
  SET_SCENARIO_DATA( "1st Scenario", "A simple test scenario", NOTIFY_ALL );

  TEST_CASE()
  {
    SET_SIMPLE_CASE( "1st Case" );
    ASSERT( 1 );
    ASSERT_FALSE( 0 );
    ASSERT_FALSE( 1 );
    ASSERT( 12415231 == 1215215123 );
  }

  TEST_CASE()
  {
    SET_CASE_DATA( "2nd Case", "Desc", NOTIFY_ALL );
    char const a[] = "abc", b[] = "abc";

    ASSERT_STR_EQ( a, b );
    ASSERT_STR_LT( a, b );
    ASSERT_STR_GT( a, b );
    ASSERT_STR_LTE( a, b );
    ASSERT_STR_GTE( a, b );

    ASSERT_STR_EQ_N( a, b, 3 );
    ASSERT_STR_LT_N( a, b, 3 );
    ASSERT_STR_GT_N( a, b, 3 );
    ASSERT_STR_LTE_N( a, b, 3 );
    ASSERT_STR_GTE_N( a, b, 3 );
  }
}

int main( void )
{
  fd = fopen( "file.log", "w+" );
  PRINT_DATA();
  f();
  PRINT_RESULTS();
  fclose( fd );
  return 0;
}
