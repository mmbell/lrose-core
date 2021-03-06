#ifndef	save_pu_HEADER
#define	save_pu_HEADER

/*
 * save_pu_ui.h - User interface object and function declarations.
 * This file was generated by `gxv' from `save_pu.G'.
 * DO NOT EDIT BY HAND.
 */

extern Attr_attribute	INSTANCE;


typedef struct {
	Xv_opaque	save_im_pu;
	Xv_opaque	save_cp;
	Xv_opaque	dir_tx;
	Xv_opaque	fname_tx;
	Xv_opaque	cmd_tx;
	Xv_opaque	save_bt;
	Xv_opaque	cancel_bt;
	Xv_opaque	save_pu_msg;
} save_pu_save_im_pu_objects;

extern save_pu_save_im_pu_objects	*save_pu_save_im_pu_objects_initialize();

extern Xv_opaque	save_pu_save_im_pu_save_im_pu_create();
extern Xv_opaque	save_pu_save_im_pu_save_cp_create();
extern Xv_opaque	save_pu_save_im_pu_dir_tx_create();
extern Xv_opaque	save_pu_save_im_pu_fname_tx_create();
extern Xv_opaque	save_pu_save_im_pu_cmd_tx_create();
extern Xv_opaque	save_pu_save_im_pu_save_bt_create();
extern Xv_opaque	save_pu_save_im_pu_cancel_bt_create();
extern Xv_opaque	save_pu_save_im_pu_save_pu_msg_create();
#endif
