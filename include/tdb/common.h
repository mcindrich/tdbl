#ifndef __tdb_COMMON_H__
#define __tdb_COMMON_H__

typedef signed char s8_t;
typedef unsigned char u8_t;
typedef char byte_t;
typedef unsigned char count_t;
typedef unsigned long string_len_t;

enum tdb_values_type_t
{
        tdb_values_type_null,
        tdb_values_type_int,
        tdb_values_type_string,
        tdb_values_type_double
};

#define TDB_LIST_UPDATE_SIZE 8

#define TDB_VALUE2INT(vptr) (*((int *)vptr))
#define TDB_VALUE2DOUBLE(vptr) (*((double *)vptr))
#define TDB_VALUE2STRING(vptr) (*((char **)vptr))

#endif
