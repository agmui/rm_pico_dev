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


namespace pico
{
    class Drivers;
}



bool process_logger();
// bool logger_enabled;
// const uint32_t period = 1000;
// absolute_time_t next_log_time;

static sd_card_t *sd_get_by_name(const char *const name);
static FATFS *sd_get_fs_by_name(const char *name);

void run_setrtc(pico::Drivers* drivers);
// static void run_lliot();
void run_date(pico::Drivers* drivers);
void run_format(pico::Drivers* drivers);
void run_mount(pico::Drivers* drivers);
bool mount(const char *drive_number);
void run_unmount(pico::Drivers* drivers);
bool unmount(const char *drive_number);
void run_chdrive(pico::Drivers* drivers);
void run_getfree(pico::Drivers* drivers);
void run_cd(pico::Drivers* drivers);
bool cd(char *dir_name);
void run_mkdir(pico::Drivers* drivers);
bool mkdir(char *dir_name);
void ls(const char *dir);
void run_ls(pico::Drivers* drivers);
void run_cat(pico::Drivers* drivers);
// static void run_big_file_test() ;
void del_node(const char *path);
void run_del_node(pico::Drivers* drivers);
// static void run_cdef() ;
// static void run_swcwdt() ;
// static void run_loop_swcwdt() ;
void run_start_logger(pico::Drivers* drivers);
void run_stop_logger(pico::Drivers* drivers);
void run_help(pico::Drivers* drivers);

#endif //  PICO_CLIFUNCTIONS_H_