#ifndef __TDB_column_LIST_H__
#define __TDB_column_LIST_H__

#include <tdb/column.h>

struct tdb_column_list_t
{
        struct tdb_column_t *data;
        count_t count;
        count_t size;
};

void tdb_column_list_create(struct tdb_column_list_t *);
void tdb_column_list_parse(struct tdb_column_list_t *, byte_t **);
void tdb_column_list_add(struct tdb_column_list_t *, struct tdb_column_t *);
void tdb_column_list_delete(struct tdb_column_list_t *);

#endif