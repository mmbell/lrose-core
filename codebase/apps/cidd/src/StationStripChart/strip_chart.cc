// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
/*************************************************************************
 * STRIP_CHART.c - Produce a strip chart like plot of Mesonet data
 *
 * F. Hage. 9/95 Version 1 (called gauge_strip for WSDDM)
 * N. Oien, M. Dixon.   Convert to TDRP - Modify for Taiwan/AOAWS -
 *   becomes metar_strip
 * F. Hage. Update for WSDDM   - Now StationStripChart
 */

#define STRIP_CHART_MAIN
#include "strip_chart.h"
#undef STRIP_CHART_MAIN

#include "Params.hh"
#include <toolsa/DateTime.hh>
using namespace std;

// prototypes

static void init_xview();
static int  x_error_proc( Display *disp, XErrorEvent *event);
static Notify_value base_win_destroy( Notify_client client,
				      Destroy_status status);
static void init_data_space(void);
static void modify_xview_objects(void);

/********************************************************************
 * MAIN: Process arguments, initialize and begin application
 */
 

int strip_chart_main(int argc, char **argv, Params *params,
		     coord_export_t *coord_shmem)

{
  MEM_zero (gd);

  xv_init(XV_INIT_ARGC_PTR_ARGV,
	  &argc,argv,
	  XV_X_ERROR_PROC, x_error_proc, NULL);

  // global struct

  gd.p = params;
  gd.cidd_mem = coord_shmem;
  
  // initialize globals, get/set defaults, establish data sources etc.
  
  init_data_space();

  // create Xview objects

  init_xview();

  // make changes to xview objects not available from DevGuide

  modify_xview_objects();
  
  // start timer

  start_timer();
  
  // Turn control over to XView.

  xv_main_loop(gd.Strip_chart_win1->win1);

  return 0;

}

/***************************************************************************
 * INIT_XVIEW : Initialize the base frame and other global objects
 */ 
 
static void init_xview()
{
 
  gd.Strip_chart_win1 =
    strip_chart_win1_objects_initialize(NULL, (Xv_opaque) NULL);

  gd.Strip_chart_config_pu =
	strip_chart_config_pu_objects_initialize(NULL, gd.Strip_chart_win1->win1);

  notify_interpose_destroy_func(gd.Strip_chart_win1->win1,
				(Notify_func) base_win_destroy);

  gd.dpy = (Display *) xv_get(gd.Strip_chart_win1->win1,XV_DISPLAY);

}

/*****************************************************************
 * X_ERROR_PROC: Handle errors generated by the X server
 */
 
static int x_error_proc(Display *disp, XErrorEvent *event)
{
  char	text[256];
 
  XGetErrorText(disp,event->error_code,text,256);
  fprintf(stderr,"Generated X error : %s, ID:%d\n", text, 
	  (int) event->resourceid);
 
  switch(event->error_code) {
  default :
    return   XV_OK;
    break;
    
  case BadAlloc :
    return   XV_OK;
    break;
  }

}

/*****************************************************************
 * INIT_DATA_SPACE : Init all globals and set up defaults
 */

static void init_data_space(void)
{

  INSTANCE = xv_unique_key(); /* get keys for retrieving data */

  gd.cur_plot = gd.p->starting_menu_selection;
  if(gd.cur_plot >= gd.p->display_variable_n + gd.p->stations_n) gd.cur_plot = gd.p->display_variable_n + gd.p->stations_n -1;

  if(gd.p->mode == Params::REALTIME){
	  gd.want_live_updates = 1;
  } else {
	  gd.want_live_updates = 0;
  }


  DateTime atime(gd.p->archive_time.year,
		 gd.p->archive_time.month,
		 gd.p->archive_time.day,
		 gd.p->archive_time.hour,
		 gd.p->archive_time.min,
		 gd.p->archive_time.sec);

  gd.archive_time = atime.utime();

  gd.pixels_per_sec = (double) gd.p->window_width / gd.p->plot_period_secs;

  gd.num_sources = gd.p->stations_n;
     
  gd.data_min = 9999999.9;
  gd.data_max = -999999.9;
  
  // Allocate space for each data station (Source) of data 
  gd.sources =
    (source_info_t *) umalloc(gd.num_sources * sizeof(source_info_t));

  // Allocate an array of sourted sources.
  gd.sorted_sources =
    (source_info_t **) umalloc(gd.num_sources * sizeof(source_info_t *));

  for(int i=0 ; i < gd.num_sources; i++) {
    gd.sources[i].station_info = &gd.p->_stations[i];
    gd.sources[i].color_cell = 0;  // Prefered color
    gd.sources[i].num_reports = 0; // total number of reports.

    gd.sources[i].reports = NULL; // Data pointer

    gd.sorted_sources[i] = &(gd.sources[i]); // Originally sorted in order of definition.
  }

  gd.fcat_cells = (int *) umalloc(gd.p->flight_category_n * sizeof(int));

  gd.ready = 1;

}

/*****************************************************************
 * FREE : free up allocated memory
 */

void strip_chart_free()
{

  for(int i=0 ; i < gd.num_sources; i++) {
    if (gd.sources[i].reports) {
      ufree(gd.sources[i].reports);
      gd.sources[i].reports = NULL;
    }
  }
  ufree (gd.sources);
  ufree (gd.fcat_cells);
}

/*****************************************************************
 * BASE_WIN_DESTROY: Interposition for base frame destroys
 */

static Notify_value
base_win_destroy( Notify_client   client, Destroy_status  status)
{

  switch(status) {
  case DESTROY_CLEANUP:
    
  case DESTROY_PROCESS_DEATH:
    PMU_unregister(gd.app_name, gd.p->instance);
    if (gd.cidd_mem != NULL)  {
      ushm_detach(gd.cidd_mem);
      if (ushm_nattach(gd.p->cidd_shmem_key) <= 0) {
	ushm_remove(gd.p->cidd_shmem_key);
      }
    }
    return notify_next_destroy_func(client,status);
    break;
    
  case DESTROY_CHECKING:
    return NOTIFY_DONE;
    break;
    
  case DESTROY_SAVE_YOURSELF:
    return NOTIFY_DONE;
    break;

  }

  return NOTIFY_DONE;

}

/*****************************************************************
 * MODIFY_XVIEW_OBJECTS : Modify any Xview objects that couldn't
 *    be set up in Devguide. This is primarily to avoid manually
 *    changing any *ui.c file
 */

static void modify_xview_objects()
{
  
  int i;
  int orig_size;
  Colormap cmap;
  XColor cell_def;
  XColor rgb_def;
  Menu_item mi;



    Xv_opaque   image1;
    Xv_opaque   image2;

    static unsigned short bbits[] =  {
#include "black.icon"
    };

    static unsigned short wbits[] =  {
#include "white.icon"
    };

    image1 = xv_create(XV_NULL, SERVER_IMAGE,
      SERVER_IMAGE_DEPTH, 1,
      SERVER_IMAGE_BITS, bbits,
      XV_WIDTH, 64,
      XV_HEIGHT, 64,
      NULL);

    image2 = xv_create(XV_NULL, SERVER_IMAGE,
      SERVER_IMAGE_DEPTH, 1,
      SERVER_IMAGE_BITS, wbits,
      XV_WIDTH, 64,
      XV_HEIGHT, 64,
      NULL);

  Menu menu = (Menu)
    xv_get(canvas_paint_window(gd.Strip_chart_win1->canvas1), WIN_MENU);

  orig_size = xv_get(gd.Strip_chart_config_pu->field_st,XV_WIDTH);
  
  xv_set(gd.Strip_chart_win1->win1,
         WIN_HEIGHT,gd.p->window_height,
         WIN_WIDTH,gd.p->window_width,
         FRAME_ICON, xv_create(XV_NULL, ICON,
                               ICON_IMAGE,image1,
                               ICON_HEIGHT, 1,
                               ICON_WIDTH, 64,
                               NULL),
	 NULL);
  
  if(gd.p->show_window == false) {
    xv_set(gd.Strip_chart_win1->win1,XV_SHOW,FALSE,NULL);
  }
	  
  gd.win_height =  xv_get(gd.Strip_chart_win1->win1,WIN_HEIGHT);
  gd.win_width =  xv_get(gd.Strip_chart_win1->win1,WIN_WIDTH);
  gd.plot_height = gd.win_height - gd.p->bottom_margin;
  gd.plot_width = gd.win_width -  gd.p->right_margin;
  
  gd.canvas_xid =
    xv_get(canvas_paint_window(gd.Strip_chart_win1->canvas1),XV_XID);

  gd.back_xid =  XCreatePixmap(gd.dpy, gd.canvas_xid,
			       gd.win_width, gd.win_height,
			       DefaultDepth(gd.dpy,0));

  cmap = DefaultColormap(gd.dpy,DefaultScreen(gd.dpy));
  gd.def_gc = DefaultGC(gd.dpy, DefaultScreen(gd.dpy));

  XAllocNamedColor(gd.dpy,cmap, gd.p->foreground_color, &cell_def,&rgb_def);
  gd.fg_cell = cell_def.pixel;

  XAllocNamedColor(gd.dpy,cmap, gd.p->background_color, &cell_def,&rgb_def);
  gd.bg_cell = cell_def.pixel;

  XAllocNamedColor(gd.dpy,cmap, gd.p->now_color, &cell_def,&rgb_def);
  gd.now_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->frost_color, &cell_def,&rgb_def);
  gd.frost_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->no_fzra_color, &cell_def,&rgb_def);
  gd.no_fzra_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->fzfg_color, &cell_def,&rgb_def);
  gd.fzfg_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->lt_fzdz_color, &cell_def,&rgb_def);
  gd.lt_fzdz_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->fzdz_color, &cell_def,&rgb_def);
  gd.fzdz_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->hv_fzdz_color, &cell_def,&rgb_def);
  gd.hv_fzdz_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->lt_fzra_color, &cell_def,&rgb_def);
  gd.lt_fzra_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->fzra_color, &cell_def,&rgb_def);
  gd.fzra_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->hv_fzra_color, &cell_def,&rgb_def);
  gd.hv_fzra_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->dz_color, &cell_def,&rgb_def);
  gd.dz_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->lt_ra_color, &cell_def,&rgb_def);
  gd.lt_ra_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->ra_color, &cell_def,&rgb_def);
  gd.ra_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->hv_ra_color, &cell_def,&rgb_def);
  gd.hv_ra_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->lt_sn_color, &cell_def,&rgb_def);
  gd.lt_sn_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->sn_color, &cell_def,&rgb_def);
  gd.sn_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->hv_sn_color, &cell_def,&rgb_def);
  gd.hv_sn_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->pe_color, &cell_def,&rgb_def);
  gd.pe_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->ts_color, &cell_def,&rgb_def);
  gd.ts_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->hz_color, &cell_def,&rgb_def);
  gd.hz_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->up_color, &cell_def,&rgb_def);
  gd.up_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->fg_color, &cell_def,&rgb_def);
  gd.fog_cell = cell_def.pixel;
  
  XAllocNamedColor(gd.dpy,cmap, gd.p->hv_fzra_color, &cell_def,&rgb_def);
  gd.hv_fzra_cell = cell_def.pixel;
  
  //Fill in the menu and Set labels on config panel.
  gd.num_active_fields = 0;
  for(i=0; i < gd.p->display_variable_n; i++) {
    mi = (Menu_item) xv_create(XV_NULL,MENUITEM,
			       MENU_STRING, gd.p->_display_variable[i].label_str,
	                       XV_KEY_DATA,    MENU_KEY, i,
			       NULL);

    xv_set(menu,MENU_APPEND_ITEM,mi, NULL);

    gd.field_lookup[i] = gd.p->_display_variable[i].field;

    gd.field_active[gd.p->_display_variable[i].field] = 1;

	 xv_set(gd.Strip_chart_config_pu->field_st,
		   PANEL_CHOICE_STRING,gd.p->_display_variable[i].field,
		   gd.p->_display_variable[i].label_str,NULL);
	
	gd.num_active_fields++;
  }

  int new_size = xv_get(gd.Strip_chart_config_pu->field_st,XV_WIDTH);
  if( new_size > orig_size) {
	   xv_set(gd.Strip_chart_config_pu->config_pu,XV_WIDTH,new_size,NULL);
  }

  for(i=0; i < gd.num_sources; i++) {
    XAllocNamedColor(gd.dpy,cmap, gd.p->_stations[i].color,
		     &cell_def,&rgb_def);
    gd.sources[i].color_cell = cell_def.pixel;
    mi = (Menu_item)
      xv_create(XV_NULL,MENUITEM,MENU_STRING,
		gd.p->_stations[i].menu_name,
	        XV_KEY_DATA,    MENU_KEY, i + gd.num_active_fields,
		NULL);

    xv_set(menu,MENU_APPEND_ITEM,mi,NULL);
  }

  // colors for flight cat
  
  for (i = 0; i < gd.p->flight_category_n; i++) {
    XAllocNamedColor(gd.dpy, cmap, gd.p->_flight_category[i].color,
		     &cell_def, &rgb_def);
    gd.fcat_cells[i] = cell_def.pixel;
  }
  
  gd.fontst = (XFontStruct *) XLoadQueryFont(gd.dpy, gd.p->font_name);
  if(gd.fontst == NULL) {
    fprintf(stderr,"Can't load font %s\n", gd.p->font_name);
    exit(-1);
  }
  gd.font  = gd.fontst->fid;
  XSetFont(gd.dpy, gd.def_gc, gd.font);

  xv_set(gd.Strip_chart_win1->canvas1, XV_HELP_DATA,
	 "strip_chart:canvas",NULL);

  set_frame_label();

  gd.new_data = true;

  check_retrieve();

}

/*****************************************************************
 * BUILD_FIELD_MENU : 
 */

void build_field_menu(void)
{

  int i,j;
  int found;
  int orig_active;
  char *label = NULL;
  Menu_item mi;

  Menu menu = (Menu)
    xv_get(canvas_paint_window(gd.Strip_chart_win1->canvas1), WIN_MENU);

  orig_active = gd.num_active_fields;

  // Remove old menu items.
  for(i= xv_get(menu,MENU_NITEMS) ; i > 0; i--) {
	  xv_set(menu,MENU_REMOVE,i,NULL);
	  xv_destroy(xv_get(menu,MENU_NTH_ITEM,i));
  }

  //Fill in the menu in the order of the config file
  gd.num_active_fields = 0;

  for (i=0; i < gd.p->display_variable_n; i++) {
	// if This field is active
	if(gd.field_active[gd.p->_display_variable[i].field]) {

	 // Add it to the menu
     mi = (Menu_item) xv_create(XV_NULL,MENUITEM,
			       MENU_STRING, gd.p->_display_variable[i].label_str,
	                       XV_KEY_DATA,    MENU_KEY, gd.num_active_fields,
			       NULL);

     xv_set(menu,MENU_APPEND_ITEM,mi, NULL);

     gd.field_lookup[gd.num_active_fields] = gd.p->_display_variable[i].field;

	 gd.num_active_fields++;
	}
  }

  // Make sure active fields not in the config file are in the menu

  for(i=0; i < MAX_FIELDS; i++ ) {
    if(gd.field_active[i]) {
	  for(j=0, found = 0; j < gd.num_active_fields && found == 0; j++) {
		  if(gd.field_lookup[j] == i) found = 1;
	  }

	  if(!found) {
		  switch(i) {
			  case Params::RATE:
				  label = "Precip Rate";
				  found = 1;
			  break;

			  case Params::ACCUMULATION:
				  label = "Precip Accum";
				  found = 1;
			  break;

			  case Params::CEILING:
				  label = "Ceiling";
				  found = 1;
			  break;

			  case Params::VISIBILITY:
				  label = "Visibility";
				  found = 1;
			  break;

			  case Params::FLIGHT_CAT:
				  label = "Flight Cat.";
				  found = 1;
			  break;

			  case Params::TEMPERATURE:
				  label = "Temperature";
				  found = 1;
			  break;

			  case Params::DEWPT:
				  label = "Dew Point";
				  found = 1;
			  break;

			  case Params::HUMIDITY:
				  label = "Humidity";
				  found = 1;
			  break;

			  case Params::WIND_SPEED:
				  label = "Wind Speed";
				  found = 1;
			  break;

			  case Params::WIND_DIRN:
				  label = "Wind Direction";
				  found = 1;
			  break;

			  case Params::PRESSURE:
				  label = "barometer";
				  found = 1;
			  break;

			  case Params::ACCUMULATION2:
				  label = "Precip Alternate";
				  found = 1;
			  break;

			  case Params::SPARE1:
				  label = "Spare1";
				  found = 1;
			  break;

			  case Params::SPARE2:
				  label = "Spare2";
				  found = 1;
			  break;

			  case Params::FZ_PRECIP:
				  label = "Freezing Precip";
				  found = 1;
			  break;

			  case Params::PRECIP_TYPE:
				  label = "Precip Type";
				  found = 1;
			  break;

		  }

          if(found ) {
			  mi = (Menu_item) xv_create(XV_NULL,MENUITEM,
			       MENU_STRING, label,
	                       XV_KEY_DATA,    MENU_KEY, gd.num_active_fields,
			       NULL);

             xv_set(menu,MENU_APPEND_ITEM,mi, NULL);

             gd.field_lookup[gd.num_active_fields] = i;

	         gd.num_active_fields++;
		  }
	  }
	}
  }

  // Now add the Stations to the Menu
  for(i=0; i < gd.num_sources; i++) {
    mi = (Menu_item)
      xv_create(XV_NULL,MENUITEM,MENU_STRING,
		gd.p->_stations[i].menu_name,
	        XV_KEY_DATA,    MENU_KEY, i + gd.num_active_fields,
		NULL);

    xv_set(menu,MENU_APPEND_ITEM,mi,NULL);
  }

  if(gd.cur_plot >= orig_active) { // Was a station plot
	 gd.cur_plot += (gd.num_active_fields - orig_active);

  } else {
	 gd.cur_plot = 0;
	 for(i=0; i < gd.num_active_fields; i++) {
	      if(gd.field_lookup[i] == gd.variable);
		  gd.cur_plot = i;
	 }
  }

  draw_plot();
}

/*****************************************************************
 * SET_FRAME_LABEL : 
 */

void set_frame_label(void)
{

  xv_set(gd.Strip_chart_win1->win1, FRAME_LABEL,
	 gd.p->window_label, NULL);
}
  
/*****************************************************************
 * UPDATE_CONFIG_POPUP: 
 */

void update_config_popup()
{
  int i;
  char buf[128];
  struct tm res;

  //Fill in the menu

  unsigned int bits = 0;
  for(i=0; i < MAX_FIELDS; i++) {
	if(gd.field_active[i]) {
	  bits |= ( 1 << i);
	}
  }

  xv_set(gd.Strip_chart_config_pu->field_st,
		 PANEL_VALUE,bits,NULL);

  sprintf(buf,"%d",gd.p->trace_line_width);
  xv_set(gd.Strip_chart_config_pu->trace_width_tx,
		 PANEL_VALUE,buf , NULL);

  sprintf(buf,"%d",gd.p->update_interval_min);
  xv_set(gd.Strip_chart_config_pu->update_interval_tx,
		 PANEL_VALUE,buf, NULL);

  sprintf(buf,"%d",gd.p->seconds_delay);
  xv_set(gd.Strip_chart_config_pu->delay_tx,
		 PANEL_VALUE,buf, NULL);

  if(gd.p->keep_period_fixed) {
    sprintf(buf,"%.2f",(gd.p->plot_period_secs /3600.0));
    xv_set(gd.Strip_chart_config_pu->scale_tx,
  		PANEL_VALUE,buf ,
		PANEL_LABEL_STRING, "Plot Period (hrs):", NULL);
  } else {
    sprintf(buf,"%.1f",(1.0 / gd.pixels_per_sec));
    xv_set(gd.Strip_chart_config_pu->scale_tx,
  		PANEL_VALUE,buf ,
		PANEL_LABEL_STRING, "Seconds Per Pixel:", NULL);
  }

  xv_set(gd.Strip_chart_config_pu->run_mode_st,
		 PANEL_VALUE,gd.p->mode , NULL);

  xv_set(gd.Strip_chart_config_pu->zone_st,
		 PANEL_VALUE,gd.p->use_localtime , NULL);

  xv_set(gd.Strip_chart_config_pu->units_st,
		 PANEL_VALUE,gd.p->units , NULL);

  xv_set(gd.Strip_chart_config_pu->url_tx,
		 PANEL_VALUE,gd.p->input_url , NULL);

  if(gd.p->use_localtime) {
      strftime(buf,128,"%Y %m %d %H %M %S %Z", localtime_r(&gd.end_time,&res));
  } else {
      strftime(buf,128,"%Y %m %d %H %M %S UTC", gmtime_r(&gd.end_time,&res));
  }
  xv_set(gd.Strip_chart_config_pu->archive_time_tx,
		 PANEL_VALUE,buf , NULL);

}
