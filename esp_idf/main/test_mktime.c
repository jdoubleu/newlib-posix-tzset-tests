#include <stdio.h>
#include <unity.h>

#include <timezones.h>

void test_Mktime_should_UTCTime(void)
{
    setenv("TZ", "UTC", 1);
    tzset();

    TEST_ASSERT_EQUAL_INT(winter_time, mktime(&winter_tm));
}

void test_Mktime_should_LocalTimestamp(void)
{
    char buffer[128];

    FOR_TIMEZONES(ptr)
    {
        setenv("TZ", ptr->tzstr, 1);
        tzset();

        snprintf(buffer, 128, "winter time, timezone = \"%s\"", ptr->tzstr);

        struct tm winter_tm_copy = winter_tm; // copy
        TEST_ASSERT_EQUAL_INT_MESSAGE(winter_time + ptr->offset_seconds, mktime(&winter_tm_copy), buffer);

        if (ptr->dst_offset_seconds != NO_TIME)
        {
            snprintf(buffer, 128, "summer time, timezone = \"%s\"", ptr->tzstr);

            struct tm summer_tm_copy = summer_tm; // copy
            TEST_ASSERT_EQUAL_INT_MESSAGE(summer_time + ptr->dst_offset_seconds, mktime(&summer_tm_copy), buffer);
        }
    }
}