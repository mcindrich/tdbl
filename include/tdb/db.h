#ifndef __TDB_DB_H__
#define __TDB_DB_H__

#include <tdb/table-list.h>

struct tdb_db_t 
{
        char *name;
        struct tdb_table_list_t tables;
};

void tdb_db_create(struct tdb_db_t *);
void tdb_db_set_name(struct tdb_db_t *, const char *);
void tdb_db_parse(struct tdb_db_t *, byte_t **);
void tdb_db_delete(struct tdb_db_t *);

#endif
