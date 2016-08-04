////////////////////////////////////////////
// Params.cc
//
// TDRP C++ code file for class 'Params'.
//
// Code for program IR2Height
//
// This file has been automatically
// generated by TDRP, do not modify.
//
/////////////////////////////////////////////

/**
 *
 * @file Params.cc
 *
 * @class Params
 *
 * This class is automatically generated by the Table
 * Driven Runtime Parameters (TDRP) system
 *
 * @note Source is automatically generated from
 *       paramdef file at compile time, do not modify
 *       since modifications will be overwritten.
 *
 *
 * @author Automatically generated
 *
 */
using namespace std;

#include "Params.hh"
#include <cstring>

  ////////////////////////////////////////////
  // Default constructor
  //

  Params::Params()

  {

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // initialize table

    _init();

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Copy constructor
  //

  Params::Params(const Params& source)

  {

    // sync the source object

    source.sync();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // copy table

    tdrpCopyTable((TDRPtable *) source._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Destructor
  //

  Params::~Params()

  {

    // free up

    freeAll();

  }

  ////////////////////////////////////////////
  // Assignment
  //

  void Params::operator=(const Params& other)

  {

    // sync the other object

    other.sync();

    // free up any existing memory

    freeAll();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // copy table

    tdrpCopyTable((TDRPtable *) other._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = other._exitDeferred;

  }

  ////////////////////////////////////////////
  // loadFromArgs()
  //
  // Loads up TDRP using the command line args.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   char **params_path_p:
  //     If this is non-NULL, it is set to point to the path
  //     of the params file used.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromArgs(int argc, char **argv,
                           char **override_list,
                           char **params_path_p,
                           bool defer_exit)
  {
    int exit_deferred;
    if (_tdrpLoadFromArgs(argc, argv,
                          _table, &_start_,
                          override_list, params_path_p,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadApplyArgs()
  //
  // Loads up TDRP using the params path passed in, and applies
  // the command line args for printing and checking.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   const char *param_file_path: the parameter file to be read in
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadApplyArgs(const char *params_path,
                            int argc, char **argv,
                            char **override_list,
                            bool defer_exit)
  {
    int exit_deferred;
    if (tdrpLoadApplyArgs(params_path, argc, argv,
                          _table, &_start_,
                          override_list,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  //

  bool Params::isArgValid(const char *arg)
  {
    return (tdrpIsArgValid(arg));
  }

  ////////////////////////////////////////////
  // load()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to load
  // up more than one class for a single application. It is a
  // lower-level routine than loadFromArgs, and hence more
  // flexible, but the programmer must do more work.
  //
  //   const char *param_file_path: the parameter file to be read in.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::load(const char *param_file_path,
                   char **override_list,
                   int expand_env, int debug)
  {
    if (tdrpLoad(param_file_path,
                 _table, &_start_,
                 override_list,
                 expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadFromBuf()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to
  // load up more than one module for a single application,
  // using buffers which have been read from a specified source.
  //
  //   const char *param_source_str: a string which describes the
  //     source of the parameter information. It is used for
  //     error reporting only.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   const char *inbuf: the input buffer
  //
  //   int inlen: length of the input buffer
  //
  //   int start_line_num: the line number in the source which
  //     corresponds to the start of the buffer.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromBuf(const char *param_source_str,
                          char **override_list,
                          const char *inbuf, int inlen,
                          int start_line_num,
                          int expand_env, int debug)
  {
    if (tdrpLoadFromBuf(param_source_str,
                        _table, &_start_,
                        override_list,
                        inbuf, inlen, start_line_num,
                        expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadDefaults()
  //
  // Loads up default params for a given class.
  //
  // See load() for more detailed info.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadDefaults(int expand_env)
  {
    if (tdrpLoad(NULL,
                 _table, &_start_,
                 NULL, expand_env, FALSE)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // sync()
  //
  // Syncs the user struct data back into the parameter table,
  // in preparation for printing.
  //
  // This function alters the table in a consistent manner.
  // Therefore it can be regarded as const.
  //

  void Params::sync(void) const
  {
    tdrpUser2Table(_table, (char *) &_start_);
  }

  ////////////////////////////////////////////
  // print()
  // 
  // Print params file
  //
  // The modes supported are:
  //
  //   PRINT_SHORT:   main comments only, no help or descriptions
  //                  structs and arrays on a single line
  //   PRINT_NORM:    short + descriptions and help
  //   PRINT_LONG:    norm  + arrays and structs expanded
  //   PRINT_VERBOSE: long  + private params included
  //

  void Params::print(FILE *out, tdrp_print_mode_t mode)
  {
    tdrpPrint(out, _table, _className, mode);
  }

  ////////////////////////////////////////////
  // checkAllSet()
  //
  // Return TRUE if all set, FALSE if not.
  //
  // If out is non-NULL, prints out warning messages for those
  // parameters which are not set.
  //

  int Params::checkAllSet(FILE *out)
  {
    return (tdrpCheckAllSet(out, _table, &_start_));
  }

  //////////////////////////////////////////////////////////////
  // checkIsSet()
  //
  // Return TRUE if parameter is set, FALSE if not.
  //
  //

  int Params::checkIsSet(const char *paramName)
  {
    return (tdrpCheckIsSet(paramName, _table, &_start_));
  }

  ////////////////////////////////////////////
  // freeAll()
  //
  // Frees up all TDRP dynamic memory.
  //

  void Params::freeAll(void)
  {
    tdrpFreeAll(_table, &_start_);
  }

  ////////////////////////////////////////////
  // usage()
  //
  // Prints out usage message for TDRP args as passed
  // in to loadFromArgs().
  //

  void Params::usage(ostream &out)
  {
    out << "TDRP args: [options as below]\n"
        << "   [ -params path ] specify params file path\n"
        << "   [ -check_params] check which params are not set\n"
        << "   [ -print_params [mode]] print parameters\n"
        << "     using following modes, default mode is 'norm'\n"
        << "       short:   main comments only, no help or descr\n"
        << "                structs and arrays on a single line\n"
        << "       norm:    short + descriptions and help\n"
        << "       long:    norm  + arrays and structs expanded\n"
        << "       verbose: long  + private params included\n"
        << "       short_expand:   short with env vars expanded\n"
        << "       norm_expand:    norm with env vars expanded\n"
        << "       long_expand:    long with env vars expanded\n"
        << "       verbose_expand: verbose with env vars expanded\n"
        << "   [ -tdrp_debug] debugging prints for tdrp\n"
        << "   [ -tdrp_usage] print this usage\n";
  }

  ////////////////////////////////////////////
  // arrayRealloc()
  //
  // Realloc 1D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::arrayRealloc(const char *param_name, int new_array_n)
  {
    if (tdrpArrayRealloc(_table, &_start_,
                         param_name, new_array_n)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // array2DRealloc()
  //
  // Realloc 2D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::array2DRealloc(const char *param_name,
                             int new_array_n1,
                             int new_array_n2)
  {
    if (tdrpArray2DRealloc(_table, &_start_, param_name,
                           new_array_n1, new_array_n2)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // _init()
  //
  // Class table initialization function.
  //
  //

  void Params::_init()

  {

    TDRPtable *tt = _table;

    // Parameter 'Comment 0'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 0");
    tt->comment_hdr = tdrpStrDup("IR2Height reads a 3D temperature field output from\na model and an infrared temperature field from a\nsatellite, and then produces a field of cloud height.\n\nNiles Oien October 4 1999.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'IR_URL'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("IR_URL");
    tt->descr = tdrpStrDup("URL for infra red data.");
    tt->help = tdrpStrDup("Input satellite data are stored here.");
    tt->val_offset = (char *) &IR_URL - &_start_;
    tt->single_val.s = tdrpStrDup("");
    tt++;
    
    // Parameter 'ModelURL'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("ModelURL");
    tt->descr = tdrpStrDup("URL for model temperature data");
    tt->help = tdrpStrDup("Input 3D temperature data, typically from a model, are here.");
    tt->val_offset = (char *) &ModelURL - &_start_;
    tt->single_val.s = tdrpStrDup("");
    tt++;
    
    // Parameter 'OutputURL'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("OutputURL");
    tt->descr = tdrpStrDup("URL to write MDV files of height.");
    tt->help = tdrpStrDup("Output height MDV files are written here.");
    tt->val_offset = (char *) &OutputURL - &_start_;
    tt->single_val.s = tdrpStrDup(".");
    tt++;
    
    // Parameter 'IRFieldNum'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("IRFieldNum");
    tt->descr = tdrpStrDup("Infrared field number. This is used if greater\nthan -1, otherwise IRFieldName is used.");
    tt->help = tdrpStrDup("Set to the clear (usually 10 micron) IR channel");
    tt->val_offset = (char *) &IRFieldNum - &_start_;
    tt->single_val.i = -1;
    tt++;
    
    // Parameter 'IRFieldName'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("IRFieldName");
    tt->descr = tdrpStrDup("Infrared field name. This is used if IRFieldNum is less\nthan 0.");
    tt->help = tdrpStrDup("Set to the clear (usually 10 micron) IR channel");
    tt->val_offset = (char *) &IRFieldName - &_start_;
    tt->single_val.s = tdrpStrDup("gms_t_11");
    tt++;
    
    // Parameter 'ModelFieldName'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("ModelFieldName");
    tt->descr = tdrpStrDup("Model temperature field name.");
    tt->help = tdrpStrDup("Set to the name of the 3D temperature matrix.");
    tt->val_offset = (char *) &ModelFieldName - &_start_;
    tt->single_val.s = tdrpStrDup("Temperature");
    tt++;
    
    // Parameter 'Instance'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("Instance");
    tt->descr = tdrpStrDup("Procmap instance");
    tt->help = tdrpStrDup("Used for process identification.");
    tt->val_offset = (char *) &Instance - &_start_;
    tt->single_val.s = tdrpStrDup("primary");
    tt++;
    
    // Parameter 'MaxTimeMismatch'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("MaxTimeMismatch");
    tt->descr = tdrpStrDup("Allowable time error between a temperature and IR field, secs.");
    tt->help = tdrpStrDup("If no match can be made, then no output will be created.");
    tt->val_offset = (char *) &MaxTimeMismatch - &_start_;
    tt->single_val.i = 7200;
    tt++;
    
    // Parameter 'Debug'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("Debug");
    tt->descr = tdrpStrDup("Debug flag.");
    tt->help = tdrpStrDup("If set, more verbose output is printed on standard error.");
    tt->val_offset = (char *) &Debug - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'DoRemap'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("DoRemap");
    tt->descr = tdrpStrDup("Remap flag.");
    tt->help = tdrpStrDup("If set, data are remapped to specified grid. If not,\nthe satellite grid is used.");
    tt->val_offset = (char *) &DoRemap - &_start_;
    tt->single_val.b = pTRUE;
    tt++;
    
    // Parameter 'Comment 1'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 1");
    tt->comment_hdr = tdrpStrDup(" ------------ GRID PARAMETERS --------\nThese specify the grid on which the\ncomputations will be performed if DoRemap is TRUE.\nOtherwise the satellite grid is used and the model data\nare remapped to this.\n\nThese must be specified - use the\nprint_mdv facility to get the satellite field\ngeometry if this is to be duplicated.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'grid_origin_lat'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("grid_origin_lat");
    tt->descr = tdrpStrDup("Latitude of grid origin");
    tt->help = tdrpStrDup("Must be specified.");
    tt->val_offset = (char *) &grid_origin_lat - &_start_;
    tt->has_min = TRUE;
    tt->min_val.d = -1000;
    tt->single_val.d = 34;
    tt++;
    
    // Parameter 'grid_origin_lon'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("grid_origin_lon");
    tt->descr = tdrpStrDup("Longitude of grid origin");
    tt->help = tdrpStrDup("Must be specified.");
    tt->val_offset = (char *) &grid_origin_lon - &_start_;
    tt->has_min = TRUE;
    tt->min_val.d = -1000;
    tt->single_val.d = -77;
    tt++;
    
    // Parameter 'grid_rotation'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("grid_rotation");
    tt->descr = tdrpStrDup("Rotation (in degrees) of grid from true north");
    tt->help = tdrpStrDup("Usually 0");
    tt->val_offset = (char *) &grid_rotation - &_start_;
    tt->has_min = TRUE;
    tt->min_val.d = -360;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'grid_projection'
    // ctype is '_projection_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("grid_projection");
    tt->descr = tdrpStrDup("Projection type of grid");
    tt->help = tdrpStrDup("Projections currently supported are FLAT and LATLON");
    tt->val_offset = (char *) &grid_projection - &_start_;
    tt->enum_def.name = tdrpStrDup("projection_t");
    tt->enum_def.nfields = 3;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("FLAT");
      tt->enum_def.fields[0].val = FLAT;
      tt->enum_def.fields[1].name = tdrpStrDup("LATLON");
      tt->enum_def.fields[1].val = LATLON;
      tt->enum_def.fields[2].name = tdrpStrDup("LAMBERT");
      tt->enum_def.fields[2].val = LAMBERT;
    tt->single_val.e = FLAT;
    tt++;
    
    // Parameter 'grid_nx'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("grid_nx");
    tt->descr = tdrpStrDup("Number of cells in the grid in X");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &grid_nx - &_start_;
    tt->has_min = TRUE;
    tt->min_val.i = 1;
    tt->single_val.i = 100;
    tt++;
    
    // Parameter 'grid_ny'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("grid_ny");
    tt->descr = tdrpStrDup("Number of cells in the grid in Y");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &grid_ny - &_start_;
    tt->has_min = TRUE;
    tt->min_val.i = 1;
    tt->single_val.i = 100;
    tt++;
    
    // Parameter 'grid_dx'
    // ctype is 'float'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = FLOAT_TYPE;
    tt->param_name = tdrpStrDup("grid_dx");
    tt->descr = tdrpStrDup("Size of the cells in the output grid in X");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &grid_dx - &_start_;
    tt->single_val.f = 1;
    tt++;
    
    // Parameter 'grid_dy'
    // ctype is 'float'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = FLOAT_TYPE;
    tt->param_name = tdrpStrDup("grid_dy");
    tt->descr = tdrpStrDup("Size of the cells in the output grid in Y");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &grid_dy - &_start_;
    tt->single_val.f = 1;
    tt++;
    
    // Parameter 'grid_minx'
    // ctype is 'float'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = FLOAT_TYPE;
    tt->param_name = tdrpStrDup("grid_minx");
    tt->descr = tdrpStrDup("X at grid's lower left corner");
    tt->help = tdrpStrDup("Units for this parameter will depend upon the output grid_projection.");
    tt->val_offset = (char *) &grid_minx - &_start_;
    tt->single_val.f = 0;
    tt++;
    
    // Parameter 'grid_miny'
    // ctype is 'float'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = FLOAT_TYPE;
    tt->param_name = tdrpStrDup("grid_miny");
    tt->descr = tdrpStrDup("Y at grid's lower left corner");
    tt->help = tdrpStrDup("Units for this parameter will depend upon the output grid_projection.");
    tt->val_offset = (char *) &grid_miny - &_start_;
    tt->single_val.f = 0;
    tt++;
    
    // Parameter 'grid_lat1'
    // ctype is 'float'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = FLOAT_TYPE;
    tt->param_name = tdrpStrDup("grid_lat1");
    tt->descr = tdrpStrDup("Lambert true latitude 1");
    tt->help = tdrpStrDup("For use with Lambert projection only.");
    tt->val_offset = (char *) &grid_lat1 - &_start_;
    tt->single_val.f = 0;
    tt++;
    
    // Parameter 'grid_lat2'
    // ctype is 'float'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = FLOAT_TYPE;
    tt->param_name = tdrpStrDup("grid_lat2");
    tt->descr = tdrpStrDup("Lambert true latitude 2");
    tt->help = tdrpStrDup("For use with Lambert projection only.");
    tt->val_offset = (char *) &grid_lat2 - &_start_;
    tt->single_val.f = 0;
    tt++;
    
    // Parameter 'Comment 2'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 2");
    tt->comment_hdr = tdrpStrDup("------ End of grid parameters. ");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'MinHeight'
    // ctype is 'float'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = FLOAT_TYPE;
    tt->param_name = tdrpStrDup("MinHeight");
    tt->descr = tdrpStrDup("Lower limit on height - same units as used in 3D Temperature field.");
    tt->help = tdrpStrDup("If the computed cloud height is less than this, set it to missing.");
    tt->val_offset = (char *) &MinHeight - &_start_;
    tt->single_val.f = 50;
    tt++;
    
    // Parameter 'MaxHeight'
    // ctype is 'float'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = FLOAT_TYPE;
    tt->param_name = tdrpStrDup("MaxHeight");
    tt->descr = tdrpStrDup("If the IR temperature is colder than any of the model temperaures\nthen use this height.");
    tt->help = tdrpStrDup("Set to a value one step above the top model temperature.");
    tt->val_offset = (char *) &MaxHeight - &_start_;
    tt->single_val.f = 470;
    tt++;
    
    // Parameter 'MaxIRTemperature'
    // ctype is 'float'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = FLOAT_TYPE;
    tt->param_name = tdrpStrDup("MaxIRTemperature");
    tt->descr = tdrpStrDup("Upper limit on IR temperature");
    tt->help = tdrpStrDup("If the temperature is warmer than this, set the output to missing.");
    tt->val_offset = (char *) &MaxIRTemperature - &_start_;
    tt->single_val.f = 0;
    tt++;
    
    // Parameter 'MaxRealtimeValidAge'
    // ctype is 'long'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = LONG_TYPE;
    tt->param_name = tdrpStrDup("MaxRealtimeValidAge");
    tt->descr = tdrpStrDup("Max age (in seconds) of input data");
    tt->help = tdrpStrDup("For realtime only - max age of input data for it to be valid");
    tt->val_offset = (char *) &MaxRealtimeValidAge - &_start_;
    tt->has_min = TRUE;
    tt->has_max = TRUE;
    tt->min_val.l = 0;
    tt->max_val.l = 86400;
    tt->single_val.l = 60;
    tt++;
    
    // Parameter 'Scale'
    // ctype is 'float'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = FLOAT_TYPE;
    tt->param_name = tdrpStrDup("Scale");
    tt->descr = tdrpStrDup("Scale to aply to height");
    tt->help = tdrpStrDup("to change from Km to meters set to 1000.0");
    tt->val_offset = (char *) &Scale - &_start_;
    tt->single_val.f = 1;
    tt++;
    
    // Parameter 'HeightUnits'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("HeightUnits");
    tt->descr = tdrpStrDup("Units for height");
    tt->help = tdrpStrDup("Should be the same as the height scale in the 3D\ntemperature MDV file if Scale is 1.0.");
    tt->val_offset = (char *) &HeightUnits - &_start_;
    tt->single_val.s = tdrpStrDup("FL");
    tt++;
    
    // Parameter 'DataDuration'
    // ctype is 'long'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = LONG_TYPE;
    tt->param_name = tdrpStrDup("DataDuration");
    tt->descr = tdrpStrDup("Time in seconds before data expire.");
    tt->help = tdrpStrDup("Usually set to approximate incoming satellite data rate.");
    tt->val_offset = (char *) &DataDuration - &_start_;
    tt->single_val.l = 3600;
    tt++;
    
    // trailing entry has param_name set to NULL
    
    tt->param_name = NULL;
    
    return;
  
  }