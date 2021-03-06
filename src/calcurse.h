/*
 * Calcurse - text-based organizer
 *
 * Copyright (c) 2004-2017 calcurse Development Team <misc@calcurse.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the
 *        following disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the
 *        following disclaimer in the documentation and/or other
 *        materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Send your feedback or comments to : misc@calcurse.org
 * Calcurse home page : http://calcurse.org
 *
 */

#ifndef CALCURSE_H
#define CALCURSE_H

#include "config.h"

#ifdef HAVE_NCURSES_H
#include <ncurses.h>
#elif defined HAVE_NCURSES_NCURSES_H
#include <ncurses/ncurses.h>
#elif defined HAVE_NCURSESW_NCURSES_H
#include <ncursesw/ncurses.h>
#else
#error "Missing ncurses header. Aborting..."
#endif

#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

#include "llist.h"
#include "vector.h"
#include "htable.h"
#include "llist_ts.h"

#include "cjson/cJSON.h"

/* Internationalization. */
#if ENABLE_NLS
#include <locale.h>
#include <libintl.h>
#undef _
#define _(String) gettext(String)
#ifdef gettext_noop
#define N_(String) gettext_noop(String)
#else
#define N_(String) (String)
#endif
#else /* NLS disabled */
#define _(String) (String)
#define N_(String) (String)
#define textdomain(String) (String)
#define gettext(String) (String)
#define dgettext(String) (String)
#define dcgettext(String) (String)
#define ngettext(String1,String2,n) ((n) == 1 ? (String1) : (String2))
#define bindtextdomain(String) (String)
#define bind_textdomain_codeset(Domain,Codeset) (Codeset)
#endif /* ENABLE_NLS */

/* Paths configuration. */
#define DIR_NAME         ".calcurse/"
#define TODO_PATH_NAME   "todo"
#define APTS_PATH_NAME   "apts"
#define CONF_PATH_NAME   "conf"
#define KEYS_PATH_NAME   "keys"
#define MEMO_PATH_NAME   "memo"
#define ABOOK_PATH_NAME  "abook"
#define LEDGER_PATH_NAME "ledger"
#define CPID_PATH_NAME   ".calcurse.pid"
#define DPID_PATH_NAME   ".daemon.pid"
#define DLOG_PATH_NAME   "daemon.log"
#define NOTES_DIR_NAME   "notes/"
#define HOOKS_DIR_NAME   "hooks/"

#define TODO_PATH        DIR_NAME TODO_PATH_NAME
#define APTS_PATH        DIR_NAME APTS_PATH_NAME
#define CONF_PATH        DIR_NAME CONF_PATH_NAME
#define KEYS_PATH        DIR_NAME KEYS_PATH_NAME
#define MEMO_PATH        DIR_NAME MEMO_PATH_NAME
#define LEDGER_PATH      DIR_NAME LEDGER_PATH_NAME
#define ABOOK_PATH	 DIR_NAME ABOOK_PATH_NAME
#define CPID_PATH        DIR_NAME CPID_PATH_NAME
#define DLOG_PATH        DIR_NAME DLOG_PATH_NAME
#define DPID_PATH        DIR_NAME DPID_PATH_NAME
#define NOTES_DIR        DIR_NAME NOTES_DIR_NAME
#define HOOKS_DIR        DIR_NAME HOOKS_DIR_NAME

#define DEFAULT_EDITOR     "vim"
#define DEFAULT_PAGER      "less"
#define DEFAULT_MERGETOOL  "vimdiff"

// wwei 2016.06.09 add for diary function start
#define DEFAULT_DIARY_ROOT_PATH	   "/home/kevin/diary"
#define DEFAULT_STUDY_ROOT_FILE    "/home/kevin/study/study.txt"
#define DEFAULT_SECRET_ROOT_FILE   "/home/kevin/study/secret.txt"
#define DEFAULT_LEDGER_SCRIPT_NAME "ledger-run.sh"
#define DEFAULT_LEDGER_FILE 	   "/home/kevin/DataLibrary/kevin.wang-account/ledger/kevin-ledger.ldg"
// wwei 2016.06.09 add for diary function end 

#define CALCURSE_TEMP_FILE   "/tmp/calcurse.tmp"

#define INSIZE_PASSWD "zaqwsx"

#define ATTR_FALSE    0
#define ATTR_TRUE     1
#define ATTR_LOWEST   2
#define ATTR_LOW      3
#define ATTR_MIDDLE   4
#define ATTR_HIGH     5
#define ATTR_HIGHEST  6

#define STATUSHEIGHT  2
#define MAX_NOTESIZ   40

/* Format for appointment hours is: HH:MM */
#define HRMIN_SIZE 6

/* Maximum number of colors available. */
#define NBUSERCOLORS  6

/* Side bar width acceptable boundaries. */
#define SBARMINWIDTH     32
#define SBARMAXWIDTHPERC 50

/* Related to date manipulation. */
#define YEARINMONTHS    12
#define YEARINDAYS      365
#define TM_YEAR_BASE    1900

#define WEEKINDAYS      7
#define DAYINHOURS      24
#define HOURINMIN       60
#define MININSEC        60

#define WEEKINHOURS     (WEEKINDAYS * DAYINHOURS)
#define WEEKINMIN       (WEEKINHOURS * HOURINMIN)
#define WEEKINSEC       (WEEKINMIN * MININSEC)
#define DAYINMIN        (DAYINHOURS * HOURINMIN)
#define DAYINSEC        (DAYINMIN * MININSEC)
#define HOURINSEC       (HOURINMIN * MININSEC)

#define MAXDAYSPERMONTH 31

/* Calendar window. */
#define CALHEIGHT       8

/* Ledger window */
#define LEDWIDTH        56 

/* Key definitions. */
#define CTRLVAL                 0x1F
#define CTRL(x)                 ((x) & CTRLVAL)
#define ESCAPE                  27
#define TAB                     9
#define SPACE                   32

#define KEYS_KEYLEN         3	/* length of each keybinding */
#define KEYS_LABELEN        8	/* length of command description */
#define KEYS_CMDS_PER_LINE  6	/* max number of commands per line */

/* Register definitions. */
#define REG_BLACK_HOLE 37

/* Size of the hash table the note garbage collector uses. */
#define NOTE_GC_HSIZE 1024

#define ERROR_MSG(...) do {                                                   \
  char msg[BUFSIZ];                                                           \
  int len;                                                                    \
                                                                              \
  len = snprintf (msg, BUFSIZ, "%s: %d: ", __FILE__, __LINE__);               \
  snprintf (msg + len, BUFSIZ - len, __VA_ARGS__);                            \
  if (ui_mode == UI_CURSES)                                                   \
    fatalbox (msg);                                                           \
  else                                                                        \
    fprintf (stderr, "%s\n", msg);                                            \
} while (0)

#define WARN_MSG(...) do {                                                    \
  char msg[BUFSIZ];                                                           \
                                                                              \
  snprintf (msg, BUFSIZ, __VA_ARGS__);                                        \
  if (ui_mode == UI_CURSES)                                                   \
    warnbox (msg);                                                            \
  else                                                                        \
    fprintf (stderr, "%s\n", msg);                                            \
} while (0)

#define EXIT(...) do {                                                        \
  ERROR_MSG(__VA_ARGS__);                                                     \
  if (ui_mode == UI_CURSES)                                                   \
    exit_calcurse (EXIT_FAILURE);                                             \
  else                                                                        \
    exit (EXIT_FAILURE);                                                      \
} while (0)

#define EXIT_IF(cond, ...) do {                                               \
  if ((cond))                                                                 \
    EXIT(__VA_ARGS__);                                                        \
} while (0)

#define RETURN_IF(cond, ...) do {                                             \
  if ((cond))                                                                 \
    {                                                                         \
      ERROR_MSG(__VA_ARGS__);                                                 \
      return;                                                                 \
    }                                                                         \
} while (0)

#define RETVAL_IF(cond, val, ...) do {                                        \
  if ((cond))                                                                 \
    {                                                                         \
      ERROR_MSG(__VA_ARGS__);                                                 \
      return (val);                                                           \
    }                                                                         \
} while (0)

#define DMON_LOG(...) do {                                      	      \
  if (dmon.log)                                                 	      \
    io_fprintln (path_dmon_log, __VA_ARGS__);                   	      \
} while (0)

#define STRINGIFY(x)  #x
#define TOSTRING(x)   STRINGIFY(x)
#define __FILE_POS__   __FILE__ ":" TOSTRING(__LINE__)

#define UTF8_MAXLEN 6
#define UTF8_LENGTH(ch) ((unsigned char)ch >= 0xFC ? 6 : \
    ((unsigned char)ch >= 0xF8 ? 5 : \
    ((unsigned char)ch >= 0xF0 ? 4 : \
    ((unsigned char)ch >= 0xE0 ? 3 : \
    ((unsigned char)ch >= 0xC0 ? 2 : 1)))))
#define UTF8_ISCONT(ch) ((unsigned char)ch >= 0x80 && \
    (unsigned char)ch <= 0xBF)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))

enum win {
	CAL,
	APP,
	TOD,
	MEMO,
	LED,
	NOT,
	STA,
	KEY,
	NBWINS
};

/* General configuration variables. */
struct conf {
	unsigned auto_save;
	unsigned auto_gc;
	unsigned periodic_save;
	unsigned confirm_quit;
	unsigned confirm_delete;
	enum win default_panel;
	unsigned compact_panels;
	unsigned system_dialogs;
	unsigned progress_bar;
	const char *editor;
	const char *pager;
	const char *mergetool;
	char output_datefmt[BUFSIZ];	/* format for displaying date */
	int input_datefmt;	/* format for reading date */

// wwei 2016.06.09 add for diary function start
	char diary_path[256];
	char study_path[256];
	char secret_path[256];
	char ledger_script_name[128]; 
	char ledger_path[256]; 
// wwei 2016.06.09 add for diary function end 
};

/* Daemon-related configuration. */
struct dmon_conf {
	unsigned enable;	/* launch daemon automatically when exiting */
	unsigned log;		/* log daemon activity */
};

/* Input date formats. */
enum datefmt {
	DATEFMT_MMDDYYYY = 1,
	DATEFMT_DDMMYYYY,
	DATEFMT_YYYYMMDD,
	DATEFMT_ISO,
	DATEFMT_MAX
};

#define DATE_FORMATS (DATEFMT_MAX - 1)

#define DATEFMT(datefmt) (datefmt == DATEFMT_MMDDYYYY ? "%m/%d/%Y" :          \
    (datefmt == DATEFMT_DDMMYYYY ? "%d/%m/%Y" :                               \
    (datefmt == DATEFMT_YYYYMMDD ? "%Y/%m/%d" : "%Y-%m-%d")))

#define DATEFMT_DESC(datefmt) (datefmt == DATEFMT_MMDDYYYY ?                  \
    _("mm/dd/yyyy") : (datefmt == DATEFMT_DDMMYYYY ? _("dd/mm/yyyy") :        \
    (datefmt == DATEFMT_YYYYMMDD ? _("yyyy/mm/dd") : _("yyyy-mm-dd"))))

struct date {
	unsigned dd;
	unsigned mm;
	unsigned yyyy;
};

/* Appointment definition. */
struct apoint {
	long start;		/* seconds since 1 jan 1970 */
	long dur;		/* duration of the appointment in seconds */

#define APOINT_NULL      0x0
#define APOINT_NOTIFY    0x1	/* Item needs to be notified */
#define APOINT_NOTIFIED  0x2	/* Item was already notified */
	int state;

	char *mesg;
	char *note;
};

/* Event definition. */
struct event {
	int id;			/* event identifier */
	long day;		/* seconds since 1 jan 1970 */
	char *mesg;
	char *note;
};

/* Todo item definition. */
struct todo {
	char *mesg;
	int id;
	int completed;
	char *note;
	char *deadline;
	struct tm deaddate;
};

/* Memo item definition. */
struct memo {
	char *mesg;
};

/* Ledger item definition. */
struct ledger {
	char *mesg;
};

struct excp {
	long st;		/* beggining of the considered day, in seconds */
};

enum recur_type {
	RECUR_NO,
	RECUR_DAILY,
	RECUR_WEEKLY,
	RECUR_MONTHLY,
	RECUR_YEARLY,
	RECUR_TYPES
};

/* To describe an item's repetition. */
struct rpt {
	enum recur_type type;	/* repetition type */
	int freq;		/* repetition frequence */
	long until;		/* ending date for repeated event */
};

/* Recurrent appointment definition. */
struct recur_apoint {
	struct rpt *rpt;	/* information about repetition */
	llist_t exc;		/* days when the item should not be repeated */
	long start;		/* beggining of the appointment */
	long dur;		/* duration of the appointment */
	char state;		/* 8 bits to store item state */
	char *mesg;		/* appointment description */
	char *note;		/* note attached to appointment */
};

/* Reccurent event definition. */
struct recur_event {
	struct rpt *rpt;	/* information about repetition */
	llist_t exc;		/* days when the item should not be repeated */
	int id;			/* event type */
	long day;		/* day at which event occurs */
	char *mesg;		/* event description */
	char *note;		/* note attached to event */
};

/* Generic pointer data type for appointments and events. */
union aptev_ptr {
	struct apoint *apt;
	struct event *ev;
	struct recur_apoint *rapt;
	struct recur_event *rev;
};

/* Available item types in the calendar view. */
enum day_item_type {
	DAY_HEADING = 1,
	RECUR_EVNT,
	EVNT,
	DAY_SEPARATOR,
	RECUR_APPT,
	APPT
};

/* Available item types. */
enum item_type {
	TYPE_EVNT,
	TYPE_APPT,
	TYPE_RECUR_EVNT,
	TYPE_RECUR_APPT,
	TYPE_TODO
};

/* Available item type masks. */
#define TYPE_MASK_EVNT (1 << TYPE_EVNT)
#define TYPE_MASK_APPT (1 << TYPE_APPT)
#define TYPE_MASK_RECUR_EVNT (1 << TYPE_RECUR_EVNT)
#define TYPE_MASK_RECUR_APPT (1 << TYPE_RECUR_APPT)
#define TYPE_MASK_RECUR (TYPE_MASK_RECUR_EVNT | TYPE_MASK_RECUR_APPT)
#define TYPE_MASK_CAL (TYPE_MASK_EVNT | TYPE_MASK_APPT | TYPE_MASK_RECUR)
#define TYPE_MASK_TODO (1 << TYPE_TODO)
#define TYPE_MASK_ALL (TYPE_MASK_CAL | TYPE_MASK_TODO)

/* Filter settings. */
struct item_filter {
	int type_mask;
	char *hash;
	regex_t *regex;
	time_t start_from;
	time_t start_to;
	time_t end_from;
	time_t end_to;
	int priority;
	int completed;
	int uncompleted;
};

/* Generic item description (to hold appointments, events...). */
struct day_item {
	enum day_item_type type;
	long start;
	union aptev_ptr item;
};

/* Available views for the calendar panel. */
enum {
	CAL_MONTH_VIEW,
	CAL_WEEK_VIEW,
	CAL_DAY_VIEW,
	CAL_VIEWS
};

/* Available views for the todo panel. */
enum {
	TODO_SHOW_COMPLETED_VIEW,
	TODO_HIDE_COMPLETED_VIEW,
	TODO_VIEWS
};

/* Available views for the memo panel. */
enum {
	MEMO_DRAFT_VIEW,
	MEMO_ABOOK_VIEW,
	MEMO_VIEWS
};

struct notify_app {
	long time;
	int got_app;
	char *txt;
	char state;
	pthread_mutex_t mutex;
};

struct io_file {
	FILE *fd;
	char name[BUFSIZ];
};

/* Available keys. */
enum key {
	KEY_GENERIC_CANCEL,
	KEY_GENERIC_SELECT,
	KEY_GENERIC_CREDITS,
	KEY_GENERIC_HELP,
	KEY_GENERIC_QUIT,
	KEY_GENERIC_SAVE,
	KEY_GENERIC_RELOAD,
	KEY_GENERIC_COPY,
	KEY_GENERIC_PASTE,
	KEY_GENERIC_CHANGE_VIEW,
	KEY_GENERIC_IMPORT,
	KEY_GENERIC_EXPORT,
	KEY_GENERIC_GOTO,
	KEY_GENERIC_OTHER_CMD,
	KEY_GENERIC_CONFIG_MENU,
	KEY_GENERIC_REDRAW,
	KEY_GENERIC_ADD_APPT,
	KEY_GENERIC_ADD_TODO,
	KEY_GENERIC_PREV_DAY,
	KEY_GENERIC_NEXT_DAY,
	KEY_GENERIC_PREV_WEEK,
	KEY_GENERIC_NEXT_WEEK,
	KEY_GENERIC_PREV_MONTH,
	KEY_GENERIC_NEXT_MONTH,
	KEY_GENERIC_PREV_YEAR,
	KEY_GENERIC_NEXT_YEAR,
	KEY_GENERIC_SCROLL_DOWN,
	KEY_GENERIC_SCROLL_UP,
	KEY_GENERIC_GOTO_TODAY,
	KEY_GENERIC_CMD,

	KEY_MOVE_RIGHT,
	KEY_MOVE_LEFT,
	KEY_MOVE_DOWN,
	KEY_MOVE_UP,
	KEY_START_OF_WEEK,
	KEY_END_OF_WEEK,
	KEY_ADD_ITEM,
	KEY_DEL_ITEM,
	KEY_EDIT_ITEM,
	KEY_VIEW_ITEM,
	KEY_PIPE_ITEM,
	KEY_FLAG_ITEM,
	KEY_REPEAT_ITEM,
	KEY_EDIT_NOTE,
	KEY_VIEW_NOTE,
	KEY_RAISE_PRIORITY,
	KEY_LOWER_PRIORITY,

	// wwei 2016.06.09 add for dirary edit function start
	/* my function key */
	KEY_DIARY_EDIT,
	KEY_STUDY_EDIT,
	KEY_SECRET_EDIT,
	KEY_MEMO_EDIT,
	KEY_LEDGER_SHOW,
	KEY_LEDGER_EDIT,

	NBKEYS,
	KEY_UNDEF,

	/* Non-configurable, context sensitive key bindings. */
	KEY_CONFIGMENU_GENERAL,
	KEY_CONFIGMENU_LAYOUT,
	KEY_CONFIGMENU_SIDEBAR,
	KEY_CONFIGMENU_COLOR,
	KEY_CONFIGMENU_NOTIFY,
	KEY_CONFIGMENU_KEYS
};

#define FLAG_CAL (1 << CAL)
#define FLAG_APP (1 << APP)
#define FLAG_TOD (1 << TOD)
#define FLAG_MEMO (1 << MEMO)
#define FLAG_LED (1 << LED)
#define FLAG_NOT (1 << NOT)
#define FLAG_STA (1 << STA)
#define FLAG_ALL ((1 << NBWINS) - 1)

#define WINS_NBAR_LOCK \
  pthread_cleanup_push(wins_nbar_cleanup, NULL); \
  wins_nbar_lock();

#define WINS_NBAR_UNLOCK \
  wins_nbar_unlock(); \
  pthread_cleanup_pop(0);

#define WINS_CALENDAR_LOCK \
  pthread_cleanup_push(wins_calendar_cleanup, NULL); \
  wins_calendar_lock();

#define WINS_CALENDAR_UNLOCK \
  wins_calendar_unlock(); \
  pthread_cleanup_pop(0);

enum ui_mode {
	UI_CURSES,
	UI_CMDLINE,
	UI_MODES
};

/* Generic window structure. */
struct window {
	WINDOW *p;		/* pointer to window */
	unsigned w;		/* width */
	unsigned h;		/* height */
	int x;			/* x position */
	int y;			/* y position */
};

/* Generic scrolling window structure. */
struct scrollwin {
	WINDOW *win;
	WINDOW *inner;
	int y;
	int x;
	int h;
	int w;
	unsigned line_off;
	unsigned line_num;
	const char *label;
};

/* Generic list box structure. */
enum listbox_row_type {
	LISTBOX_ROW_TEXT,
	LISTBOX_ROW_CAPTION
};

typedef enum listbox_row_type (*listbox_fn_item_type_t) (int, void *);
typedef int (*listbox_fn_item_height_t) (int, void *);
typedef void (*listbox_fn_draw_item_t) (int, WINDOW *, int, int, void *);

struct listbox {
	struct scrollwin sw;
	unsigned item_count;
	int item_sel;
	listbox_fn_item_type_t fn_type;
	enum listbox_row_type *type;
	listbox_fn_item_height_t fn_height;
	unsigned *ch;
	listbox_fn_draw_item_t fn_draw;
	void *cb_data;
};

/* Pad structure to handle scrolling. */
struct pad {
	int width;
	int length;
	int first_onscreen;	/* first line to be displayed inside window */
	WINDOW *ptrwin;		/* pointer to the pad window */
};

/* Notification bar definition. */
#define NOTIFY_FLAGGED_ONLY    0
#define NOTIFY_UNFLAGGED_ONLY  1
#define NOTIFY_ALL             2

struct nbar {
	unsigned show;		/* display or hide the notify-bar */
	int cntdwn;		/* warn when time left before next app
				   becomes lesser than cntdwn */
	char datefmt[BUFSIZ];	/* format for displaying date */
	char timefmt[BUFSIZ];	/* format for displaying time */
	char cmd[BUFSIZ];	/* notification command */
	const char *shell;	/* user shell to launch notif. cmd */
	unsigned notify_all;	/* notify all appointments */
	pthread_mutex_t mutex;
};

/* Dynamic strings. */
struct string {
	char *buf;
	int bufsize;
	int len;
};

/* ABook struct */
typedef struct _ABOOK {
	char* name;		/* 联系人姓名 */
	char* email;		/* 联系人E-mail地址 */
	char* description;      /* 描述信息 */
} ABOOK;

/* Return codes for the getstring() function. */
enum getstr {
	GETSTRING_VALID,
	GETSTRING_ESC,		/* user pressed escape to cancel editing. */
	GETSTRING_RET		/* return was pressed without entering any text. */
};

/* Return codes for parse_datetime(). */
#define PARSE_DATETIME_HAS_DATE (1 << 0)
#define PARSE_DATETIME_HAS_TIME (1 << 1)

/* Week days. */
enum wday {
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	WDAYS
};

/* Possible movements inside calendar. */
enum move {
	DAY_PREV,
	DAY_NEXT,
	WEEK_PREV,
	WEEK_NEXT,
	WEEK_START,
	WEEK_END,
	MONTH_PREV,
	MONTH_NEXT,
	YEAR_PREV,
	YEAR_NEXT
};

/* Available color pairs. */
enum {
	COLR_RED = 1,
	COLR_GREEN,
	COLR_YELLOW,
	COLR_BLUE,
	COLR_MAGENTA,
	COLR_CYAN,
	COLR_DEFAULT,
	COLR_HIGH,
	COLR_CUSTOM,

	COLR_PRI0,
	COLR_PRI1,
	COLR_PRI2,
	COLR_PRI3,
	COLR_PRI4,
	COLR_PRI5,
	COLR_PRI6,
	COLR_PRI7,
	COLR_PRI8,
	COLR_PRI9,
	COLR_PRI10,

	COLR_HIPRI0,
	COLR_HIPRI1,
	COLR_HIPRI2,
	COLR_HIPRI3,
	COLR_HIPRI4,
	COLR_HIPRI5,
	COLR_HIPRI6,
	COLR_HIPRI7,
	COLR_HIPRI8,
	COLR_HIPRI9,
	COLR_HIPRI10,
	COLR_HIBORD
};

/* Available import types. */
enum import_type {
	IO_IMPORT_ICAL,
	IO_IMPORT_NBTYPES
};

/* Available export types. */
enum export_type {
	IO_EXPORT_ICAL,
	IO_EXPORT_PCAL,
	IO_EXPORT_NBTYPES
};

/* To customize the display when saving data. */
enum save_display {
	IO_SAVE_DISPLAY_BAR,
	IO_SAVE_DISPLAY_NONE
};

/* apoint.c */
extern llist_ts_t alist_p;
void apoint_free_bkp(void);
struct apoint *apoint_dup(struct apoint *);
void apoint_free(struct apoint *);
void apoint_llist_init(void);
void apoint_llist_free(void);
struct apoint *apoint_new(char *, char *, long, long, char);
unsigned apoint_inday(struct apoint *, long *);
void apoint_sec2str(struct apoint *, long, char *, char *);
char *apoint_tostr(struct apoint *);
char *apoint_hash(struct apoint *);
void apoint_write(struct apoint *, FILE *);
struct apoint *apoint_scan(FILE *, struct tm, struct tm, char, char *,
			   struct item_filter *);
void apoint_delete(struct apoint *);
struct notify_app *apoint_check_next(struct notify_app *, long);
void apoint_switch_notify(struct apoint *);
void apoint_paste_item(struct apoint *, long);

/* args.c */
int parse_args(int, char **);

/* calendar.c */
void ui_calendar_view_next(void);
void ui_calendar_view_prev(void);
void ui_calendar_set_view(int);
int ui_calendar_get_view(void);
void ui_calendar_start_date_thread(void);
void ui_calendar_stop_date_thread(void);
void ui_calendar_set_current_date(void);
void ui_calendar_set_first_day_of_week(enum wday);
void ui_calendar_change_first_day_of_week(void);
unsigned ui_calendar_week_begins_on_monday(void);
void ui_calendar_store_current_date(struct date *);
void ui_calendar_init_slctd_day(void);
struct date *ui_calendar_get_slctd_day(void);
time_t ui_calendar_get_slctd_day_sec(void);
void ui_calendar_monthly_view_cache_set_invalid(void);
void ui_calendar_update_panel(void);
void ui_calendar_goto_today(void);
void ui_calendar_change_day(int);
void ui_calendar_move(enum move, int);
long ui_calendar_start_of_year(void);
long ui_calendar_end_of_year(void);
const char *ui_calendar_get_pom(time_t);

/* config.c */

void config_load(void);
unsigned config_save(void);

/* custom.c */
void custom_init_attr(void);
void custom_apply_attr(WINDOW *, int);
void custom_remove_attr(WINDOW *, int);
void custom_layout_config(void);
void custom_sidebar_config(void);
void custom_color_config(void);
void custom_color_theme_name(char *);
void custom_confwin_init(struct window *, const char *);
void custom_set_swsiz(struct scrollwin *);
void custom_general_config(void);
void custom_keys_config(void);
void custom_config_main(void);

// wwei 2016.06.18 set color of todo item as priority start
void set_pri_color(WINDOW *, int);
void reset_pri_color(WINDOW *, int);
// wwei 2016.06.18 set color of todo item as priority end 

/* day.c */
void day_free_vector(void);
char *day_item_get_mesg(struct day_item *);
char *day_item_get_note(struct day_item *);
void day_item_erase_note(struct day_item *);
long day_item_get_duration(struct day_item *);
int day_item_get_state(struct day_item *);
void day_item_add_exc(struct day_item *, long);
void day_item_fork(struct day_item *, struct day_item *);
void day_store_items(long, int);
void day_process_storage(struct date *, unsigned);
void day_display_item_date(struct day_item *, WINDOW *, int, long, int, int);
void day_display_item(struct day_item *, WINDOW *, int, int, int, int);
void day_write_stdout(long, const char *, const char *, const char *,
		      const char *, int *);
void day_popup_item(struct day_item *);
int day_check_if_item(struct date);
unsigned day_chk_busy_slices(struct date, int, int *);
struct day_item *day_cut_item(long, int);
int day_paste_item(struct day_item *, long);
int day_get_position_by_aptev_ptr(union aptev_ptr);
int day_get_position(struct day_item *);
struct day_item *day_get_item(int);
unsigned day_item_count(int);
void day_edit_note(struct day_item *, const char *);
void day_view_note(struct day_item *, const char *);
void day_item_switch_notify(struct day_item *);

/* dmon.c */
void dmon_start(int);
void dmon_stop(void);

/* event.c */
extern llist_t eventlist;
void event_free_bkp(void);
struct event *event_dup(struct event *);
void event_free(struct event *);
void event_llist_init(void);
void event_llist_free(void);
struct event *event_new(char *, char *, long, int);
unsigned event_inday(struct event *, long *);
char *event_tostr(struct event *);
char *event_hash(struct event *);
void event_write(struct event *, FILE *);
struct event *event_scan(FILE *, struct tm, int, char *, struct item_filter *);
void event_delete(struct event *);
void event_paste_item(struct event *, long);

/* getstring.c */
enum getstr getstring(WINDOW *, char *, int, int, int);
enum getstr getpasswdstring(WINDOW *, char *, int, int, int);
int updatestring(WINDOW *, char **, int, int);

/* help.c */
int display_help(const char *);

/* hooks.c */
int run_hook(const char *);

/* ical.c */
void ical_import_data(FILE *, FILE *, unsigned *, unsigned *, unsigned *,
		      unsigned *, unsigned *, const char *, const char *,
		      const char *, const char *, const char *);
void ical_export_data(FILE *, int);

/* io.c */
unsigned io_fprintln(const char *, const char *, ...);
void io_init(const char *, const char *);
void io_extract_data(char *, const char *, int);
void io_save_mutex_lock(void);
void io_save_mutex_unlock(void);
void io_dump_apts(const char *, const char *, const char *, const char *);
unsigned io_save_apts(const char *);
void io_dump_todo(const char *);
unsigned io_save_todo(const char *);
unsigned io_save_keys(void);
void io_save_cal(enum save_display);
void io_load_app(struct item_filter *);
void io_load_todo(struct item_filter *);
void io_load_memo(struct item_filter *);
void io_load_abook(struct item_filter *);
void io_load_blank(void);
void io_load_ledger(struct item_filter *);
void io_load_data(struct item_filter *);
void io_reload_data(void);
void io_load_keys(const char *);
int io_check_dir(const char *);
unsigned io_dir_exists(const char *);
unsigned io_file_exists(const char *);
int io_check_file(const char *);
int io_check_data_files(void);
void io_startup_screen(int);
void io_export_data(enum export_type, int);
void io_import_data(enum import_type, const char *, const char *, const char *,
		    const char *, const char *, const char *);
struct io_file *io_log_init(void);
void io_log_print(struct io_file *, int, const char *);
void io_log_display(struct io_file *, const char *, const char *);
void io_log_free(struct io_file *);
void io_start_psave_thread(void);
void io_stop_psave_thread(void);
void io_set_lock(void);
unsigned io_dump_pid(char *);
unsigned io_get_pid(char *);
int io_files_equal(const char *, const char *);
int io_file_is_empty(char *);
int io_file_cp(const char *, const char *);
void io_unset_modified(void);
void io_set_modified(void);
int io_get_modified(void);

/* keys.c */
void keys_init(void);
void keys_free(void);
void keys_dump_defaults(char *);
const char *keys_get_label(enum key);
enum key keys_get_action(int);
enum key keys_getch(WINDOW * win, int *, int *);
int keys_assign_binding(int, enum key);
void keys_remove_binding(int, enum key);
int keys_str2int(const char *);
const char *keys_int2str(int);
int keys_action_count_keys(enum key);
const char *keys_action_firstkey(enum key);
const char *keys_action_nkey(enum key, int);
char *keys_action_allkeys(enum key);
void keys_display_bindings_bar(WINDOW *, int *, int, int, int);
void keys_popup_info(enum key);
void keys_save_bindings(FILE *);
int keys_check_missing_bindings(void);
void keys_fill_missing(void);

/* listbox.c */
void listbox_init(struct listbox *, int, int, int, int, const char *,
		  listbox_fn_item_type_t, listbox_fn_item_height_t,
		  listbox_fn_draw_item_t);
void listbox_delete(struct listbox *);
void listbox_resize(struct listbox *, int, int, int, int);
void listbox_set_cb_data(struct listbox *, void *);
void listbox_load_items(struct listbox *, int);
void listbox_draw_deco(struct listbox *, int);
void listbox_display(struct listbox *);
int listbox_get_sel(struct listbox *);
void listbox_set_sel(struct listbox *, unsigned);
void listbox_sel_move(struct listbox *, int);

/* mem.c */
void *xmalloc(size_t);
void *xcalloc(size_t, size_t);
void *xrealloc(void *, size_t, size_t);
char *xstrdup(const char *);
void xfree(void *);

/* kevin functions  */
struct tm parse_deadline(const char* deadline);
void parse_deadline_date(struct tm date,char *buf);
int check_deadline_available(char *deadline);

#ifdef CALCURSE_MEMORY_DEBUG

#define mem_malloc(s)         dbg_malloc ((s), __FILE_POS__)
#define mem_calloc(n, s)      dbg_calloc ((n), (s), __FILE_POS__)
#define mem_realloc(p, n, s)  dbg_realloc ((p), (n), (s), __FILE_POS__)
#define mem_strdup(s)         dbg_strdup ((s), __FILE_POS__)
#define mem_free(p)           dbg_free ((p), __FILE_POS__)

void *dbg_malloc(size_t, const char *);
void *dbg_calloc(size_t, size_t, const char *);
void *dbg_realloc(void *, size_t, size_t, const char *);
char *dbg_strdup(const char *, const char *);
void dbg_free(void *, const char *);
void mem_stats(void);

#else /* MEMORY DEBUG disabled */

#define mem_malloc(s)         xmalloc ((s))
#define mem_calloc(n, s)      xcalloc ((n), (s))
#define mem_realloc(p, n, s)  xrealloc ((p), (n), (s))
#define mem_strdup(s)         xstrdup ((s))
#define mem_free(p)           xfree ((p))
#define mem_stats()

#endif /* CALCURSE_MEMORY_DEBUG */

/* note.c */
char *generate_note(const char *);
void edit_note(char **, const char *);
void view_note(const char *, const char *);
void erase_note(char **);
void note_read(char *, FILE *);
void note_gc(void);

/* notify.c */
int notify_time_left(void);
unsigned notify_needs_reminder(void);
void notify_update_app(long, char, char *);
int notify_bar(void);
void notify_init_vars(void);
void notify_init_bar(void);
void notify_free_app(void);
void notify_start_main_thread(void);
void notify_stop_main_thread(void);
void notify_reinit_bar(void);
unsigned notify_launch_cmd(char *);
void notify_update_bar(void);
unsigned notify_get_next(struct notify_app *);
unsigned notify_get_next_bkgd(void);
char *notify_app_txt(void);
void notify_check_next_app(int);
void notify_check_added(char *, long, char);
void notify_check_repeated(struct recur_apoint *);
int notify_same_item(long);
int notify_same_recur_item(struct recur_apoint *);
void notify_config_bar(void);

/* pcal.c */
void pcal_export_data(FILE *);

/* recur.c */
extern llist_ts_t recur_alist_p;
extern llist_t recur_elist;
struct recur_event *recur_event_dup(struct recur_event *);
struct recur_apoint *recur_apoint_dup(struct recur_apoint *);
void recur_event_free_bkp(void);
void recur_apoint_free_bkp(void);
void recur_event_free(struct recur_event *);
void recur_apoint_free(struct recur_apoint *);
void recur_apoint_llist_init(void);
void recur_event_llist_init(void);
void recur_apoint_llist_free(void);
void recur_event_llist_free(void);
struct recur_apoint *recur_apoint_new(char *, char *, long, long, char,
				      int, int, long, llist_t *);
struct recur_event *recur_event_new(char *, char *, long, int, int, int,
				    long, llist_t *);
char recur_def2char(enum recur_type);
int recur_char2def(char);
struct recur_apoint *recur_apoint_scan(FILE *, struct tm, struct tm,
				       char, int, struct tm, char *,
				       llist_t *, char, struct item_filter *);
struct recur_event *recur_event_scan(FILE *, struct tm, int, char,
				     int, struct tm, char *, llist_t *,
				     struct item_filter *);
char *recur_apoint_tostr(struct recur_apoint *);
char *recur_apoint_hash(struct recur_apoint *);
void recur_apoint_write(struct recur_apoint *, FILE *);
char *recur_event_tostr(struct recur_event *);
char *recur_event_hash(struct recur_event *);
void recur_event_write(struct recur_event *, FILE *);
void recur_save_data(FILE *);
unsigned recur_item_find_occurrence(long, long, llist_t *, int,
				    int, long, long, time_t *);
unsigned recur_apoint_find_occurrence(struct recur_apoint *, long, time_t *);
unsigned recur_event_find_occurrence(struct recur_event *, long, time_t *);
unsigned recur_item_inday(long, long, llist_t *, int, int, long, long);
unsigned recur_apoint_inday(struct recur_apoint *, long *);
unsigned recur_event_inday(struct recur_event *, long *);
void recur_event_add_exc(struct recur_event *, long);
void recur_apoint_add_exc(struct recur_apoint *, long);
void recur_event_erase(struct recur_event *);
void recur_apoint_erase(struct recur_apoint *);
void recur_exc_scan(llist_t *, FILE *);
struct notify_app *recur_apoint_check_next(struct notify_app *, long,
					   long);
void recur_apoint_switch_notify(struct recur_apoint *);
void recur_event_paste_item(struct recur_event *, long);
void recur_apoint_paste_item(struct recur_apoint *, long);

/* sigs.c */
void sigs_init(void);
unsigned sigs_set_hdlr(int, void (*)(int));
void sigs_ignore(void);
void sigs_unignore(void);

/* strings.c */
void string_init(struct string *);
void string_reset(struct string *);
int string_grow(struct string *, int);
char *string_buf(struct string *);
int string_catf(struct string *, const char *, ...);
int string_vcatf(struct string *, const char *, va_list);
int string_printf(struct string *, const char *, ...);

/* todo.c */
extern llist_t todolist;
struct todo *todo_get_item(int, int);
struct todo *todo_add(char *, int, char *, int, char *);
char *todo_tostr(struct todo *);
char *todo_hash(struct todo *);
void todo_write(struct todo *, FILE *);
void todo_delete_note(struct todo *);
void todo_delete(struct todo *);
void todo_resort(struct todo *);
void todo_flag(struct todo *);
int todo_get_position(struct todo *, int);
void todo_edit_note(struct todo *, const char *);
void todo_view_note(struct todo *, const char *);
void todo_free(struct todo *);
void todo_init_list(void);
void todo_free_list(void);

/* memo.c */
extern llist_t memolist;
void memo_free(struct memo *memo);
void memo_init_list(void);
void memo_free_list(void);
struct memo *memo_add(char *mesg);

/* ledger.c */
extern llist_t ledgerlist;
void ledger_free(struct ledger *ledger);
void ledger_init_list(void);
void ledger_free_list(void);
struct ledger *ledger_add(char *mesg);

/* ui-day.c */
struct day_item *ui_day_selitem(void);
void ui_day_set_selitem_by_aptev_ptr(union aptev_ptr);
void ui_day_set_selitem(struct day_item *);
void ui_day_item_add(void);
void ui_day_item_delete(unsigned);
void ui_day_item_edit(void);
void ui_day_item_pipe(void);
void ui_day_item_repeat(void);
void ui_day_item_cut_free(unsigned);
void ui_day_item_copy(unsigned);
void ui_day_item_paste(unsigned);
void ui_day_load_items(void);
void ui_day_sel_reset(void);
void ui_day_sel_move(int);
void ui_day_draw(int, WINDOW *, int, int, void *);
enum listbox_row_type ui_day_row_type(int, void *);
int ui_day_height(int, void *);
void ui_day_update_panel(int);
void ui_day_popup_item(void);
void ui_day_flag(void);
void ui_day_view_note(void);
void ui_day_edit_note(void);

/* ui-todo.c */
void ui_todo_add(void);
void ui_todo_delete(void);
void ui_todo_edit(void);
void ui_todo_pipe(void);
void ui_todo_draw(int, WINDOW *, int, int, void *);
enum listbox_row_type ui_todo_row_type(int, void *);
int ui_todo_height(int, void *);
void ui_todo_load_items(void);
void ui_todo_sel_reset(void);
void ui_todo_sel_move(int);
void ui_memo_win_scrol(int);

void ui_todo_update_panel(int);
void ui_todo_chg_priority(int);
void ui_todo_popup_item(void);
void ui_todo_flag(void);
void ui_todo_view_note(void);
void ui_todo_edit_note(void);
void ui_todo_view_prev(void);
void ui_todo_view_next(void);
int ui_todo_get_view(void);
void ui_todo_set_view(int);

/* ui-memo.c */
void ui_memo_draw(int, WINDOW *, int, int, void *);
enum listbox_row_type ui_memo_row_type(int, void *);
int ui_memo_height(int, void *);
void ui_memo_update_panel(int);
void ui_memo_load_items(void);

/* ui-ledger.c */
void ui_ledger_draw(int, WINDOW *, int, int, void *);
enum listbox_row_type ui_ledger_row_type(int, void *);
int ui_ledger_height(int, void *);
void ui_ledger_update_panel(int);
void ui_ledger_load_items(void);

/* utf8.c */
int utf8_width(char *);
int utf8_strwidth(char *);
int utf8_chop(char *, int);

/* utils.c */
void exit_calcurse(int) __attribute__ ((__noreturn__));
void free_user_data(void);
void fatalbox(const char *);
void warnbox(const char *);
void status_mesg(const char *, const char *);
int status_ask_choice(const char *, const char[], int);
int status_ask_bool(const char *);
int status_ask_simplechoice(const char *, const char *[], int);
void erase_window_part(WINDOW *, int, int, int, int);
WINDOW *popup(int, int, int, int, const char *, const char *, int);
void print_in_middle(WINDOW *, int, int, int, const char *);
int is_all_digit(const char *);
long get_item_time(long);
int get_item_hour(long);
int get_item_min(long);
struct tm date2tm(struct date, unsigned, unsigned);
time_t date2sec(struct date, unsigned, unsigned);
time_t utcdate2sec(struct date, unsigned, unsigned);
int date_cmp_day(time_t, time_t);
char *date_sec2date_str(long, const char *);
void date_sec2date_fmt(long, const char *, char *);
int date_change(struct tm *, int, int);
long date_sec_change(long, int, int);
long update_time_in_date(long, unsigned, unsigned);
time_t get_sec_date(struct date);
long min2sec(unsigned);
void draw_scrollbar(WINDOW *, int, int, int, int, int, unsigned);
void item_in_popup(const char *, const char *, const char *, const char *);
time_t get_today(void);
long now(void);
char *nowstr(void);
void print_bool_option_incolor(WINDOW *, unsigned, int, int);
const char *get_tempdir(void);
char *new_tempfile(const char *);
int check_date(unsigned, unsigned, unsigned);
int parse_date(const char *, enum datefmt, int *, int *, int *,
	       struct date *);
int check_time(unsigned, unsigned);
int parse_time(const char *, unsigned *, unsigned *);
int parse_duration(const char *, unsigned *);
int parse_date_duration(const char *, unsigned *);
int parse_datetime(const char *, long *);
void file_close(FILE *, const char *);
void psleep(unsigned);
int fork_exec(int *, int *, const char *, const char *const *);
int shell_exec(int *, int *, const char *, const char *const *);
int child_wait(int *, int *, int);
void press_any_key(void);
void print_apoint(const char *, long, struct apoint *);
void print_event(const char *, long, struct event *);
void print_recur_apoint(const char *, long, time_t, struct recur_apoint *);
void print_recur_event(const char *, long, struct recur_event *);
void print_todo(const char *, struct todo *);
int vasprintf(char **, const char *, va_list);
int asprintf(char **, const char *, ...);
int starts_with(const char *, const char *);
int starts_with_ci(const char *, const char *);
int hash_matches(const char *, const char *);
int show_dialogs(void);

/* vars.c */
extern int col, row;
extern int resize;
extern unsigned colorize;
extern int foreground, background;
extern enum ui_mode ui_mode;
extern int read_only;
extern int quiet;
extern int want_reload;
extern const char *datefmt_str[DATE_FORMATS];
extern int days[12];
extern const char *monthnames[12];
extern const char *daynames[8];
extern char path_dir[BUFSIZ];
extern char path_todo[BUFSIZ];
extern char path_apts[BUFSIZ];
extern char path_conf[BUFSIZ];
extern char path_keys[BUFSIZ];
extern char path_memo[BUFSIZ];
extern char path_ledger[BUFSIZ];
extern char path_notes[BUFSIZ];
extern char path_cpid[BUFSIZ];
extern char path_dpid[BUFSIZ];
extern char path_dmon_log[BUFSIZ];
extern char path_hooks[BUFSIZ];
extern char path_abook[BUFSIZ];
extern struct conf conf;
extern struct pad apad;
extern struct nbar nbar;
extern struct dmon_conf dmon;
void vars_init(void);

/* wins.c */
extern struct window win[NBWINS];
extern struct scrollwin sw_cal;
extern struct listbox lb_apt;
extern struct listbox lb_todo;
extern struct listbox lb_memo;
extern struct listbox lb_ledger;
unsigned wins_nbar_lock(void);
void wins_nbar_unlock(void);
void wins_nbar_cleanup(void *);
unsigned wins_calendar_lock(void);
void wins_calendar_unlock(void);
void wins_calendar_cleanup(void *);
int wins_refresh(void);
int wins_wrefresh(WINDOW *);
int wins_doupdate(void);
int wins_layout(void);
void wins_set_layout(int);
unsigned wins_sbar_width(void);
unsigned wins_sbar_wperc(void);
void wins_set_sbar_width(unsigned);
void wins_sbar_winc(void);
void wins_sbar_wdec(void);
enum win wins_slctd(void);
void wins_slctd_set(enum win);
void wins_slctd_next(void);
void wins_init(void);
void wins_scrollwin_init(struct scrollwin *, int, int, int, int, const char *);
void wins_scrollwin_resize(struct scrollwin *, int, int, int, int);
void wins_scrollwin_set_linecount(struct scrollwin *, unsigned);
void wins_scrollwin_delete(struct scrollwin *);
void wins_scrollwin_draw_deco(struct scrollwin *, int);
void wins_scrollwin_display(struct scrollwin *);
void wins_scrollwin_up(struct scrollwin *, int);
void wins_scrollwin_down(struct scrollwin *, int);
int wins_scrollwin_is_visible(struct scrollwin *, unsigned);
void wins_scrollwin_ensure_visible(struct scrollwin *, unsigned);
void wins_scrollwin_set_lower(struct scrollwin *, unsigned);
void wins_resize(void);
void wins_resize_panels(void);
void wins_show(WINDOW *, const char *);
void wins_get_config(void);
void wins_update_border(int);
void wins_update_panels(int);
void wins_update(int);
void wins_reset_noupdate(void);
void wins_reset(void);
void wins_prepare_external(void);
void wins_unprepare_external(void);
void wins_launch_external(const char *[]);
void wins_set_bindings(int *, int);
void wins_update_bindings(void);
void wins_status_bar(void);
void wins_erase_status_bar(void);
void wins_other_status_page(int);
void wins_reset_status_page(void);

/* encrypt.c */
int unlink_file(const char* file); 
int rename_file(const char* src,const char* des);
int copy_file(const char* src,const char* des);
void encrypt_file(const char* src,const char* des);
void decrypt_file(const char* src,const char* des);

/* cjson.c */
void init_json_module();
void release_json_module();
void cjson_sync_disk();
void cjson_insert_element(ABOOK* ab);

#endif /* CALCURSE_H */
