#ifndef PICO_CLIFUNCTIONS_H_
#define PICO_CLIFUNCTIONS_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hardware/rtc.h"
#include "pico/stdlib.h"
//
#include "ff.h" /* Obtains integer types */
//
#include "diskio.h" /* Declarations of disk functions */
//
// #include "f_util.h"
// #include "hw_config.h"
// #include "my_debug.h"
// #include "rtc.h"
#include "sd_card.h"


//
// extern "C"
// {
//     // int lliot(size_t pnum);
//     void ls(const char *dir);
//     void simple();
//     // void big_file_test(const char *const pathname, size_t size,
//     //                         uint32_t seed);
//     // void vCreateAndVerifyExampleFiles(const char *pcMountPath);
//     // void vStdioWithCWDTest(const char *pcMountPath);
//     bool process_logger();
// }

bool process_logger();
static bool logger_enabled;
static const uint32_t period = 1000;
static absolute_time_t next_log_time;

static sd_card_t *sd_get_by_name(const char *const name);
static FATFS *sd_get_fs_by_name(const char *name);

static void run_setrtc();
// static void run_lliot();
static void run_date();
static void run_format();
static void run_mount();
static bool mount(const char *driver_number);
static void run_unmount();
static bool unmount(const char *drive_number);
static void run_chdrive();
static void run_getfree();
static void run_cd();
static bool cd(char *dir_name);
static void run_mkdir();
static bool mkdir(char *dir_name);
static void ls(const char *dir);
static void run_ls();
static void run_cat();
// static void run_big_file_test() ;
static void del_node(const char *path);
static void run_del_node();
// static void run_cdef() ;
// static void run_swcwdt() ;
// static void run_loop_swcwdt() ;
static void run_start_logger();
static void run_stop_logger();
static void run_help();


#endif //  PICO_CLIFUNCTIONS_H_