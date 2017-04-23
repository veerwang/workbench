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

enum listbox_row_type ui_ledger_row_type(int i, void *cb_data)
{
	return LISTBOX_ROW_TEXT;
}

int ui_ledger_height(int n, void *cb_data)
{
	return 1;
}

void ui_ledger_draw(int n, WINDOW *win, int y, int hilt, void *cb_data)
{
	llist_item_t *i = *((llist_item_t **)cb_data);
	struct ledger *ledger = LLIST_TS_GET_DATA(i);
	int width = lb_ledger.sw.w - 2;
	char *mesg;
	char buf[width * UTF8_MAXLEN];
	int j;

	if (utf8_strwidth(ledger->mesg) < width) {
		mesg = ledger->mesg;
	} else {
		width -= 3;
		for (j = 0; ledger->mesg[j] && width > 0; j++) {
			if (!UTF8_ISCONT(ledger->mesg[j]))
				width -= utf8_width(&ledger->mesg[j]);
			buf[j] = ledger->mesg[j];
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

void ui_ledger_load_items(void)
{
	listbox_load_items(&lb_ledger, ledgerlist.size);
}

/* Updates the TODO panel. */
void ui_ledger_update_panel(int which_pan)
{
	llist_item_t *p = LLIST_FIRST(&ledgerlist);

	listbox_set_cb_data(&lb_ledger, &p);

	listbox_display(&lb_ledger);
}

void ui_ledger_win_scrol(int delta)
{
	if ( delta < 0 )
		wins_scrollwin_up(&lb_ledger.sw,-delta);
	else
		wins_scrollwin_down(&lb_ledger.sw,delta);
	
	wins_doupdate();
}
