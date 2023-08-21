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

/**
 * @brief sets real time clock
 * 
 * @note cli needs multiple arguments: setrtc <DD> <MM> <YY> <hh> <mm> <ss>:
 * 
 * @param drivers 
 */
void run_setrtc(pico::Drivers* drivers);

// static void run_lliot();

/**
 * @brief prints date and time
 * 
 * @param drivers 
 */
void run_date(pico::Drivers* drivers);

/**
 * @brief formats drive
 * 
 * @note cli needs drive number argument: format [<drive#:>]
 * 
 * @param drivers 
 */
void run_format(pico::Drivers* drivers);

/**
 * @brief cli function to mount the SD card
 * 
 * @note defaults to drive number 0 if no argument is given
 * 
 * @param drivers 
 */
void run_mount(pico::Drivers* drivers);

/**
 * @brief mounts SD card
 * 
 * @note please use this instead of \ref f_mount() because it does several checks
 * and updates pSD's internal state
 * 
 * @param drivers 
 */
bool mountCard(const char *drive_number);

/**
 * @brief cli function to unmount the SD card
 * 
 * @note defaults to drive number 0 if no argument is given
 * 
 * @param drivers 
 */
void run_unmount(pico::Drivers* drivers);

/**
 * @brief unmounts the SD card
 * 
 * @param drive_number 
 * @return if the unmount was successful
 */
bool unmountCard(const char *drive_number);


/**
 * @brief Changes the current directory of the logical drive.
 * 
 * @note cli takes drive number: chdrive <drive#:>.
 * Use \ref f_chdrive(drive#) if you are using this in code
 * 
 * @param drivers 
 */
void run_chdrive(pico::Drivers* drivers);

/**
 * @brief Print the free space on drive
 * 
 * @note cli takes drive number: getfree [<drive#:>]
 * 
 * @param drivers 
 */
void run_getfree(pico::Drivers* drivers);

/**
 * @brief cli to run cd()
 * 
 * @note cli takes path as argument: cd <path>
 * 
 * @param drivers 
 */
void run_cd(pico::Drivers* drivers);

/**
 * @brief Changes the current directory of the SD card (like unix cd)
 * 
 * @param dir_name 
 * @return true if successful 
 */
bool cd(char *dir_name);


/**
 * @brief cli runs mkdir()
 * 
 * @note cli takes path as argment: mkdir <path>
 * 
 * @param drivers 
 */
void run_mkdir(pico::Drivers* drivers);

/**
 * @brief makes new directory (like unix mkdir)
 * 
 * @param dir_name 
 * @return true if success 
 */
bool mkdir(char *dir_name);

/**
 * @brief lists directory (like unix ls)
 * 
 * @param dir 
 */
void ls(const char *dir);

/**
 * @brief cli runs ls()
 * 
 * @param drivers 
 */
void run_ls(pico::Drivers* drivers);

/**
 * @brief prints file contents (like unix cat)
 * 
 * @note cli takes filename: cat <filename>
 * 
 * @param drivers 
 */
void run_cat(pico::Drivers* drivers);
// static void run_big_file_test() ;

/**
 * @brief deletes directory (like unix rm -rf <dir>)
 * 
 * @param path 
 */
void del_node(const char *path);

/**
 * @brief cli runs del_node()
 * 
 * @brief cli takes path argument: del_node <path>
 * 
 * @param drivers 
 */
void run_del_node(pico::Drivers* drivers);
// static void run_cdef() ;
// static void run_swcwdt() ;
// static void run_loop_swcwdt() ;
//TODO:
void run_start_logger(pico::Drivers* drivers);
//TODO:
void run_stop_logger(pico::Drivers* drivers);

/**
 * @brief prints help
 * 
 * @param drivers 
 */
void run_help(pico::Drivers* drivers);

#endif //  PICO_CLIFUNCTIONS_H_