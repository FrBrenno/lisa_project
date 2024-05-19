#pragma once
#include "thorlabs_api/WFS.h"

// Device IDs
#define  DEVICE_OFFSET_WFS20           (0x00200) // device IDs of WFS20 instruments start at 512 decimal

// Camera settings
#define  SAMPLE_PIXEL_FORMAT           PIXEL_FORMAT_MONO8   // only 8 bit format is supported
#define  SAMPLE_CAMERA_RESOL_WFS20     CAM_RES_WFS20_512    // 512x512 pixels
#define  SAMPLE_REF_PLANE              WFS_REF_INTERNAL

// Pupil Settings
#define  SAMPLE_PUPIL_CENTROID_X       (0.0) // in mm
#define  SAMPLE_PUPIL_CENTROID_Y       (0.0)
#define  SAMPLE_PUPIL_DIAMETER_X       (2.0) // in mm, needs to fit to selected camera resolution
#define  SAMPLE_PUPIL_DIAMETER_Y       (2.0)
