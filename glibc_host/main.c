#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <timezones.h>

static int failed = 0;

#define TEST_ASSERT_EQUAL_INT_MESSAGE(...) assert_equal(__VA_ARGS__)
void assert_equal(int lhs, int rhs, const char* msg)
{
    if (lhs != rhs)
    {
        printf("Assertion failed! Expected %d to equal %d. %s\n", lhs, rhs, msg);
        ++failed;
    }
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

int main(void)
{
    printf("##### Running tests #####\n");
    test_Mktime_should_LocalTimestamp();

    printf("\n\n%d tests failed.\n", failed);
    printf("##### Finished #####\n");

    return failed;
}