/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
/* ** Copyright UCAR (c) 1990 - 2016                                         */
/* ** University Corporation for Atmospheric Research (UCAR)                 */
/* ** National Center for Atmospheric Research (NCAR)                        */
/* ** Boulder, Colorado, USA                                                 */
/* ** BSD licence applies - redistribution and use in source and binary      */
/* ** forms, with or without modification, are permitted provided that       */
/* ** the following conditions are met:                                      */
/* ** 1) If the software is modified to produce derivative works,            */
/* ** such modified software should be clearly marked, so as not             */
/* ** to confuse it with the version available from UCAR.                    */
/* ** 2) Redistributions of source code must retain the above copyright      */
/* ** notice, this list of conditions and the following disclaimer.          */
/* ** 3) Redistributions in binary form must reproduce the above copyright   */
/* ** notice, this list of conditions and the following disclaimer in the    */
/* ** documentation and/or other materials provided with the distribution.   */
/* ** 4) Neither the name of UCAR nor the names of its contributors,         */
/* ** if any, may be used to endorse or promote products derived from        */
/* ** this software without specific prior written permission.               */
/* ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  */
/* ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      */
/* ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    */
/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
/*
 * linear_stubs.c - Notify and event callback function stubs.
 * This file was generated by `gxv' from `linear.G'.
 */

#include "cscale_edit.h"



/*
 * Done callback function for `popup1'.
 */
void
linear_done(frame)
	Frame		frame;
{
  
  xv_set(frame, XV_SHOW, FALSE, NULL);
  
	/* gxv_start_connections DO NOT EDIT THIS SECTION */

	/* gxv_end_connections */

} /* end linear_done */



/*
 * Event callback function for `linear_min'.
 */
void
lin_min_events(item, event)
	Panel_item	item;
	Event		*event;
{
  linear_popup1_objects *ip = (linear_popup1_objects *)
    xv_get(item, XV_KEY_DATA, INSTANCE);
  char *value = (char *)xv_get(item, PANEL_VALUE);
  char *endptr;

  Lin_min = strtod(value, &endptr);
  
	/* gxv_start_connections DO NOT EDIT THIS SECTION */

	/* gxv_end_connections */

  panel_default_handle_event(item, event);

} /* end lin_min_events */



/*
 * Notify callback function for `fields'.
 */
Panel_setting
lin_field_notify(item, event)
	Panel_item	item;
	Event		*event;
{
  linear_popup1_objects *ip = (linear_popup1_objects *)
    xv_get(item, XV_KEY_DATA, INSTANCE);
  int	value = (int) xv_get(item, PANEL_VALUE);

  Lin_fields = (double)value;

	/* gxv_start_connections DO NOT EDIT THIS SECTION */

	/* gxv_end_connections */

  return panel_text_notify(item, event);

} /* end lin_field_notify */



/*
 * Event callback function for `delta'.
 */
void
lin_delta_events(item, event)
	Panel_item	item;
	Event		*event;
{
  linear_popup1_objects *ip = (linear_popup1_objects *)
    xv_get(item, XV_KEY_DATA, INSTANCE);
  char *value = (char *)xv_get(item, PANEL_VALUE);
  char *endptr;

  Lin_delta = strtod(value, &endptr);
  
	/* gxv_start_connections DO NOT EDIT THIS SECTION */

	/* gxv_end_connections */

  panel_default_handle_event(item, event);

} /* end lin_delta_events */



/*
 * Notify callback function for `apply_button'.
 */
void
apply_button(item, event)
	Panel_item	item;
	Event		*event;
{
  linear_popup1_objects *ip = (linear_popup1_objects *)
    xv_get(item, XV_KEY_DATA, INSTANCE);
  int i;
  double min;
  
  Num_fields = (int)Lin_fields;
  xv_set(Cscale_edit_window1->fields, PANEL_VALUE, Num_fields, NULL);
  xv_set(Cscale_edit_window1->status_message, PANEL_LABEL_STRING,
         "Status:", NULL);
  min = Lin_min;
  
  for (i = Num_fields; i > 0; i--)
    {
    Color_struct[i-1].min_val = min;
    Color_struct[i-1].max_val = min + Lin_delta;
    min += Lin_delta;
  } /* for i = Num_fields to 0 */
  
  colorize_can2();
  can2_draw_text();
  can2_draw_rect();
    
	/* gxv_start_connections DO NOT EDIT THIS SECTION */

	/* gxv_end_connections */

} /* end apply_button */



/*
 * Notify callback function for `linear_arbitrary'.
 */
void
lin_arb_proc(item, value, event)
	Panel_item	item;
	int		value;
	Event		*event;
{
  char string[32];
  linear_popup1_objects *ip = (linear_popup1_objects *)
    xv_get(item, XV_KEY_DATA, INSTANCE);

  Lin_arb_format = value;

  xv_set(Cscale_edit_window1->status_message, PANEL_LABEL_STRING,
         "Status:", NULL);

  if (Lin_arb_format == 1)
    {
    /* gray out min and delta fields and deactivate apply button */
    /* and activate color_scale_min field */
    xv_set(Linear_popup1->linear_min, PANEL_INACTIVE, TRUE, NULL);
    xv_set(Linear_popup1->delta, PANEL_INACTIVE, TRUE, NULL);
    xv_set(Linear_popup1->apply_button, PANEL_INACTIVE, TRUE, NULL);
    xv_set(Linear_popup1->fields, PANEL_INACTIVE, TRUE, NULL);
    xv_set(Linear_popup1->color_scale_min, PANEL_INACTIVE, FALSE, NULL);
    Field = Num_fields;
    colorize_can2();
    can2_draw_text();
    can2_draw_rect();
    highlight_field();
    xv_set(Linear_popup1->color_scale_min, PANEL_LABEL_STRING,
           "Color Value 1 Min:", NULL);
    xv_set(Linear_popup1->color_scale_max, PANEL_LABEL_STRING,
           "Color Value   Max:", NULL);
    Cvalue = 1;
    sprintf(string, "%lg", Color_struct[Field-1].min_val);
    xv_set(Linear_popup1->color_scale_min, PANEL_VALUE, string, NULL);
    xv_set(Linear_popup1->controls1, PANEL_CARET_ITEM,
           Linear_popup1->color_scale_min, NULL);
  } /* end Lin_arb_format == 1 */
  else
    { /* gray out color_scale_max and color_scale_min fields */
      /* and activate the min and delta fields and the apply_button */
    xv_set(Linear_popup1->linear_min, PANEL_INACTIVE, FALSE, NULL);
    xv_set(Linear_popup1->delta, PANEL_INACTIVE, FALSE, NULL);
    xv_set(Linear_popup1->apply_button, PANEL_INACTIVE, FALSE, NULL);
    xv_set(Linear_popup1->fields, PANEL_INACTIVE, FALSE, NULL);
    xv_set(Linear_popup1->color_scale_min, PANEL_INACTIVE, TRUE, NULL);
    xv_set(Linear_popup1->color_scale_max, PANEL_INACTIVE, TRUE, NULL);
    xv_set(Linear_popup1->controls1, PANEL_CARET_ITEM, 
           Linear_popup1->linear_min, NULL);
  } /* end else if Lin_arb_format == 0 */
 
	/* gxv_start_connections DO NOT EDIT THIS SECTION */

	/* gxv_end_connections */

} /* end lin_arb_proc */



/*
 * Notify callback function for `color_scale_min'.
 */
Panel_setting
cscale_min_proc(item, event)
	Panel_item	item;
	Event		*event;
{
  char *endptr;
  char string[32];
  linear_popup1_objects *ip = (linear_popup1_objects *)
    xv_get(item, XV_KEY_DATA, INSTANCE);
  char *value = (char *)xv_get(item, PANEL_VALUE);
  
  Cscale_min = strtod(value, &endptr);
  
  if (Field == Num_fields && Num_fields != 1)
    {
    Color_struct[Field-1].min_val = Cscale_min;
    Field -= 1;
    colorize_can2();
    can2_draw_text();
    can2_draw_rect();
    highlight_field();
    Cvalue++;
    sprintf(string, "Color Value %d Min:", Cvalue);
    xv_set(Linear_popup1->color_scale_min, PANEL_LABEL_STRING, string, NULL);
    sprintf(string, "%lg", Color_struct[Field-1].min_val);
    xv_set(Linear_popup1->color_scale_min, PANEL_VALUE, string, NULL);
  } /* end if Field == Num_fields */
  else if (Field != 1)
    {
    Color_struct[Field-1].min_val = Cscale_min;
    Color_struct[Field].max_val = Cscale_min;
    Field -= 1;
    colorize_can2();
    can2_draw_text();
    can2_draw_rect();
    highlight_field();
    Cvalue++;
    sprintf(string, "Color Value %d Min:", Cvalue);
    xv_set(Linear_popup1->color_scale_min, PANEL_LABEL_STRING, string, NULL);
    sprintf(string, "%lg", Color_struct[Field-1].min_val);
    xv_set(Linear_popup1->color_scale_min, PANEL_VALUE, string, NULL);
  } /* end else if Field != 1 */
  else
    {
    Color_struct[Field-1].min_val = Cscale_min;
    if (Num_fields != 1)
      Color_struct[Field].max_val = Cscale_min;
    xv_set(Linear_popup1->color_scale_max, PANEL_INACTIVE, FALSE, NULL);
    sprintf(string, "Color Value %d Min:", Cvalue);
    xv_set(Linear_popup1->color_scale_min, PANEL_LABEL_STRING, string, NULL);
    sprintf(string, "%lg", Color_struct[Field-1].max_val);
    xv_set(Linear_popup1->color_scale_max, PANEL_VALUE, string, NULL);
    sprintf(string, "Color Value %d Max:", Cvalue);
    xv_set(Linear_popup1->color_scale_max, PANEL_LABEL_STRING, string, NULL);
    return panel_text_notify(item, event);
  } /* end else Field == 1 */

	/* gxv_start_connections DO NOT EDIT THIS SECTION */

	/* gxv_end_connections */

} /* end cscale_min_proc */



/*
 * Notify callback function for `color_scale_max'.
 */
Panel_setting
cscale_max_proc(item, event)
	Panel_item	item;
	Event		*event;
{
  linear_popup1_objects *ip = (linear_popup1_objects *)
    xv_get(item, XV_KEY_DATA, INSTANCE);
  char *value = (char *)xv_get(item, PANEL_VALUE);
  char *endptr;
  char string[32];
   
  Cscale_max = strtod(value, &endptr);

  Color_struct[Field-1].max_val = Cscale_max;
  Field = Num_fields;
  colorize_can2();
  can2_draw_text();
  can2_draw_rect();
  highlight_field();
  sprintf(string, "%lg", Color_struct[Field-1].min_val);
  xv_set(Linear_popup1->color_scale_min, PANEL_VALUE, string, NULL);
  xv_set(Linear_popup1->color_scale_min, PANEL_LABEL_STRING, 
         "Color Value 1 Min:", NULL);
  xv_set(Linear_popup1->color_scale_max, PANEL_LABEL_STRING,
         "Color Value   Max:", NULL);
  Cvalue = 1;
  xv_set(Linear_popup1->color_scale_max, PANEL_INACTIVE, TRUE, NULL);
  
	/* gxv_start_connections DO NOT EDIT THIS SECTION */

	/* gxv_end_connections */

  return panel_text_notify(item, event);

} /* end cscale_max_proc */