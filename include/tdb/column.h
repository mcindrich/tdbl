#ifndef __TDB_column_H__
#define __TDB_column_H__

#include <tdb/value-list.h>

struct tdb_column_t
{
        char *name;
        struct tdb_value_list_t values;
};

void tdb_column_create(struct tdb_column_t *);
void tdb_column_set_name(struct tdb_column_t *, const char *);
void tdb_column_parse(struct tdb_column_t *, byte_t **);
void tdb_column_delete(struct tdb_column_t *);

#endif