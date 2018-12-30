#ifndef __TDB_VALUE_LIST_H__
#define __TDB_VALUE_LIST_H__

#include <stddef.h>
#include <tdb/common.h>

// count is size_t ==> there can be a large number of values in the column

struct tdb_value_list_t
{
        void *data;
        size_t count;
        size_t size;
        enum tdb_values_type_t type;
};

void tdb_value_list_create(struct tdb_value_list_t *, enum tdb_values_type_t);
void tdb_value_list_parse(struct tdb_value_list_t *, enum tdb_values_type_t, 
        byte_t **);
void tdb_value_list_add(struct tdb_value_list_t *, void *);
void *tdb_value_list_get(struct tdb_value_list_t *, size_t );
void tdb_value_list_delete(struct tdb_value_list_t *);

#endif