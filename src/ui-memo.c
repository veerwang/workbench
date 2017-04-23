/*
 * Calcurse - text-based organizer
 *
 * Copyright (c) 2004-2016 calcurse Development Team <misc@calcurse.org>
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

#include "calcurse.h"
#include "string.h"

static unsigned ui_memo_view;

static void display_draft_view(void);
static void display_abook_view(void);
static void (* display_view[MEMO_VIEWS])(void) = {display_draft_view,display_abook_view};

/* Switch between memo views (memo view is selected by default). */
void ui_memo_view_next(void)
{
	ui_memo_view++;
	if (ui_memo_view == MEMO_VIEWS)
		ui_memo_view = 0;
}

void ui_memo_view_prev(void)
{
	if (ui_memo_view == 0)
		ui_memo_view = MEMO_VIEWS;
	ui_memo_view--;
}

void ui_memo_set_view(int view)
{
	ui_memo_view = (view < 0
			    || view >= MEMO_VIEWS) ? MEMO_DRAFT_VIEW : view;
}

int ui_memo_get_view(void)
{
	return (int)ui_memo_view;
}

enum listbox_row_type ui_memo_row_type(int i, void *cb_data)
{
	return LISTBOX_ROW_TEXT;
}

int ui_memo_height(int n, void *cb_data)
{
	return 1;
}

void ui_memo_draw(int n, WINDOW *win, int y, int hilt, void *cb_data)
{
	llist_item_t *i = *((llist_item_t **)cb_data);
	struct memo *memo = LLIST_TS_GET_DATA(i);
	int width = lb_memo.sw.w - 2;
	char *mesg;
	char buf[width * UTF8_MAXLEN];
	int j;

	if (utf8_strwidth(memo->mesg) < width) {
		mesg = memo->mesg;
	} else {
		width -= 3;
		for (j = 0; memo->mesg[j] && width > 0; j++) {
			if (!UTF8_ISCONT(memo->mesg[j]))
				width -= utf8_width(&memo->mesg[j]);
			buf[j] = memo->mesg[j];
		}
		if (j) {
			buf[j - 1] = '.';
			buf[j] = '.';
			buf[j + 1] = '.';
			buf[j + 2] = '\0';
		} else {
			buf[0] = 0;
		}
		mesg = buf;
	}


	mvwprintw(win, y, 0, "%s", mesg);

	*((llist_item_t **)cb_data) = i->next;
}

void ui_memo_load_items(void)
{
	listbox_load_items(&lb_memo, memolist.size);
}

/* Updates the TODO panel. */
void ui_memo_update_panel(int which_pan)
{
	display_view[ui_memo_view]();
}

void ui_memo_win_scrol(int delta)
{
	if ( delta < 0 )
		wins_scrollwin_up(&lb_memo.sw,-delta);
	else
		wins_scrollwin_down(&lb_memo.sw,delta);
	
	wins_doupdate();
}

void display_draft_view(void)
{
	llist_item_t *p = LLIST_FIRST(&memolist);

	listbox_set_cb_data(&lb_memo, &p);

	listbox_display(&lb_memo);
}

void display_abook_view(void)
{

}
