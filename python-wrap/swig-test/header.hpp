#ifndef KESTREL_KESTREL_STRUCT_H
#define KESTREL_KESTREL_STRUCT_H

#include <kestrel/kestrel_define.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @addtogroup kestrel_struct
/// @{

///
/// Max string length of fourcc string
///
#define KESTREL_FOURCC_MAX_STRING_SIZE (32)

///
/// FOURCC maker
///
#define KESTREL_MAKEFOURCC(a, b, c, d)                                         \
  ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))

#define KESTREL_INVALID_FOURCC (0)

///
/// Kestrel range struct definition
///
typedef struct kestrel_range_t {
  int32_t start;
  int32_t end;
} kestrel_range_t;

///
/// Kestrel integer 2D point struct definition
///
typedef struct kestrel_point2d_t {
  /** X coordinate */
  int32_t x;
  /** Y coordinate */
  int32_t y;
} kestrel_point2d_t;

///
/// Kestrel float 2D point struct definition
///
typedef struct kestrel_point2df_t {
  /** X coordinate */
  float x;
  /** Y coordinate */
  float y;
} kestrel_point2df_t;

///
/// Kestrel 2D size struct definition
///
typedef struct kestrel_size2d_t {
  /** Area width */
  int32_t width;
  /** Area Height */
  int32_t height;
} kestrel_size2d_t;

///
/// Kestrel 2D area struct definition
///
typedef struct kestrel_area2d_t {
  /** Area start coordination X */
  int32_t left;
  /** Area start coordination Y */
  int32_t top;
  /** Area width */
  int32_t width;
  /** Area Height */
  int32_t height;
} kestrel_area2d_t;

typedef struct kestrel_point3d_t {
  double x; ///< the value of the X coordinate
  double y; ///< the value of the Y coordinate
  double z; ///< the value of the Z coordinate
} kestrel_point3d_t;

typedef struct kestrel_size3d_t {
  double x; ///< the size of the X dimension
  double y; ///< the size of the Y dimension
  double z; ///< the size of the Z dimension
} kestrel_size3d_t;

typedef struct kestrel_area3d_t {
  kestrel_point3d_t point; ///< the point of the Area3d
  kestrel_size3d_t size;   ///< the size of the Area3d
} kestrel_area3d_t;

///
/// Kestrel primitive type
///
typedef enum {
  /// obscure bytes (e.g. encoded JPEG)
  KESTREL_BYTE = 0,
  /// boolean (1-byte)
  KESTREL_BOOL = 1,
  /// 8-bit signed integer
  KESTREL_INT8 = 11,
  /// 8-bit signed integer
  KESTREL_INT8x2 = 12,
  /// 8-bit signed integer
  KESTREL_INT8x3 = 13,
  /// 8-bit signed integer
  KESTREL_INT8x4 = 14,
  /// 16-bit signed integer
  KESTREL_INT16 = 21,
  /// 16-bit signed integer
  KESTREL_INT16x2 = 22,
  /// 16-bit signed integer
  KESTREL_INT16x3 = 23,
  /// 16-bit signed integer
  KESTREL_INT16x4 = 24,
  /// 32-bit signed integer
  KESTREL_INT32 = 31,
  /// 32-bit signed integer
  KESTREL_INT32x2 = 32,
  /// 32-bit signed integer
  KESTREL_INT32x3 = 33,
  /// 32-bit signed integer
  KESTREL_INT32x4 = 34,
  /// 64-bit signed integer
  KESTREL_INT64 = 4,
  /// 8-bit unsigned integer
  KESTREL_UINT8 = 51,
  /// 8-bit unsigned integer
  KESTREL_UINT8x2 = 52,
  /// 8-bit unsigned integer
  KESTREL_UINT8x3 = 53,
  /// 8-bit unsigned integer
  KESTREL_UINT8x4 = 54,
  /// 16-bit unsigned integer
  KESTREL_UINT16 = 61,
  /// 16-bit unsigned integer
  KESTREL_UINT16x2 = 62,
  /// 16-bit unsigned integer
  KESTREL_UINT16x3 = 63,
  /// 16-bit unsigned integer
  KESTREL_UINT16x4 = 64,
  /// 32-bit unsigned integer
  KESTREL_UINT32 = 71,
  /// 32-bit unsigned integer
  KESTREL_UINT32x2 = 72,
  /// 32-bit unsigned integer
  KESTREL_UINT32x3 = 73,
  /// 32-bit unsigned integer
  KESTREL_UINT32x4 = 74,
  /// 64-bit unsigned integer
  KESTREL_UINT64 = 8,
  /// 16-bit floating point real number
  KESTREL_FLOAT16 = 91,
  /// 16-bit floating point real number
  KESTREL_FLOAT16x2 = 92,
  /// 16-bit floating point real number
  KESTREL_FLOAT16x3 = 93,
  /// 16-bit floating point real number
  KESTREL_FLOAT16x4 = 94,
  /// 32-bit floating point real number
  KESTREL_FLOAT32 = 101,
  /// 32-bit floating point real number
  KESTREL_FLOAT32x2 = 102,
  /// 32-bit floating point real number
  KESTREL_FLOAT32x3 = 103,
  /// 32-bit floating point real number
  KESTREL_FLOAT32x4 = 104,
  /// 64-bit floating point real number
  KESTREL_FLOAT64 = 111,
  /// 64-bit floating point real number
  KESTREL_FLOAT64x2 = 112,
  /// 64-bit floating point real number
  KESTREL_FLOAT64x3 = 113,
  /// 64-bit floating point real number
  KESTREL_FLOAT64x4 = 114,
  /// 32-bit complex number
  KESTREL_COMPLEX32 = 121,
  /// 32-bit complex number
  KESTREL_COMPLEX32x2 = 122,
  /// 32-bit complex number
  KESTREL_COMPLEX32x3 = 123,
  /// 32-bit complex number
  KESTREL_COMPLEX32x4 = 124,
  /// 64-bit complex number
  KESTREL_COMPLEX64 = 141,
  /// 128-bit complex number
  KESTREL_COMPLEX128 = 151,
  /// Unknow
  KESTREL_DTYPE_UNKNOWN

} kestrel_data_type_e;

/// @brief Get data type element size
/// @param[in] t Data element type
/// @return Size of data type element in terms of bytes
KESTREL_API
size_t kestrel_data_type_size(kestrel_data_type_e t);

KESTREL_API
const char *kestrel_date_type_str(kestrel_data_type_e t);
/// @}

#ifdef __cplusplus
}
#endif

#endif
