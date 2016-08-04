// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2016
// ** University Corporation for Atmospheric Research(UCAR)
// ** National Center for Atmospheric Research(NCAR)
// ** Boulder, Colorado, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
////////////////////////////////////////////
// Params.hh
//
// TDRP header file for 'Params' class.
//
// Code for program Wrf2Mdv
//
// This header file has been automatically
// generated by TDRP, do not modify.
//
/////////////////////////////////////////////

/**
 *
 * @file Params.hh
 *
 * This class is automatically generated by the Table
 * Driven Runtime Parameters (TDRP) system
 *
 * @class Params
 *
 * @author automatically generated
 *
 */

#ifndef Params_hh
#define Params_hh

using namespace std;

#include <tdrp/tdrp.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>

// Class definition

class Params {

public:

  // enum typedefs

  typedef enum {
    DEBUG_OFF = 0,
    DEBUG_WARNINGS = 1,
    DEBUG_NORM = 2,
    DEBUG_VERBOSE = 3
  } debug_t;

  typedef enum {
    DEBUG_RH2 = 0,
    DEBUG_SOIL_AM = 1,
    DEBUG_NONE = 2
  } alg_debug_t;

  typedef enum {
    ARCHIVE = 0,
    REALTIME = 1
  } mode_t;

  typedef enum {
    U_FIELD = 0,
    V_FIELD = 1,
    Q_FIELD = 2,
    CLW_FIELD = 3,
    RNW_FIELD = 4,
    ICE_FIELD = 5,
    SNOW_FIELD = 6,
    GRAUPEL_FIELD = 7,
    W_FIELD = 8,
    P_FIELD = 9,
    PB_FIELD = 10,
    PHB_FIELD = 11,
    PH_FIELD = 12,
    DNW_FIELD = 13,
    MUB_FIELD = 14,
    MU_FIELD = 15,
    REFL_10CM_FIELD = 16,
    U_EDGE_FIELD = 17,
    V_EDGE_FIELD = 18,
    TK_FIELD = 19,
    TC_FIELD = 20,
    WSPD_FIELD = 21,
    WDIR_FIELD = 22,
    PRESSURE_FIELD = 23,
    RH_FIELD = 24,
    SPEC_H_FIELD = 25,
    DEWPT_FIELD = 26,
    ICING_FIELD = 27,
    CLW_G_FIELD = 28,
    RNW_G_FIELD = 29,
    THETA_FIELD = 30,
    DBZ_3D_FIELD = 31,
    HGT_FIELD = 32,
    Z_AGL_FIELD = 33,
    ITFADEF_FIELD = 34,
    GEO_POT_FIELD = 35,
    Q_G_FIELD = 36,
    CAPE_3D_FIELD = 37,
    CIN_3D_FIELD = 38,
    LCL_3D_FIELD = 39,
    LFC_3D_FIELD = 40,
    EL_3D_FIELD = 41,
    START_2D_FIELDS = 42,
    SOIL_T_1_FIELD = 43,
    SOIL_T_2_FIELD = 44,
    SOIL_T_3_FIELD = 45,
    SOIL_T_4_FIELD = 46,
    SOIL_T_5_FIELD = 47,
    SOIL_M_1_FIELD = 48,
    SOIL_M_2_FIELD = 49,
    SOIL_M_3_FIELD = 50,
    SOIL_M_4_FIELD = 51,
    SOIL_M_5_FIELD = 52,
    SOIL_AM_1_FIELD = 53,
    SOIL_AM_2_FIELD = 54,
    SOIL_AM_3_FIELD = 55,
    SOIL_AM_4_FIELD = 56,
    SOIL_AM_5_FIELD = 57,
    LAT_FIELD = 58,
    LON_FIELD = 59,
    GROUND_T_FIELD = 60,
    RAINC_FIELD = 61,
    RAINNC_FIELD = 62,
    TERRAIN_FIELD = 63,
    LAND_USE_FIELD = 64,
    SNOWCOVR_FIELD = 65,
    TSEASFC_FIELD = 66,
    PBL_HGT_FIELD = 67,
    T2_FIELD = 68,
    Q2_FIELD = 69,
    U10_FIELD = 70,
    V10_FIELD = 71,
    SNOWH_FIELD = 72,
    SFC_PRES_FIELD = 73,
    LAND_MASK_FIELD = 74,
    TH2_FIELD = 75,
    HFX_FIELD = 76,
    LH_FIELD = 77,
    SNOW_WE_FIELD = 78,
    SNOW_NC_FIELD = 79,
    GRAUPEL_NC_FIELD = 80,
    SOIL_TYPE_FIELD = 81,
    FZLEVEL_FIELD = 82,
    RAIN_TOTAL_FIELD = 83,
    RH2_FIELD = 84,
    T2C_FIELD = 85,
    WSPD10_FIELD = 86,
    WDIR10_FIELD = 87,
    TWP_FIELD = 88,
    RWP_FIELD = 89,
    VIL_FIELD = 90,
    DBZ_2D_FIELD = 91,
    SPEC_H_2M_FIELD = 92,
    CAPE_FIELD = 93,
    CIN_FIELD = 94,
    LCL_FIELD = 95,
    LFC_FIELD = 96,
    EL_FIELD = 97,
    LANDUSEF_1_FIELD = 98,
    LANDUSEF_2_FIELD = 99,
    LANDUSEF_6_FIELD = 100,
    LANDUSEF_15_FIELD = 101,
    GREENFRAC_7_FIELD = 102,
    TOTAL_FIELD_COUNT = 103
  } output_field_name_t;

  typedef enum {
    OUT_INT8 = 1,
    OUT_INT16 = 2,
    OUT_FLOAT32 = 5
  } output_encoding_t;

  typedef enum {
    OUTPUT_PROJ_FLAT = 0,
    OUTPUT_PROJ_LATLON = 1,
    OUTPUT_PROJ_LAMBERT = 2,
    OUTPUT_PROJ_STEREOGRAPHIC = 3,
    OUTPUT_PROJ_MERCATOR = 4,
    OUTPUT_PROJ_NATIVE = 5
  } output_projection_t;

  typedef enum {
    FLIGHT_LEVELS = 0,
    PRESSURE_LEVELS = 1,
    HEIGHT_LEVELS = 2,
    NATIVE_VERTICAL_LEVELS = 3
  } output_levels_t;

  typedef enum {
    _MDV_COMPRESSION_NONE = 0,
    _MDV_COMPRESSION_RLE = 1,
    _MDV_COMPRESSION_LZO = 2,
    _MDV_COMPRESSION_ZLIB = 3,
    _MDV_COMPRESSION_BZIP = 4
  } compression_t;

  typedef enum {
    SCALING_ROUNDED = 0,
    SCALING_DYNAMIC = 1
  } scaling_t;

  // struct typedefs

  typedef struct {
    output_field_name_t name;
    output_encoding_t encoding;
  } output_field_t;

  typedef struct {
    output_field_name_t original_name;
    char* name;
    char* long_name;
  } afield_name_map_t;

  typedef struct {
    double lat;
    double lon;
  } output_origin_t;

  typedef struct {
    int nx;
    int ny;
    double minx;
    double miny;
    double dx;
    double dy;
  } output_grid_t;

  typedef struct {
    double lower_level;
    double upper_level;
  } pressure_limits_t;

  ///////////////////////////
  // Member functions
  //

  ////////////////////////////////////////////
  // Default constructor
  //

  Params ();

  ////////////////////////////////////////////
  // Copy constructor
  //

  Params (const Params&);

  ////////////////////////////////////////////
  // Destructor
  //

  ~Params ();

  ////////////////////////////////////////////
  // Assignment
  //

  void operator=(const Params&);

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

  int loadFromArgs(int argc, char **argv,
                   char **override_list,
                   char **params_path_p,
                   bool defer_exit = false);

  bool exitDeferred() { return (_exitDeferred); }

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

  int loadApplyArgs(const char *params_path,
                    int argc, char **argv,
                    char **override_list,
                    bool defer_exit = false);

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  //

  static bool isArgValid(const char *arg);

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

  int load(const char *param_file_path,
           char **override_list,
           int expand_env, int debug);

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

  int loadFromBuf(const char *param_source_str,
                  char **override_list,
                  const char *inbuf, int inlen,
                  int start_line_num,
                  int expand_env, int debug);

  ////////////////////////////////////////////
  // loadDefaults()
  //
  // Loads up default params for a given class.
  //
  // See load() for more detailed info.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int loadDefaults(int expand_env);

  ////////////////////////////////////////////
  // sync()
  //
  // Syncs the user struct data back into the parameter table,
  // in preparation for printing.
  //
  // This function alters the table in a consistent manner.
  // Therefore it can be regarded as const.
  //

  void sync() const;

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

  void print(FILE *out, tdrp_print_mode_t mode = PRINT_NORM);

  ////////////////////////////////////////////
  // checkAllSet()
  //
  // Return TRUE if all set, FALSE if not.
  //
  // If out is non-NULL, prints out warning messages for those
  // parameters which are not set.
  //

  int checkAllSet(FILE *out);

  //////////////////////////////////////////////////////////////
  // checkIsSet()
  //
  // Return TRUE if parameter is set, FALSE if not.
  //
  //

  int checkIsSet(const char *param_name);

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

  int arrayRealloc(const char *param_name,
                   int new_array_n);

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

  int array2DRealloc(const char *param_name,
                     int new_array_n1,
                     int new_array_n2);

  ////////////////////////////////////////////
  // freeAll()
  //
  // Frees up all TDRP dynamic memory.
  //

  void freeAll(void);

  ////////////////////////////////////////////
  // usage()
  //
  // Prints out usage message for TDRP args as passed
  // in to loadFromArgs().
  //

  static void usage(ostream &out);

  ///////////////////////////
  // Data Members
  //

  char _start_; // start of data region
                // needed for zeroing out data
                // and computing offsets

  debug_t debug;

  alg_debug_t alg_debug;

  char* instance;

  int Procmap_reg_interval_secs;

  mode_t mode;

  char* soilparm_path;

  char* realtime_input_dir;

  int File_quiescence_secs;

  int Dir_search_depth;

  int Dir_scan_interval_secs;

  char* DomainString;

  char* File_extension;

  tdrp_bool_t use_ldata;

  tdrp_bool_t get_times_from_filenames;

  int max_realtime_valid_age;

  int min_forecast_dtime;

  int max_forecast_dtime;

  tdrp_bool_t specify_lead_times;

  int *_lead_times;
  int lead_times_n;

  char* output_url;

  output_field_t *_output_fields;
  int output_fields_n;

  afield_name_map_t *_field_name_map;
  int field_name_map_n;

  tdrp_bool_t wind_speed_in_knots;

  output_projection_t output_projection;

  output_origin_t output_origin;

  double lambert_lat1;

  double lambert_lat2;

  double stereographic_tangent_lat;

  double stereographic_tangent_lon;

  output_grid_t output_grid;

  output_levels_t output_levels;

  int *_flight_levels;
  int flight_levels_n;

  double *_pressure_levels;
  int pressure_levels_n;

  double *_height_levels;
  int height_levels_n;

  tdrp_bool_t copy_lowest_downwards;

  compression_t output_compression;

  scaling_t output_scaling;

  tdrp_bool_t output_path_in_forecast_format;

  char* data_set_info;

  char* data_set_name;

  char* data_set_source;

  float no_icing_clw;

  float trace_icing_clw;

  float trace_severity;

  float light_icing_clw;

  float light_severity;

  float moderate_icing_clw;

  float moderate_severity;

  float severe_icing_clw;

  float severe_severity;

  char* adiabat_temp_lookup_filename;

  tdrp_bool_t negative_cin;

  pressure_limits_t pressure_limits;

  char _end_; // end of data region
              // needed for zeroing out data

private:

  void _init();

  mutable TDRPtable _table[63];

  const char *_className;

  bool _exitDeferred;

};

#endif
