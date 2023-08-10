//todo turn into class
#include "CliFunctions.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//
// #include "hardware/adc.h"
#include "hardware/rtc.h"
#include "pico/stdlib.h"
//
#include "ff.h" /* Obtains integer types */
//
#include "diskio.h" /* Declarations of disk functions */
//
#include "f_util.h"
#include "hw_config.h"
#include "my_debug.h"
#include "rtc.h"
#include "sd_card.h"

#include "Command.h"



bool logger_enabled;
const uint32_t period = 1000;
absolute_time_t next_log_time;

static sd_card_t *sd_get_by_name(const char *const name) {
    for (size_t i = 0; i < sd_get_num(); ++i)
        if (0 == strcmp(sd_get_by_num(i)->pcName, name)) return sd_get_by_num(i);
    DBG_PRINTF("%s: unknown name %s\n", __func__, name);
    return NULL;
}
static FATFS *sd_get_fs_by_name(const char *name) {
    for (size_t i = 0; i < sd_get_num(); ++i)
        if (0 == strcmp(sd_get_by_num(i)->pcName, name)) return &sd_get_by_num(i)->fatfs;
    DBG_PRINTF("%s: unknown name %s\n", __func__, name);
    return NULL;
}

void run_setrtc(pico::Drivers* drivers) {
    const char *dateStr = strtok(NULL, " ");
    if (!dateStr) {
        printf("Missing argument\n");
        return;
    }
    int date = atoi(dateStr);

    const char *monthStr = strtok(NULL, " ");
    if (!monthStr) {
        printf("Missing argument\n");
        return;
    }
    int month = atoi(monthStr);

    const char *yearStr = strtok(NULL, " ");
    if (!yearStr) {
        printf("Missing argument\n");
        return;
    }
    int year = atoi(yearStr) + 2000;

    const char *hourStr = strtok(NULL, " ");
    if (!hourStr) {
        printf("Missing argument\n");
        return;
    }
    int hour = atoi(hourStr);

    const char *minStr = strtok(NULL, " ");
    if (!minStr) {
        printf("Missing argument\n");
        return;
    };
    int min = atoi(minStr);

    const char *secStr = strtok(NULL, " ");
    if (!secStr) {
        printf("Missing argument\n");
        return;
    }
    int sec = atoi(secStr);

    datetime_t t = {.year = static_cast<int16_t>(year),
                    .month = static_cast<int8_t>(month),
                    .day = static_cast<int8_t>(date),
                    .dotw = 0,  // 0 is Sunday, so 5 is Friday
                    .hour = static_cast<int8_t>(hour),
                    .min = static_cast<int8_t>(min),
                    .sec = static_cast<int8_t>(sec)};
    rtc_set_datetime(&t);
}
// static void run_lliot() {
//     size_t pnum = 0;
//     char *arg1 = strtok(NULL, " ");
//     if (arg1) {
//         pnum = strtoul(arg1, NULL, 0);
//     }
//     lliot(pnum);
// }
void run_date(pico::Drivers* drivers) {
    char buf[128] = {0};
    time_t epoch_secs = time(NULL);
    struct tm *ptm = localtime(&epoch_secs);
    size_t n = strftime(buf, sizeof(buf), "%c", ptm);
    myASSERT(n);
    printf("%s\n", buf);
    strftime(buf, sizeof(buf), "%j",
             ptm);  // The day of the year as a decimal number (range
                    // 001 to 366).
    printf("Day of year: %s\n", buf);
}
void run_format(pico::Drivers* drivers) {
    const char *arg1 = strtok(NULL, " ");
    if (!arg1) arg1 = sd_get_by_num(0)->pcName;
    FATFS *p_fs = sd_get_fs_by_name(arg1);
    if (!p_fs) {
        printf("Unknown logical drive number: \"%s\"\n", arg1);
        return;
    }
    /* Format the drive with default parameters */
    FRESULT fr = f_mkfs(arg1, 0, 0, FF_MAX_SS * 2);
    if (FR_OK != fr) printf("f_mkfs error: %s (%d)\n", FRESULT_str(fr), fr);
}
void run_mount(pico::Drivers* drivers) {
    const char *arg1 = strtok(NULL, " ");
    if (!arg1) arg1 = sd_get_by_num(0)->pcName;
    mount(arg1);
}
bool mount(const char *drive_number){
    FATFS *p_fs = sd_get_fs_by_name(drive_number);
    if (!p_fs) {
        printf("Unknown logical drive number: \"%s\"\n", drive_number);
        return false;
    }
    FRESULT fr = f_mount(p_fs, drive_number, 1);
    if (FR_OK != fr) {
        printf("f_mount error: %s (%d)\n", FRESULT_str(fr), fr);
        return false;
    }
    sd_card_t *pSD = sd_get_by_name(drive_number);
    myASSERT(pSD);
    pSD->mounted = true;
    return true;
}

void run_unmount(pico::Drivers* drivers) {
    const char *arg1 = strtok(NULL, " ");
    if (!arg1) arg1 = sd_get_by_num(0)->pcName;
    unmount(arg1);
}
bool unmount(const char *drive_number){
    FATFS *p_fs = sd_get_fs_by_name(drive_number);
    if (!p_fs) {
        printf("Unknown logical drive number: \"%s\"\n", drive_number);
        return false;
    }
    FRESULT fr = f_unmount(drive_number);
    if (FR_OK != fr) {
        printf("f_unmount error: %s (%d)\n", FRESULT_str(fr), fr);
        return false;
    }
    sd_card_t *pSD = sd_get_by_name(drive_number);
    myASSERT(pSD);
    pSD->mounted = false;
    pSD->m_Status |= STA_NOINIT; // in case medium is removed
    printf("unmounted successfully\n");
    return true;
}
void run_chdrive(pico::Drivers* drivers) {
    const char *arg1 = strtok(NULL, " ");
    if (!arg1) arg1 = sd_get_by_num(0)->pcName;
    FRESULT fr = f_chdrive(arg1);
    if (FR_OK != fr) printf("f_mount error: %s (%d)\n", FRESULT_str(fr), fr);
}
void run_getfree(pico::Drivers* drivers) {
    const char *arg1 = strtok(NULL, " ");
    if (!arg1) arg1 = sd_get_by_num(0)->pcName;
    DWORD fre_clust, fre_sect, tot_sect;
    /* Get volume information and free clusters of drive */
    FATFS *p_fs = sd_get_fs_by_name(arg1);
    if (!p_fs) {
        printf("Unknown logical drive number: \"%s\"\n", arg1);
        return;
    }
    FRESULT fr = f_getfree(arg1, &fre_clust, &p_fs);
    if (FR_OK != fr) {
        printf("f_getfree error: %s (%d)\n", FRESULT_str(fr), fr);
        return;
    }
    /* Get total sectors and free sectors */
    tot_sect = (p_fs->n_fatent - 2) * p_fs->csize;
    fre_sect = fre_clust * p_fs->csize;
    /* Print the free space (assuming 512 bytes/sector) */
    printf("%10lu KiB total drive space.\n%10lu KiB available.\n", tot_sect / 2,
           fre_sect / 2);
}
void run_cd(pico::Drivers* drivers) {
    char *arg1 = strtok(NULL, " ");
    if (!arg1) {
        printf("Missing argument\n");
        return;
    }

}
bool cd(char *dir_name){
    FRESULT fr = f_chdir(dir_name);
    if (FR_OK != fr){
        printf("f_mkfs error: %s (%d)\n", FRESULT_str(fr), fr);
        return false;
    }
    return true;
}
void run_mkdir(pico::Drivers* drivers) {
    char *arg1 = strtok(NULL, " ");
    if (!arg1) {
        printf("Missing argument\n");
        return;
    }
}
bool mkdir(char *dir_name){
    FRESULT fr = f_mkdir(dir_name);
    if (FR_OK != fr){
        printf("f_mkfs error: %s (%d)\n", FRESULT_str(fr), fr);
        return false;
    }
    return true;
}
void ls(const char *dir) {
    char cwdbuf[FF_LFN_BUF] = {0};
    FRESULT fr; /* Return value */
    char const *p_dir;
    if (dir[0]) {
        p_dir = dir;
    } else {
        fr = f_getcwd(cwdbuf, sizeof cwdbuf);
        if (FR_OK != fr) {
            printf("f_getcwd error: %s (%d)\n", FRESULT_str(fr), fr);
            return;
        }
        p_dir = cwdbuf;
    }
    printf("Directory Listing: %s\n", p_dir);
    DIR dj;      /* Directory object */
    FILINFO fno; /* File information */
    memset(&dj, 0, sizeof dj);
    memset(&fno, 0, sizeof fno);
    fr = f_findfirst(&dj, &fno, p_dir, "*");
    if (FR_OK != fr) {
        printf("f_findfirst error: %s (%d)\n", FRESULT_str(fr), fr);
        return;
    }
    while (fr == FR_OK && fno.fname[0]) { /* Repeat while an item is found */
        /* Create a string that includes the file name, the file size and the
         attributes string. */
        const char *pcWritableFile = "writable file",
                   *pcReadOnlyFile = "read only file",
                   *pcDirectory = "directory";
        const char *pcAttrib;
        /* Point pcAttrib to a string that describes the file. */
        if (fno.fattrib & AM_DIR) {
            pcAttrib = pcDirectory;
        } else if (fno.fattrib & AM_RDO) {
            pcAttrib = pcReadOnlyFile;
        } else {
            pcAttrib = pcWritableFile;
        }
        /* Create a string that includes the file name, the file size and the
         attributes string. */
        printf("%s [%s] [size=%llu]\n", fno.fname, pcAttrib, fno.fsize);

        fr = f_findnext(&dj, &fno); /* Search for next item */
    }
    f_closedir(&dj);
}
void run_ls(pico::Drivers* drivers) {
    const char *arg1 = strtok(NULL, " ");
    if (!arg1) arg1 = "";
    ls(arg1);
}
void run_cat(pico::Drivers* drivers) {
    char *arg1 = strtok(NULL, " ");
    if (!arg1) {
        printf("Missing argument\n");
        return;
    }
    FIL fil;
    FRESULT fr = f_open(&fil, arg1, FA_READ);
    if (FR_OK != fr) {
        printf("f_open error: %s (%d)\n", FRESULT_str(fr), fr);
        return;
    }
    char buf[256];
    while (f_gets(buf, sizeof buf, &fil)) {
        printf("%s", buf);
    }
    fr = f_close(&fil);
    if (FR_OK != fr) printf("f_open error: %s (%d)\n", FRESULT_str(fr), fr);
}
// static void run_big_file_test() {
//     const char *pcPathName = strtok(NULL, " ");
//     if (!pcPathName) {
//         printf("Missing argument\n");
//         return;
//     }
//     const char *pcSize = strtok(NULL, " ");
//     if (!pcSize) {
//         printf("Missing argument\n");
//         return;
//     }
//     size_t size = strtoul(pcSize, 0, 0);
//     const char *pcSeed = strtok(NULL, " ");
//     if (!pcSeed) {
//         printf("Missing argument\n");
//         return;
//     }
//     uint32_t seed = atoi(pcSeed);
//     big_file_test(pcPathName, size, seed);
// }
void del_node(const char *path) {
    FILINFO fno;
    char buff[256];
    /* Directory to be deleted */
    strlcpy(buff, path, sizeof(buff));
    /* Delete the directory */
    FRESULT fr = delete_node(buff, sizeof buff / sizeof buff[0], &fno);
    /* Check the result */
    if (fr) {
        printf("Failed to delete the directory %s. ", path);
        printf("%s error: %s (%d)\n", __func__, FRESULT_str(fr), fr);
    }
}
void run_del_node(pico::Drivers* drivers) {
    char *arg1 = strtok(NULL, " ");
    if (!arg1) {
        printf("Missing argument\n");
        return;
    }
    del_node(arg1);
}
// static void run_cdef() {
//     f_mkdir("/cdef");  // fake mountpoint
//     vCreateAndVerifyExampleFiles("/cdef");
// }
// static void run_swcwdt() { vStdioWithCWDTest("/cdef"); }
// static void run_loop_swcwdt() {
//     int cRxedChar = 0;
//     do {
//         del_node("/cdef");
//         run_cdef();
//         run_swcwdt();
//         cRxedChar = getchar_timeout_us(0);
//     } while (PICO_ERROR_TIMEOUT == cRxedChar);
// }

void run_start_logger(pico::Drivers* drivers) {
    logger_enabled = true;
    next_log_time = delayed_by_ms(get_absolute_time(), period);
}
void run_stop_logger(pico::Drivers* drivers) { logger_enabled = false; }
void run_help(pico::Drivers* drivers);//todo
// static void run_help() {
//     for (size_t i = 0; i < count_of(cmds); ++i) {
//         printf("%s\n\n", cmds[i].help);
//     }
// }
