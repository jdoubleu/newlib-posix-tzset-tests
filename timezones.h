#ifndef TIMEZONES_H
#define TIMEZONES_H

#include <time.h>
#include <limits.h>

// winter time is March, 21st 2022 at 8:15pm and 20 seconds
static struct tm winter_tm = {
    .tm_sec     = 20,
    .tm_min     = 15,
    .tm_hour    = 20,
    .tm_mday    = 21,
    .tm_mon     = 3 - 1,
    .tm_year    = 2022 - 1900,
    .tm_isdst   = 0
};

// summer time is July, 15th 2022 at 10:50am and 40 seconds
static struct tm summer_tm = {
    .tm_sec     = 40,
    .tm_min     = 50,
    .tm_hour    = 10,
    .tm_mday    = 15,
    .tm_mon     = 7 - 1,
    .tm_year    = 2022 - 1900,
    .tm_isdst   = 1
};

// UTC unix time for the winter time
static const time_t winter_time = 1647893720;
static const time_t summer_time = 1657882240;

struct tz_test {
    const char* tzstr;
    int offset_seconds;
    int dst_offset_seconds;
};

#define IN_SECONDS(h, m, s) ((h) * 3600 + (m) * 60 + (s))

#define NO_TIME INT_MIN

struct tz_test test_timezones[] = {
    /*
     * creating test vectors based on the POSIX spec (https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap08.html#tag_08_03)
     */
    // normal std names
    {"MAR1",         IN_SECONDS(1, 0, 0),    NO_TIME},
    {"MAR-1",       -IN_SECONDS(1, 0, 0),    NO_TIME},
    {"MAR+2",        IN_SECONDS(2, 0, 0),    NO_TIME},
    {"MAR7",         IN_SECONDS(7, 0, 0),    NO_TIME},
    {"MAR-7",       -IN_SECONDS(7, 0, 0),    NO_TIME},
    {"MARS5",        IN_SECONDS(5, 0, 0),    NO_TIME},
    {"MARSM5",       IN_SECONDS(5, 0, 0),    NO_TIME},
    {"MARSMOON5",    IN_SECONDS(5, 0, 0),    NO_TIME},   // assuming TZNAME_MAX >= 8
    {"MARS5:23:42",  IN_SECONDS(5, 23, 42),  NO_TIME},
    {"SUN-7:14:24", -IN_SECONDS(7, 14, 24),  NO_TIME},
    // with DST
    {"MAR5SMAR",                IN_SECONDS(5, 0, 0), IN_SECONDS(4, 0, 0)},  // only DST name
    {"MAR5SMAR2",               IN_SECONDS(5, 0, 0), IN_SECONDS(2, 0, 0)},  // DST name with offset
    {"MAR3SMAR-3",              IN_SECONDS(3, 0, 0), -IN_SECONDS(3, 0, 0)},
    {"MARSWINTER4MARSUMMER",    IN_SECONDS(4, 0, 0), IN_SECONDS(3, 0, 0)},
    {"MARSWINTER4MARSUMMER3",   IN_SECONDS(4, 0, 0), IN_SECONDS(3, 0, 0)},
    // with DST IN_SECONDSs
    {"WMARS3SMARS,J80",                                 IN_SECONDS(3, 0, 0), IN_SECONDS(2, 0, 0)},
    {"WMARS3SMARS,J80,J134",                            IN_SECONDS(3, 0, 0), IN_SECONDS(2, 0, 0)},
    {"WMARS3SMARS,79",                                  IN_SECONDS(3, 0, 0), IN_SECONDS(2, 0, 0)},
    {"WMARS3SMARS,76,134",                              IN_SECONDS(3, 0, 0), IN_SECONDS(2, 0, 0)},
    {"WMARS3SMARS,76/02,134/03",                        IN_SECONDS(3, 0, 0), IN_SECONDS(2, 0, 0)},
    {"WMARS3SMARS,76/02:15:45,134/03:40:20",            IN_SECONDS(3, 0, 0), IN_SECONDS(2, 0, 0)},
    {"WMARS3SMARS,M3.4.1/02:15:45,M8.3.1/03:40:20",     IN_SECONDS(3, 0, 0), IN_SECONDS(2, 0, 0)},

    // special std names
    {"<UNK>-1",                                 -IN_SECONDS(1, 0, 0),     NO_TIME},
    {"<UNKNOWN>-2",                             -IN_SECONDS(2, 0, 0),     NO_TIME},                  // require TZNAME_MAX >= 9
    {"<003>3",                                   IN_SECONDS(3, 0, 0),     NO_TIME},
    {"<+04>4",                                   IN_SECONDS(4, 0, 0),     NO_TIME},
    {"<-05>-5",                                 -IN_SECONDS(5, 0, 0),     NO_TIME},
    {"<A-5>6",                                   IN_SECONDS(6, 0, 0),     NO_TIME},
    {"<+A5>-7",                                 -IN_SECONDS(7, 0, 0),     NO_TIME},
    {"<0123456>8",                               IN_SECONDS(8, 0, 0),     NO_TIME},
    {"<0A1B2C3>9",                               IN_SECONDS(9, 0, 0),     NO_TIME},
    {"<RD-04>-4<RD+005>5",                      -IN_SECONDS(4, 0, 0),     IN_SECONDS(5, 0, 0)},
    {"<WINT+03>3<SUM+02>",                       IN_SECONDS(3, 0, 0),     IN_SECONDS(2, 0, 0)},
    {"<WINT+03>3<SUM+02>2",                      IN_SECONDS(3, 0, 0),     IN_SECONDS(2, 0, 0)},
    {"<WINT+03>3:15<SUM+02>2:30:15",             IN_SECONDS(3, 15, 0),    IN_SECONDS(2, 30, 15)},
    {"<H3M15>3:15<H2M30S15>2:30:15",             IN_SECONDS(3, 15, 0),    IN_SECONDS(2, 30, 15)},   // requires TZNAME_MAX >= 10
    {"<+H6M20S12>6:20:12<-H4M40S14>-4:40:14",     IN_SECONDS(6, 20, 12), -IN_SECONDS(4, 40, 14)},   // requires TZNAME_MAX >= 11

    /* 
     * real-world test vectors.
     * IN_SECONDSzones extracted from the tzdb (https://github.com/eggert/tz#2019e).
     * The IN_SECONDSzone strings can also be obtained from https://raw.githubusercontent.com/nayarsystems/posix_tz_db/master/zones.csv.
     */
    { /* Etc/GMT-14 */              "<+14>-14",                        -IN_SECONDS(14, 0, 0),     NO_TIME},
    { /* Etc/GMT+12 */              "<-12>12",                          IN_SECONDS(12, 0, 0),     NO_TIME},
    { /* Africa/Casablanca */       "<+01>-1",                         -IN_SECONDS(1, 0, 0),      NO_TIME},
    { /* America/Araguaina */       "<-03>3",                           IN_SECONDS(3, 0, 0),      NO_TIME},
    { /* America/Asuncion */        "<-04>4<-03>,M10.1.0/0,M3.4.0/0",   IN_SECONDS(4, 0, 0),      IN_SECONDS(3, 0, 0)},
    { /* America/Los_Angeles */     "PST8PDT,M3.2.0,M11.1.0",           IN_SECONDS(8, 0, 0),      IN_SECONDS(7, 0, 0)},
    { /* America/New_York */        "EST5EDT,M3.2.0,M11.1.0",           IN_SECONDS(5, 0, 0),      IN_SECONDS(4, 0, 0)},
    { /* America/Scoresbysund */    "<-01>1<+00>,M3.5.0/0,M10.5.0/1",   IN_SECONDS(1, 0, 0),      IN_SECONDS(0, 0, 0)},
    { /* Asia/Colombo */            "<+0530>-5:30",                    -IN_SECONDS(5, 30, 0),     NO_TIME},
    { /* Europe/Berlin */           "CET-1CEST,M3.5.0,M10.5.0/3",      -IN_SECONDS(1, 0, 0),     -IN_SECONDS(2, 0, 0)},

    // END of list
    {NULL, NO_TIME, NO_TIME}
};

// helper macros
#define FOR_TIMEZONES(iter_name) for (struct tz_test* iter_name = test_timezones; iter_name->tzstr != NULL; ++iter_name)

#endif // TIMEZONES_H