#pragma once
#include "WFS.h"

// Device IDs
#define  DEVICE_OFFSET_WFS10           (0x00100) // device IDs of WFS10 instruments start at 256 decimal
#define  DEVICE_OFFSET_WFS20           (0x00200) // device IDs of WFS20 instruments start at 512 decimal
#define  DEVICE_OFFSET_WFS30           (0x00400) // device IDs of WFS30 instruments start at 1024 decimal
#define  DEVICE_OFFSET_WFS40           (0x00800) // device IDs of WFS40 instruments start at 2048 decimal
#define  DEVICE_OFFSET_WFS31           (0x01000) // device IDs of WFS31 instruments start at 4096 decimal

// Options macros
#define  OPTION_OFF                    (0)
#define  OPTION_ON                     (1)

// Camera settings
#define  SAMPLE_PIXEL_FORMAT           PIXEL_FORMAT_MONO8   // only 8 bit format is supported
#define  SAMPLE_CAMERA_RESOL_WFS20     CAM_RES_WFS20_512    // 512x512 pixels
#define  SAMPLE_REF_PLANE              WFS_REF_INTERNAL

// Pupil Settings
#define  SAMPLE_PUPIL_CENTROID_X       (0.0) // in mm
#define  SAMPLE_PUPIL_CENTROID_Y       (0.0)
#define  SAMPLE_PUPIL_DIAMETER_X       (2.0) // in mm, needs to fit to selected camera resolution
#define  SAMPLE_PUPIL_DIAMETER_Y       (2.0)


// Miscellaneous settings
#define  SAMPLE_IMAGE_READINGS         (10) // trials to read a exposed spotfield image

#define  SAMPLE_WAVEFRONT_TYPE         WAVEFRONT_MEAS // calculate measured wavefront

#define  SAMPLE_PRINTOUT_SPOTS         (5)  // printout results for first 5 x 5 spots only

#define  SAMPLE_OUTPUT_FILE_NAME       "WFS_sample_output.txt"