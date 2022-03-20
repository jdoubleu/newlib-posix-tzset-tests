#include <stdio.h>
#include <unity.h>

TEST_CASE("tzset", "[newlib]")
{
    TEST_ASSERT( true );
}

void app_main(void)
{
    UNITY_BEGIN();
    unity_run_all_tests();
    UNITY_END();

    unity_run_menu();
}
