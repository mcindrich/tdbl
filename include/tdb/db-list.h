#ifndef __TDB_DB_LIST_H__
#define __TDB_DB_LIST_H__

#include <tdb/db.h>
#include <tdb/common.h>
#include <stdio.h> // FILE *
#include <stddef.h>

struct tdb_db_list_t
{
        struct tdb_db_t *data;
        count_t count;
        count_t size;
};

void tdb_db_list_create(struct tdb_db_list_t *);
void tdb_db_list_parse(struct tdb_db_list_t *, byte_t **);
void tdb_db_list_add(struct tdb_db_list_t *, struct tdb_db_t *);
void tdb_db_list_delete(struct tdb_db_list_t *);

#endif
