#ifndef __TDB_TABLE_H__
#define __TDB_TABLE_H__

#include <tdb/column-list.h>

struct tdb_table_t
{
        char *name;
        struct tdb_column_list_t columns;
};

void tdb_table_create(struct tdb_table_t *);
void tdb_table_set_name(struct tdb_table_t *, const char *);
void tdb_table_parse(struct tdb_table_t *, byte_t **);
void tdb_table_delete(struct tdb_table_t *);

#endif