#ifndef	regis_tool_HEADER
#define	regis_tool_HEADER

/*
 * regis_tool_ui.h - User interface object and function declarations.
 * This file was generated by `gxv' from `regis_tool.G'.
 * DO NOT EDIT BY HAND.
 */

extern Attr_attribute	INSTANCE;


typedef struct {
	Xv_opaque	win1;
	Xv_opaque	controls1;
	Xv_opaque	start_bt;
	Xv_opaque	comp_bt;
	Xv_opaque	status_msg;
	Xv_opaque	each_pt_msg;
	Xv_opaque	avg_msg;
} regis_tool_win1_objects;

extern regis_tool_win1_objects	*regis_tool_win1_objects_initialize();

extern Xv_opaque	regis_tool_win1_win1_create();
extern Xv_opaque	regis_tool_win1_controls1_create();
extern Xv_opaque	regis_tool_win1_start_bt_create();
extern Xv_opaque	regis_tool_win1_comp_bt_create();
extern Xv_opaque	regis_tool_win1_status_msg_create();
extern Xv_opaque	regis_tool_win1_each_pt_msg_create();
extern Xv_opaque	regis_tool_win1_avg_msg_create();
#endif