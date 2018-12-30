#ifndef __TDB_TABLE_LIST_H__
#define __TDB_TABLE_LIST_H__

#include <tdb/table.h>
#include <stddef.h>

struct tdb_table_list_t
{
        struct tdb_table_t *data;
        count_t count;
        count_t size;
};

void tdb_table_list_create(struct tdb_table_list_t *);
void tdb_table_list_parse(struct tdb_table_list_t *, byte_t **);
void tdb_table_list_add(struct tdb_table_list_t *, struct tdb_table_t *);
void tdb_table_list_delete(struct tdb_table_list_t *);

#endif