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
/*******************************************
 * _tdrp.c
 *
 * TDRP C code file.
 *
 * Code for program mdv_thresh_cnt
 *
 * This file has been automatically
 * generated by TDRP, do not modify.
 *
 *******************************************/

#include "_tdrp.h"
#include <string.h>

/*
 * file scope variables
 */

static TDRPtable Table[9];
static _tdrp_struct *Params;
static char *Module = "";

/*************************************************************
 * _tdrp_load_from_args()
 *
 * Loads up TDRP using the command line args.
 *
 * Check TDRP_usage() for command line actions associated with
 * this function.
 *
 *   argc, argv: command line args
 *
 *   _tdrp_struct *params: loads up this struct
 * 
 *   char **override_list: A null-terminated list of overrides
 *     to the parameter file.
 *     An override string has exactly the format of an entry
 *     in the parameter file itself.
 *
 *   char **params_path_p: if non-NULL, this is set to point to
 *                         the path of the params file used.
 *
 *  Returns 0 on success, -1 on failure.
 */

int _tdrp_load_from_args(int argc, char **argv,
                         _tdrp_struct *params,
                         char **override_list,
                         char **params_path_p)
{
  Params = params;
  _tdrp_init(Params);
  if (tdrpLoadFromArgs(argc, argv,
                       Table, Params,
                       override_list, params_path_p)) {
    return (-1);
  } else {
    return (0);
  }
}

/*************************************************************
 * _tdrp_load()
 *
 * Loads up TDRP for a given module.
 *
 * This version of load gives the programmer the option to load
 * up more than one module for a single application. It is a
 * lower-level routine than _tdrp_load_from_args,
 * and hence more flexible, but the programmer must do more work.
 *
 *   char *param_file_path: the parameter file to be read in.
 *
 *   _tdrp_struct *params: loads up this struct
 *
 *   char **override_list: A null-terminated list of overrides
 *     to the parameter file.
 *     An override string has exactly the format of an entry
 *     in the parameter file itself.
 *
 *  expand_env: flag to control environment variable
 *                expansion during tokenization.
 *              If TRUE, environment expansion is set on.
 *              If FALSE, environment expansion is set off.
 *
 *  Returns 0 on success, -1 on failure.
 */

int _tdrp_load(char *param_file_path,
               _tdrp_struct *params,
               char **override_list,
               int expand_env, int debug)
{
  Params = params;
  _tdrp_init(Params);
  if (tdrpLoad(param_file_path, Table,
               params, override_list,
               expand_env, debug)) {
    return (-1);
  } else {
    return (0);
  }
}

/*************************************************************
 * _tdrp_load_defaults()
 *
 * Loads up defaults for a given module.
 *
 * See _tdrp_load() for more details.
 *
 *  Returns 0 on success, -1 on failure.
 */

int _tdrp_load_defaults(_tdrp_struct *params,
                        int expand_env)
{
  Params = params;
  _tdrp_init(Params);
  if (tdrpLoad(NULL, Table,
               params, NULL,
               expand_env, FALSE)) {
    return (-1);
  } else {
    return (0);
  }
}

/*************************************************************
 * _tdrp_sync()
 *
 * Syncs the user struct data back into the parameter table,
 * in preparation for printing.
 */

void _tdrp_sync(void)
{
  tdrpUser2Table(Table, Params);
}

/*************************************************************
 * _tdrp_print()
 * 
 * Print params file
 *
 * The modes supported are:
 *
 *   PRINT_SHORT:   main comments only, no help or descriptions
 *                  structs and arrays on a single line
 *   PRINT_NORM:    short + descriptions and help
 *   PRINT_LONG:    norm  + arrays and structs expanded
 *   PRINT_VERBOSE: long  + private params included
 */

void _tdrp_print(FILE *out, tdrp_print_mode_t mode)
{
  tdrpPrint(out, Table, Module, mode);
}

/*************************************************************
 * _tdrp_check_all_set()
 *
 * Return TRUE if all set, FALSE if not.
 *
 * If out is non-NULL, prints out warning messages for those
 * parameters which are not set.
 */

int _tdrp_check_all_set(FILE *out)
{
  return (tdrpCheckAllSet(out, Table, Params));
}

/*************************************************************
 * _tdrp_check_is_set()
 *
 * Return TRUE if parameter is set, FALSE if not.
 *
 */

int _tdrp_check_is_set(char *param_name)
{
  return (tdrpCheckIsSet(param_name, Table, Params));
}

/*************************************************************
 * _tdrp_free_all()
 *
 * Frees up all TDRP dynamic memory.
 */

void _tdrp_free_all(void)
{
  tdrpFreeAll(Table, Params);
}

/*************************************************************
 * _tdrp_array_realloc()
 *
 * Realloc 1D array.
 *
 * If size is increased, the values from the last array entry is
 * copied into the new space.
 *
 * Returns 0 on success, -1 on error.
 */

int _tdrp_array_realloc(char *param_name, int new_array_n)
{
  if (tdrpArrayRealloc(Table, Params, param_name, new_array_n)) {
    return (-1);
  } else {
    return (0);
  }
}

/*************************************************************
 * _tdrp_array2D_realloc()
 *
 * Realloc 2D array.
 *
 * If size is increased, the values from the last array entry is
 * copied into the new space.
 *
 * Returns 0 on success, -1 on error.
 */

int _tdrp_array2D_realloc(char *param_name,
                          int new_array_n1,
                          int new_array_n2)
{
  if (tdrpArray2DRealloc(Table, Params, param_name,
			 new_array_n1, new_array_n2)) {
    return (-1);
  } else {
    return (0);
  }
}

/*************************************************************
 * _tdrp_table()
 *
 * Returns pointer to static Table for this module.
 */

TDRPtable *_tdrp_table(void)
{
  return (Table);
}

/*************************************************************
 * _tdrp_init()
 *
 * Module table initialization function.
 *
 *
 * Returns pointer to static Table for this module.
 */

TDRPtable *_tdrp_init(_tdrp_struct *params)

{

  TDRPtable *tt = Table;

  _tdrp_struct pp; /* for computing byte_offsets */

  /* zero out struct, and store size */

  memset(params, 0, sizeof(_tdrp_struct));
  params->struct_size = sizeof(_tdrp_struct);

  /* Parameter 'thresh_comp' */
  /* ctype is '_thresh_comp_t' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = ENUM_TYPE;
  tt->param_name = tdrpStrDup("thresh_comp");
  tt->descr = tdrpStrDup("Threshold comparison type.");
  tt->help = tdrpStrDup("Data values will be compared to threshold using the thresh_comp comparison.");
  tt->val_offset = (char *) &(pp.thresh_comp) - (char *) &pp;
  tt->enum_def.name = tdrpStrDup("thresh_comp_t");
  tt->enum_def.nfields = 4;
  tt->enum_def.fields = (enum_field_t *)
      tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
    tt->enum_def.fields[0].name = tdrpStrDup("LESS_THAN");
    tt->enum_def.fields[0].val = LESS_THAN;
    tt->enum_def.fields[1].name = tdrpStrDup("LESS_THAN_OR_EQUAL");
    tt->enum_def.fields[1].val = LESS_THAN_OR_EQUAL;
    tt->enum_def.fields[2].name = tdrpStrDup("GREATER_THAN");
    tt->enum_def.fields[2].val = GREATER_THAN;
    tt->enum_def.fields[3].name = tdrpStrDup("GREATER_THAN_OR_EQUAL");
    tt->enum_def.fields[3].val = GREATER_THAN_OR_EQUAL;
  tt->single_val.e = GREATER_THAN_OR_EQUAL;
  tt++;
  
  /* Parameter 'debug' */
  /* ctype is '_debug' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = ENUM_TYPE;
  tt->param_name = tdrpStrDup("debug");
  tt->descr = tdrpStrDup("Debug option");
  tt->help = tdrpStrDup("If set, debug messages will be printed with the appropriate level of detail.");
  tt->val_offset = (char *) &(pp.debug) - (char *) &pp;
  tt->enum_def.name = tdrpStrDup("debug");
  tt->enum_def.nfields = 4;
  tt->enum_def.fields = (enum_field_t *)
      tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
    tt->enum_def.fields[0].name = tdrpStrDup("DEBUG_OFF");
    tt->enum_def.fields[0].val = DEBUG_OFF;
    tt->enum_def.fields[1].name = tdrpStrDup("DEBUG_WARNINGS");
    tt->enum_def.fields[1].val = DEBUG_WARNINGS;
    tt->enum_def.fields[2].name = tdrpStrDup("DEBUG_NORM");
    tt->enum_def.fields[2].val = DEBUG_NORM;
    tt->enum_def.fields[3].name = tdrpStrDup("DEBUG_VERBOSE");
    tt->enum_def.fields[3].val = DEBUG_VERBOSE;
  tt->single_val.e = DEBUG_OFF;
  tt++;
  
  /* Parameter 'mode' */
  /* ctype is '_mode' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = ENUM_TYPE;
  tt->param_name = tdrpStrDup("mode");
  tt->descr = tdrpStrDup("Operation mode");
  tt->help = tdrpStrDup("Program may be run in two modes, archive and realtime. In realtime mode, the analysis is performed for each volume scan as it becomes available. In archiv mode, the file list is obtained from the command line.");
  tt->val_offset = (char *) &(pp.mode) - (char *) &pp;
  tt->enum_def.name = tdrpStrDup("mode");
  tt->enum_def.nfields = 2;
  tt->enum_def.fields = (enum_field_t *)
      tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
    tt->enum_def.fields[0].name = tdrpStrDup("ARCHIVE");
    tt->enum_def.fields[0].val = ARCHIVE;
    tt->enum_def.fields[1].name = tdrpStrDup("REALTIME");
    tt->enum_def.fields[1].val = REALTIME;
  tt->single_val.e = ARCHIVE;
  tt++;
  
  /* Parameter 'trigger' */
  /* ctype is '_trigger' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = ENUM_TYPE;
  tt->param_name = tdrpStrDup("trigger");
  tt->descr = tdrpStrDup("Trigger mechanism.");
  tt->help = tdrpStrDup("TIME_TRIGGER: the program is triggered at constant time intervals - see time_trigger_interval. FILE_TRIGGER: the program watches the first input_dir and triggers based on data in that directory.");
  tt->val_offset = (char *) &(pp.trigger) - (char *) &pp;
  tt->enum_def.name = tdrpStrDup("trigger");
  tt->enum_def.nfields = 2;
  tt->enum_def.fields = (enum_field_t *)
      tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
    tt->enum_def.fields[0].name = tdrpStrDup("TIME_TRIGGER");
    tt->enum_def.fields[0].val = TIME_TRIGGER;
    tt->enum_def.fields[1].name = tdrpStrDup("FILE_TRIGGER");
    tt->enum_def.fields[1].val = FILE_TRIGGER;
  tt->single_val.e = FILE_TRIGGER;
  tt++;
  
  /* Parameter 'time_trigger_interval' */
  /* ctype is 'long' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = LONG_TYPE;
  tt->param_name = tdrpStrDup("time_trigger_interval");
  tt->descr = tdrpStrDup("Interval for TIME_TRIGGER - secs.");
  tt->help = tdrpStrDup("For TIME_TRIGGER, this is the interval between trigger events. In REALTIME mode, a time trigger always occurs on the hour, and at constant intervals thereafter. In ARCHIVE mode the trigger starts at start_time and at constant intervals thereafter.");
  tt->val_offset = (char *) &(pp.time_trigger_interval) - (char *) &pp;
  tt->has_min = TRUE;
  tt->min_val.l = 0;
  tt->single_val.l = 300;
  tt++;
  
  /* Parameter 'trigger_time_margin' */
  /* ctype is 'long' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = LONG_TYPE;
  tt->param_name = tdrpStrDup("trigger_time_margin");
  tt->descr = tdrpStrDup("Max time diff for searching for files relative to the trigger time - secs.");
  tt->help = tdrpStrDup("When matching files up with the trigger time, the difference between the trigger time and file time must be less than this margin. This value is also used as the max age of the latest data info file when in REALTIME mode with FILE_TRIGGER.");
  tt->val_offset = (char *) &(pp.trigger_time_margin) - (char *) &pp;
  tt->has_min = TRUE;
  tt->min_val.l = 0;
  tt->single_val.l = 600;
  tt++;
  
  /* Parameter 'input_dirs' */
  /* ctype is 'char*' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = STRING_TYPE;
  tt->param_name = tdrpStrDup("input_dirs");
  tt->descr = tdrpStrDup("Input directory.");
  tt->help = tdrpStrDup("If available, data from this directory will be counted.");
  tt->val_offset = (char *) &(pp.input_dirs) - (char *) &pp;
  tt->single_val.s = tdrpStrDup(".");
  tt++;
  
  /* Parameter 'field_num' */
  /* ctype is 'int' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = INT_TYPE;
  tt->param_name = tdrpStrDup("field_num");
  tt->descr = tdrpStrDup("Field number to be processed from input files.");
  tt->help = tdrpStrDup("This field will be read from the input files and data values above threshold counted.");
  tt->val_offset = (char *) &(pp.field_num) - (char *) &pp;
  tt->has_min = TRUE;
  tt->min_val.i = 0;
  tt->single_val.i = 0;
  tt++;
  
  /* trailing entry has param_name set to NULL */
  
  tt->param_name = NULL;
  
  return (Table);

}
