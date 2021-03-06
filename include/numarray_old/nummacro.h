#if !defined(_ndarraymacro)
#define _ndarraymacro

/* The structs defined here are private implementation details of numarray
which are subject to change w/o notice.
*/

typedef struct
{
	long in1, in2, out, thread_id;
	char cumop[12]; 
	PyObject *type;
	PyObject *ctuple;
} _cache_entry;

typedef struct
{
	int insert;
	_cache_entry entry[20];
} _ufunc_cache;

typedef PyObject *(*_ufunc_function)(PyObject *ufunc, 
				     int n_ins, PyObject *ins[], 
				     int n_outs, PyObject*outs[]);
typedef struct {
	PyObject_HEAD
	PyObject *oprator;          /* ufunc name */
        PyObject *identity;          /* identity value, e.g. 0 for + or 1 for * */
        int   n_inputs, n_outputs;
        _ufunc_function call;
	_ufunc_cache cache;
} PyUfuncObject;

typedef struct {
	PyObject_HEAD
	PyObject *(*compute)(PyObject*,PyObject*,PyObject*);   /* Must match PyOperatorObject */
	PyObject *(*rebuffer)(PyObject*,PyObject*,PyObject*);
	void (*clean)(PyObject*,PyObject*);
	int       arr_position;
	int       inb_position;
	int       direction;
	int       generated;
	int       conversion_required;
	PyObject  *buffers[4];
	PyObject  *bytestrides[2];
	PyObject  *convfunction;
	PyObject  *stridefunction;
	PyObject  *result_buff;
} PyConverterObject;


typedef struct {
	PyObject_HEAD
	PyObject *(*compute)(PyObject*,PyObject*,PyObject*);   /* Must match PyConverterObject */
	PyObject *inputs;
	PyObject *outputs;
	PyObject *cfunc;
	int      striding;
} PyOperatorObject;
 
#define PY_BOOL_CHAR "b"
#define PY_INT8_CHAR "b"
#define PY_INT16_CHAR "h"
#define PY_INT32_CHAR "i"
#define PY_FLOAT32_CHAR "f"
#define PY_FLOAT64_CHAR "d"
#define PY_UINT8_CHAR "h"
#define PY_UINT16_CHAR "i"
#define PY_UINT32_CHAR "i" /* Unless longer int available */
#define PY_COMPLEX64_CHAR "D"
#define PY_COMPLEX128_CHAR "D"

#define PY_LONG_CHAR "l"
#define PY_LONG_LONG_CHAR "L"

#define pyFPE_DIVIDE_BY_ZERO  1
#define pyFPE_OVERFLOW        2
#define pyFPE_UNDERFLOW       4
#define pyFPE_INVALID         8

#define isNonZERO(x) (x != 0) /* to convert values to boolean 1's or 0's */

typedef enum
{
	NUM_CONTIGUOUS=1,
	NUM_NOTSWAPPED=2,
	NUM_ALIGNED=4,
	NUM_WRITABLE=8,
	NUM_COPY=16,

	NUM_C_ARRAY  = (NUM_CONTIGUOUS | NUM_ALIGNED | NUM_NOTSWAPPED),
	NUM_UNCONVERTED = 0
} NumRequirements;

#define UNCONVERTED 0
#define C_ARRAY     (NUM_CONTIGUOUS | NUM_NOTSWAPPED | NUM_ALIGNED)

#define MUST_BE_COMPUTED 2   

#define NUM_FLOORDIVIDE(a,b,out) (out) = floor((a)/(b))

#define NA_Begin() Py_Initialize(); import_libnumarray();
#define NA_End()   NA_Done(); Py_Finalize();

#define NA_OFFSETDATA(num) ((void *) num->data)

/* unaligned NA_COPY functions */
#define NA_COPY1(i, o)  (*(o) = *(i))
#define NA_COPY2(i, o)  NA_COPY1(i, o), NA_COPY1(i+1, o+1)
#define NA_COPY4(i, o)  NA_COPY2(i, o), NA_COPY2(i+2, o+2)
#define NA_COPY8(i, o)  NA_COPY4(i, o), NA_COPY4(i+4, o+4)
#define NA_COPY16(i, o) NA_COPY8(i, o), NA_COPY8(i+8, o+8)

/* byteswapping macros: these fail if i==o */
#define NA_SWAP1(i, o)  NA_COPY1(i, o)
#define NA_SWAP2(i, o)  NA_SWAP1(i, o+1), NA_SWAP1(i+1, o)
#define NA_SWAP4(i, o)  NA_SWAP2(i, o+2), NA_SWAP2(i+2, o)
#define NA_SWAP8(i, o)  NA_SWAP4(i, o+4), NA_SWAP4(i+4, o)
#define NA_SWAP16(i, o) NA_SWAP8(i, o+8), NA_SWAP8(i+8, o)

/* complex byteswaps must swap each part (real, imag) independently */
#define NA_COMPLEX_SWAP8(i, o)  NA_SWAP4(i, o), NA_SWAP4(i+4, o+4)
#define NA_COMPLEX_SWAP16(i, o) NA_SWAP8(i, o), NA_SWAP8(i+8, o+8)

/* byteswapping macros:  these work even if i == o */
#define NA_TSWAP1(i, o, t) NA_COPY1(i, t), NA_SWAP1(t, o)
#define NA_TSWAP2(i, o, t) NA_COPY2(i, t), NA_SWAP2(t, o)
#define NA_TSWAP4(i, o, t) NA_COPY4(i, t), NA_SWAP4(t, o)
#define NA_TSWAP8(i, o, t) NA_COPY8(i, t), NA_SWAP8(t, o)

/* fast copy functions for %N aligned i and o */
#define NA_ACOPY1(i, o) (((Int8    *)o)[0]   = ((Int8    *)i)[0])
#define NA_ACOPY2(i, o) (((Int16   *)o)[0]   = ((Int16   *)i)[0])
#define NA_ACOPY4(i, o) (((Int32   *)o)[0]   = ((Int32   *)i)[0])
#define NA_ACOPY8(i, o) (((Float64 *)o)[0]   = ((Float64 *)i)[0])
#define NA_ACOPY16(i, o) (((Complex64 *)o)[0]   = ((Complex64 *)i)[0])

/* from here down, type("ai") is NDInfo*  */

#define NA_PTR(ai)   ((char *) NA_OFFSETDATA((ai)))
#define NA_TEMP(ai)  ((char *) &((ai)->temp))
#define NA_PTR1(ai, i)       (NA_PTR(ai) +                                   \
                              (i)*(ai)->strides[0])
#define NA_PTR2(ai, i, j)    (NA_PTR(ai) +                                   \
                              (i)*(ai)->strides[0] +                         \
                              (j)*(ai)->strides[1])
#define NA_PTR3(ai, i, j, k) (NA_PTR(ai) +                                   \
                              (i)*(ai)->strides[0] +                         \
                              (j)*(ai)->strides[1] +                         \
                              (k)*(ai)->strides[2])
#define NA_RESULT(ai, type)   (*((type *) NA_TEMP(ai)))


#define NA_SET_TEMP(ai, type, v) (((type *) &(ai)->temp)[0] = v)

#define NA_SWAPComplex64 NA_COMPLEX_SWAP16
#define NA_SWAPComplex32 NA_COMPLEX_SWAP8
#define NA_SWAPFloat64   NA_SWAP8
#define NA_SWAPFloat32   NA_SWAP4
#define NA_SWAPInt64     NA_SWAP8
#define NA_SWAPUInt64    NA_SWAP8
#define NA_SWAPInt32     NA_SWAP4
#define NA_SWAPUInt32    NA_SWAP4
#define NA_SWAPInt16     NA_SWAP2
#define NA_SWAPUInt16    NA_SWAP2
#define NA_SWAPInt8      NA_SWAP1
#define NA_SWAPUInt8     NA_SWAP1
#define NA_SWAPBool      NA_SWAP1

#define NA_COPYComplex64 NA_COPY16
#define NA_COPYComplex32 NA_COPY8
#define NA_COPYFloat64   NA_COPY8
#define NA_COPYFloat32   NA_COPY4
#define NA_COPYInt64     NA_COPY8
#define NA_COPYUInt64    NA_COPY8
#define NA_COPYInt32     NA_COPY4
#define NA_COPYUInt32    NA_COPY4
#define NA_COPYInt16     NA_COPY2
#define NA_COPYUInt16    NA_COPY2
#define NA_COPYInt8      NA_COPY1
#define NA_COPYUInt8     NA_COPY1
#define NA_COPYBool      NA_COPY1

#define NA_REM(ai, ptr)  ((ai)->wptr = (ptr))
#define NA_REC(ai)       ((ai)->wptr)

/* ========================== ptr get/set ================================ */

/* byteswapping */
#define NA_GETPb(ai, type, ptr)                                               \
         (NA_REM(ai, ptr), NA_SWAP##type(NA_REC(ai), NA_TEMP(ai)),            \
	  NA_RESULT(ai, type))        

/* aligning */
#define NA_GETPa(ai, type, ptr)                                               \
         (NA_REM(ai, ptr), NA_COPY##type(NA_REC(ai), NA_TEMP(ai)),            \
	  NA_RESULT(ai, type))

/* fast (aligned, !byteswapped) */
#define NA_GETPf(ai, type, ptr) (*((type *) (ptr)))

#define NA_GETP(ai, type, ptr)                                                \
   (PyArray_ISCARRAY(ai) ? NA_GETPf(ai, type, ptr)                            \
                   : (PyArray_ISBYTESWAPPED(ai) ?                             \
                                      NA_GETPb(ai, type, ptr)                 \
                                    : NA_GETPa(ai, type, ptr)))

/* NOTE:  NA_SET* macros cannot be used as values. */

/* byteswapping */
#define NA_SETPb(ai, type, ptr, v)                                            \
         (NA_REM(ai, ptr), NA_SET_TEMP(ai, type, v),                          \
	  NA_SWAP##type(NA_TEMP(ai), NA_REC(ai)))

/* aligning */
#define NA_SETPa(ai, type, ptr, v)                                            \
         (NA_REM(ai, ptr), NA_SET_TEMP(ai, type, v),                          \
          NA_COPY##type(NA_TEMP(ai), NA_REC(ai)))

/* fast (aligned, !byteswapped) */
#define NA_SETPf(ai, type, ptr, v) ((*((type *) ptr)) = (v))

#define NA_SETP(ai, type, ptr, v)                                             \
    if (PyArray_ISCARRAY(ai)) {                                               \
         NA_SETPf((ai), type, (ptr), (v));                                    \
    } else if (PyArray_ISBYTESWAPPED(ai)) {                                   \
	 NA_SETPb((ai), type, (ptr), (v));                                    \
    } else                                                                    \
         NA_SETPa((ai), type, (ptr), (v))

/* ========================== 1 index get/set ============================ */

/* byteswapping */
#define NA_GET1b(ai, type, i)    NA_GETPb(ai, type, NA_PTR1(ai, i))
/* aligning */
#define NA_GET1a(ai, type, i)    NA_GETPa(ai, type, NA_PTR1(ai, i))
/* fast (aligned, !byteswapped) */
#define NA_GET1f(ai, type, i)    NA_GETPf(ai, type, NA_PTR1(ai, i))
/* testing */
#define NA_GET1(ai, type, i)     NA_GETP(ai, type, NA_PTR1(ai, i))

/* byteswapping */
#define NA_SET1b(ai, type, i, v) NA_SETPb(ai, type, NA_PTR1(ai, i), v)
/* aligning */
#define NA_SET1a(ai, type, i, v) NA_SETPa(ai, type, NA_PTR1(ai, i), v)
/* fast (aligned, !byteswapped) */
#define NA_SET1f(ai, type, i, v) NA_SETPf(ai, type, NA_PTR1(ai, i), v)
/* testing */
#define NA_SET1(ai, type, i, v)  NA_SETP(ai, type,  NA_PTR1(ai, i), v)

/* ========================== 2 index get/set ============================= */

/* byteswapping */
#define NA_GET2b(ai, type, i, j)    NA_GETPb(ai, type, NA_PTR2(ai, i, j))
/* aligning */
#define NA_GET2a(ai, type, i, j)    NA_GETPa(ai, type, NA_PTR2(ai, i, j))
/* fast (aligned, !byteswapped) */
#define NA_GET2f(ai, type, i, j)    NA_GETPf(ai, type, NA_PTR2(ai, i, j))
/* testing */
#define NA_GET2(ai, type, i, j)     NA_GETP(ai, type, NA_PTR2(ai, i, j))

/* byteswapping */
#define NA_SET2b(ai, type, i, j, v) NA_SETPb(ai, type, NA_PTR2(ai, i, j), v)
/* aligning */
#define NA_SET2a(ai, type, i, j, v) NA_SETPa(ai, type, NA_PTR2(ai, i, j), v)
/* fast (aligned, !byteswapped) */
#define NA_SET2f(ai, type, i, j, v) NA_SETPf(ai, type, NA_PTR2(ai, i, j), v)

#define NA_SET2(ai, type, i, j,  v)  NA_SETP(ai, type,  NA_PTR2(ai, i, j), v)

/* ========================== 3 index get/set ============================= */

/* byteswapping */
#define NA_GET3b(ai, type, i, j, k)    NA_GETPb(ai, type, NA_PTR3(ai, i, j, k))
/* aligning */
#define NA_GET3a(ai, type, i, j, k)    NA_GETPa(ai, type, NA_PTR3(ai, i, j, k))
/* fast (aligned, !byteswapped) */
#define NA_GET3f(ai, type, i, j, k)    NA_GETPf(ai, type, NA_PTR3(ai, i, j, k))
/* testing */
#define NA_GET3(ai, type, i, j, k)     NA_GETP(ai, type, NA_PTR3(ai, i, j, k))

/* byteswapping */
#define NA_SET3b(ai, type, i, j, k, v)                                        \
        NA_SETPb(ai, type, NA_PTR3(ai, i, j, k), v)
/* aligning */
#define NA_SET3a(ai, type, i, j, k, v)                                        \
        NA_SETPa(ai, type, NA_PTR3(ai, i, j, k), v)
/* fast (aligned, !byteswapped) */
#define NA_SET3f(ai, type, i, j, k, v)                                        \
        NA_SETPf(ai, type, NA_PTR3(ai, i, j, k), v)
#define NA_SET3(ai, type, i, j, k, v)                                         \
        NA_SETP(ai, type,  NA_PTR3(ai, i, j, k), v)

/* ========================== 1D get/set ================================== */

#define NA_GET1Db(ai, type, base, cnt, out)                                   \
        { int i, stride = ai->strides[ai->nd-1];                              \
           for(i=0; i<cnt; i++) {                                             \
               out[i] = NA_GETPb(ai, type, base);                             \
               base += stride;                                                \
           }                                                                  \
        } 

#define NA_GET1Da(ai, type, base, cnt, out)                                   \
        { int i, stride = ai->strides[ai->nd-1];                              \
           for(i=0; i<cnt; i++) {                                             \
               out[i] = NA_GETPa(ai, type, base);                             \
               base += stride;                                                \
           }                                                                  \
        } 

#define NA_GET1Df(ai, type, base, cnt, out)                                   \
        { int i, stride = ai->strides[ai->nd-1];                              \
           for(i=0; i<cnt; i++) {                                             \
               out[i] = NA_GETPf(ai, type, base);                             \
               base += stride;                                                \
           }                                                                  \
        } 

#define NA_GET1D(ai, type, base, cnt, out)                                    \
        if (PyArray_ISCARRAY(ai)) {                                           \
	      NA_GET1Df(ai, type, base, cnt, out);                            \
        } else if (PyArray_ISBYTESWAPPED(ai)) {                               \
              NA_GET1Db(ai, type, base, cnt, out);                            \
        } else {                                                              \
              NA_GET1Da(ai, type, base, cnt, out);                            \
	}
        
#define NA_SET1Db(ai, type, base, cnt, in)                                    \
        { int i, stride = ai->strides[ai->nd-1];                              \
           for(i=0; i<cnt; i++) {                                             \
               NA_SETPb(ai, type, base, in[i]);                               \
               base += stride;                                                \
           }                                                                  \
        }

#define NA_SET1Da(ai, type, base, cnt, in)                                    \
        { int i, stride = ai->strides[ai->nd-1];                              \
           for(i=0; i<cnt; i++) {                                             \
               NA_SETPa(ai, type, base, in[i]);                               \
               base += stride;                                                \
           }                                                                  \
        }

#define NA_SET1Df(ai, type, base, cnt, in)                                    \
        { int i, stride = ai->strides[ai->nd-1];                              \
           for(i=0; i<cnt; i++) {                                             \
               NA_SETPf(ai, type, base, in[i]);                               \
               base += stride;                                                \
           }                                                                  \
        }

#define NA_SET1D(ai, type, base, cnt, out)                                    \
        if (PyArray_ISCARRAY(ai)) {                                           \
              NA_SET1Df(ai, type, base, cnt, out);                            \
        } else if (PyArray_ISBYTESWAPPED(ai)) {                               \
              NA_SET1Db(ai, type, base, cnt, out);                            \
        } else {                                                              \
	      NA_SET1Da(ai, type, base, cnt, out);                            \
	}
        
/* ========================== utilities ================================== */

#if !defined(MIN)
#define MIN(x,y) (((x)<=(y)) ? (x) : (y))
#endif

#if !defined(MAX)
#define MAX(x,y) (((x)>=(y)) ? (x) : (y))
#endif

#if !defined(ABS)
#define ABS(x) (((x) >= 0) ? (x) : -(x))
#endif

#define ELEM(x)  (sizeof(x)/sizeof(x[0]))

#define BOOLEAN_BITWISE_NOT(x) ((x) ^ 1)

#define NA_NBYTES(a) (a->descr->elsize * NA_elements(a))

#if defined(NA_SMP)
#define BEGIN_THREADS Py_BEGIN_ALLOW_THREADS
#define END_THREADS Py_END_ALLOW_THREADS
#else
#define BEGIN_THREADS
#define END_THREADS
#endif

#include "numconfig.h"

#define ADD_VERSION(m) \
	if (PyModule_AddObject(m, "__version__", \
            PyString_FromString(NUMARRAY_VERSION)) < 0) \
		return;

#if !defined(NA_isnan)

#define U32(u) (* (Int32 *) &(u) )
#define U64(u) (* (Int64 *) &(u) )

#define NA_isnan32(u) \
  ( (( U32(u) & 0x7f800000) == 0x7f800000)  && ((U32(u) & 0x007fffff) != 0)) ? 1:0

#if !defined(_MSC_VER)
#define NA_isnan64(u) \
  ( (( U64(u) & 0x7ff0000000000000LL) == 0x7ff0000000000000LL)  && ((U64(u) & 0x000fffffffffffffLL) != 0)) ? 1:0
#else
#define NA_isnan64(u) \
  ( (( U64(u) & 0x7ff0000000000000i64) == 0x7ff0000000000000i64)  && ((U64(u) & 0x000fffffffffffffi64) != 0)) ? 1:0
#endif

#define NA_isnanC32(u) (NA_isnan32(((Complex32 *)&(u))->r) || NA_isnan32(((Complex32 *)&(u))->i))
#define NA_isnanC64(u) (NA_isnan64(((Complex64 *)&(u))->r) || NA_isnan64(((Complex64 *)&(u))->i))

#endif /* NA_isnan */

#if  PY_VERSION_HEX < 0x02030000
#define PyBool_FromLong PyInt_FromLong
#endif

#endif /* _ndarraymacro */
