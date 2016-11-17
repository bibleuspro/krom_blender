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

bool keystate[256];
bool browser_initialized = false;
/* add handlers, stuff you only do once or on area/region changes */
static void armory_main_area_init(wmWindowManager *wm, ARegion *ar)
{	
	int i;
	for (i = 0; i < 256; i++) keystate[i] = false;

	UI_view2d_region_reinit(&ar->v2d, V2D_COMMONVIEW_CUSTOM, ar->winx, ar->winy);

	bool browser_running = armoryStarted();
    
	int x = ar->winrct.xmin;
	int y = ar->winrct.ymin;
	int w = ar->winrct.xmax - ar->winrct.xmin;
	int h = ar->winrct.ymax - ar->winrct.ymin;

	/* Start new browser instance */
	if (!browser_running) {
		if (!browser_initialized) {
			armoryInit();
			browser_initialized = true;
		}
		armoryShow(x, y, w, h);
	}
	else {
		armoryUpdatePosition(x, y, w, h);
	}
}

static void armory_main_area_exit(wmWindowManager *wm, ARegion *ar)
{
	armoryExit();
}

static void armory_main_area_free(ARegion *ar)
{
	armoryFree();
}

int lastmx = -1, lastmy = -1;
int pressed = 0;
static void armory_main_area_draw(const bContext *C, ARegion *ar)
{
	/* draw entirely, view changes should be handled here */
	// SpaceArmory *sarmory = CTX_wm_space_armory(C);
	// View2D *v2d = &ar->v2d;
	// View2DScrollers *scrollers;
 
	// /* clear and setup matrix */
	// UI_ThemeClearColor(TH_BACK);
	// glClearColor(1.0, 0.0, 0.0, 1.0);
	// glClear(GL_COLOR_BUFFER_BIT);
 
	// /* works best with no view2d matrix set */
	// UI_view2d_view_ortho(v2d);
 
	// /* reset view matrix */
	// UI_view2d_view_restore(C);
 
	// /* scrollers */
	// scrollers = UI_view2d_scrollers_calc(C, v2d, V2D_ARG_DUMMY, V2D_ARG_DUMMY, V2D_ARG_DUMMY, V2D_GRID_CLAMP);
	// UI_view2d_scrollers_draw(C, v2d, scrollers);
	// UI_view2d_scrollers_free(scrollers);





	armoryDraw();

	glUseProgram(0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);




	int x = ar->winrct.xmin;
	int y = ar->winrct.ymin;
	int w = ar->winrct.xmax - ar->winrct.xmin;
	int h = ar->winrct.ymax - ar->winrct.ymin;

	wmWindow *win = CTX_wm_window(C);
	wmEvent* event = win->eventstate;

	int mx = event->x;
	int my = h - event->y;

	if (mx != lastmx || my != lastmy) {
		armoryMouseMove(mx, my);
	}
	else if (event->type == LEFTMOUSE) {
		if (event->val == KM_PRESS && pressed == 0) {
			pressed = 1;
			armoryMousePress(mx, my);	
		}
		else if (event->val == KM_RELEASE && pressed == 1) {
			pressed = 0;
			armoryMouseRelease(mx, my);
		}
	}
	
	if (event->type >= LEFTARROWKEY && event->type <= UPARROWKEY) {
		if (event->val == KM_PRESS && keystate[event->type] == false) {
			keystate[event->type] = true;
			armoryKeyDown(event->type);
		}
		else if (event->val == KM_RELEASE && keystate[event->type] == true) {
			keystate[event->type] = false;
			armoryKeyUp(event->type);
		}
	}


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
