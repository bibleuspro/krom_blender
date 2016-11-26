/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2008 Blender Foundation.
 * All rights reserved.
 *
 * ***** END GPL LICENSE BLOCK *****
 */
 
/** \file blender/editors/space_armory/space_armory.c
 *  \ingroup sparmory
 */
 
#include <string.h>
 
#include "DNA_text_types.h"
 
#include "MEM_guardedalloc.h"
 
#include "BLI_blenlib.h"
 
#include "BKE_context.h"
#include "BKE_screen.h"
 
#include "ED_space_api.h"
#include "ED_screen.h"
 
#include "BIF_gl.h"
 
#include "WM_api.h"
#include "WM_types.h"
 
#include "UI_interface.h"
#include "UI_resources.h"
#include "UI_view2d.h"

#include "ArmoryWrapper.h"
 
static SpaceLink *armory_new(const bContext *C)
{	
	ScrArea *sa = CTX_wm_area(C);
	ARegion *ar;
	SpaceArmory *sarmory;
 
	sarmory = MEM_callocN(sizeof(SpaceArmory), "initarmory");
	sarmory->spacetype = SPACE_ARMORY;
 
	/* header */
	ar = MEM_callocN(sizeof(ARegion), "header for armory");
 
	BLI_addtail(&sarmory->regionbase, ar);
	ar->regiontype = RGN_TYPE_HEADER;
	ar->alignment = RGN_ALIGN_BOTTOM;
 
	/* main area */
	ar = MEM_callocN(sizeof(ARegion), "main area for armory");
 
	BLI_addtail(&sarmory->regionbase, ar);
	ar->regiontype = RGN_TYPE_WINDOW;

	return (SpaceLink *)sarmory;
}

bool keystate[512];
/* add handlers, stuff you only do once or on area/region changes */
static void armory_main_area_init(wmWindowManager *wm, ARegion *ar)
{	
	UI_view2d_region_reinit(&ar->v2d, V2D_COMMONVIEW_CUSTOM, ar->winx, ar->winy);
    
	int x = ar->winrct.xmin;
	int y = ar->winrct.ymin;
	int w = ar->winrct.xmax - ar->winrct.xmin;
	int h = ar->winrct.ymax - ar->winrct.ymin;

	if (!armoryStarted()) {
		for (int i = 0; i < 512; i++) keystate[i] = false;
		armoryShow(x, y, w, h);
	}
	else armoryUpdatePosition(x, y, w, h);
}

static void armory_main_area_exit(wmWindowManager *wm, ARegion *ar)
{
	armoryExit();
}

static void armory_main_area_free(ARegion *ar)
{
	armoryFree();
}

void armory_GPU_buffers_unbind(void)
{
	// TODO
	//int i;
	// if (GLStates & GPU_BUFFER_VERTEX_STATE)
		glDisableClientState(GL_VERTEX_ARRAY);
	// if (GLStates & GPU_BUFFER_NORMAL_STATE)
		glDisableClientState(GL_NORMAL_ARRAY);
	// if (GLStates & GPU_BUFFER_TEXCOORD_UNIT_0_STATE)
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	// if (GLStates & GPU_BUFFER_TEXCOORD_UNIT_2_STATE) {
		glClientActiveTexture(GL_TEXTURE2);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glClientActiveTexture(GL_TEXTURE0);
	// }
	// if (GLStates & GPU_BUFFER_COLOR_STATE)
		glDisableClientState(GL_COLOR_ARRAY);
	// if (GLStates & GPU_BUFFER_ELEMENT_STATE)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// GLStates &= ~(GPU_BUFFER_VERTEX_STATE | GPU_BUFFER_NORMAL_STATE |
	              // GPU_BUFFER_TEXCOORD_UNIT_0_STATE | GPU_BUFFER_TEXCOORD_UNIT_2_STATE |
	              // GPU_BUFFER_COLOR_STATE | GPU_BUFFER_ELEMENT_STATE);

	// for (i = 0; i < MAX_GPU_ATTRIB_DATA; i++) {
		// if (attribData[i].index != -1) {
			// glDisableVertexAttribArray(attribData[i].index);
		// }
		// else
			// break;
	// }
	// attribData[0].index = -1;

	glUseProgram(0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

#ifndef SYS_OSX // Blender limited to opengl 2.1 on macos
	glBindVertexArray(0);
#endif
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
	glDisableVertexAttribArray(7);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



int lastmx = -1, lastmy = -1;
int pressed = 0;

static void handleEvent(int mx, int my, int etype, int eval, bool prev) {

	// Fix handling multiple events at once
	if (!prev) {
	    if (etype == LEFTMOUSE || etype == RIGHTMOUSE) {
			int button = etype == LEFTMOUSE ? 0 : 1;
			if (eval == KM_PRESS && pressed == 0) {
				pressed = 1;
				armoryMousePress(button, mx, my);	
			}
			else if (eval == KM_RELEASE && pressed == 1) {
				pressed = 0;
				armoryMouseRelease(button, mx, my);
			}
		}
		if (mx != lastmx || my != lastmy) {
			armoryMouseMove(mx, my);
		}
	}
	
	// wm_event_types.h
	if ((etype >= LEFTARROWKEY && etype <= UPARROWKEY) ||
		(etype >= AKEY && etype <= ZKEY) ||
		(etype >= ZEROKEY && etype <= NINEKEY) ||
		(etype == LEFTSHIFTKEY || etype == ESCKEY)) {

		if (eval == KM_PRESS && keystate[etype] == false) {
			keystate[etype] = true;
			armoryKeyDown(etype);
		}
		else if (eval == KM_RELEASE && keystate[etype] == true) {
			keystate[etype] = false;
			armoryKeyUp(etype);
		}
	}
}

int lasteval = -1;
int lastetype = -1;

static void armory_main_area_draw(const bContext *C, ARegion *ar)
{
	glPushAttrib(GL_TEXTURE_BIT | GL_DEPTH_BUFFER_BIT); // Fix drawBuffers & viewport depth
	// | GL_VIEWPORT_BIT | GL_SCISSOR_BIT
	armoryDraw();
	glPopAttrib();
	armory_GPU_buffers_unbind();

	int x = ar->winrct.xmin;
	int xmax = ar->winrct.xmax;
	int y = ar->winrct.ymin;
	int ymax = ar->winrct.ymax;
	int w = ar->winrct.xmax - ar->winrct.xmin;
	int h = ar->winrct.ymax - ar->winrct.ymin;

	wmWindow *win = CTX_wm_window(C);
	wmEvent* event = win->eventstate;

	int mx = event->x - x;
	int my = ymax - event->y;

	// Mouse in bounds
	if (event->x >= x && event->x <= xmax && event->y >= y && event->y <= ymax) {
        
        // Prev event unhandled, > 2 events per frame still get unhandled
		if (lastetype != -1 && lasteval != -1) {
			if (event->prevtype != lastetype || event->prevval != lasteval) {
				handleEvent(mx, my, event->prevtype, event->prevval, true);
			}
		}

		handleEvent(mx, my, event->type, event->val, false);
	}

	lastetype = event->type;
	lasteval = event->val;

	lastmx = mx;
	lastmy = my;
}
 
static void armory_header_area_init(wmWindowManager *UNUSED(wm), ARegion *ar)
{
	ED_region_header_init(ar);
}
 
static void armory_header_area_draw(const bContext *C, ARegion *ar)
{
	ED_region_header(C, ar);
}
 
/********************* registration ********************/
 
/* only called once, from space/spacetypes.c */
void ED_spacetype_armory(void)
{
	armoryNew();

	SpaceType *st = MEM_callocN(sizeof(SpaceType), "spacetype armory");
	ARegionType *art;
 
	st->spaceid = SPACE_ARMORY;
	strncpy(st->name, "Armory", BKE_ST_MAXNAME);
 
	st->new = armory_new;
 
	/* regions: main window */
	art = MEM_callocN(sizeof(ARegionType), "spacetype armory region");
	art->regionid = RGN_TYPE_WINDOW;
 
	art->init = armory_main_area_init;
	art->exit = armory_main_area_exit;
	art->draw = armory_main_area_draw;
	art->free = armory_main_area_free;
 
	BLI_addhead(&st->regiontypes, art);
 
	/* regions: header */
	art = MEM_callocN(sizeof(ARegionType), "spacetype armory region");
	art->regionid = RGN_TYPE_HEADER;
	art->prefsizey = HEADERY;
	art->keymapflag = ED_KEYMAP_UI | ED_KEYMAP_VIEW2D | ED_KEYMAP_HEADER;
	art->init = armory_header_area_init;
	art->draw = armory_header_area_draw;
 
	BLI_addhead(&st->regiontypes, art);
 
	BKE_spacetype_register(st);
}
