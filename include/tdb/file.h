#ifndef __TDB_FILE_H__
#define __TDB_FILE_H__

#include <tdb/header.h>
#include <tdb/db-list.h>

struct tdb_file_t
{
        struct tdb_header_t header;
        struct tdb_db_list_t dbs;
};

void tdb_file_create(struct tdb_file_t *);
void tdb_file_parse(struct tdb_file_t *, const char *);

// write databases to the file
void tdb_file_write(struct tdb_file_t *, const char *);
void tdb_file_delete(struct tdb_file_t *);

#endif