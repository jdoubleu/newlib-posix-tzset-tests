#include <stdio.h>
#include <unity.h>

#define TIMEZONES_DEFINE_DATA
#include <timezones.h>

// test_tzset.c
void test_Mktime_should_UTCTime();
void test_Mktime_should_LocalTimestamp(); 

void app_main(void)
{
    printf("\n\n#####\nBEGIN testing\n#####\n\n");

    UNITY_BEGIN();
    RUN_TEST(test_Mktime_should_UTCTime);
    RUN_TEST(test_Mktime_should_LocalTimestamp);
    UNITY_END();

    printf("\n\n######\nEND testing\n######\n\n");
}
