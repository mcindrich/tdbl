#include <tdb/db-list.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void tdb_db_list_create(struct tdb_db_list_t *dbs)
{
        dbs->data = NULL;
        dbs->count = dbs->size = 0;
}

void tdb_db_list_parse(struct tdb_db_list_t *dbs, byte_t **data)
{
        count_t i;

        memcpy(&dbs->count, *data, sizeof(dbs->count));
        *data += sizeof(dbs->count);

        dbs->data = (struct tdb_db_t *) malloc(sizeof(struct tdb_db_t) * 
                dbs->count);
        for(i = 0; i < dbs->count; i++)
        {
                // get all databases
                // NAME_LEN -> NAME -> TABLE_COUNT -> TABLES
                tdb_db_parse(&dbs->data[i], data);
        }
        dbs->size = dbs->count;
}

void tdb_db_list_add(struct tdb_db_list_t *dbs, struct tdb_db_t *db)
{
        if(dbs->count == dbs->size)
        {
                dbs->size += TDB_LIST_UPDATE_SIZE;
                dbs->data = (struct tdb_db_t *) realloc(dbs->data, 
                        sizeof(struct tdb_db_t) * dbs->size);
        }
        dbs->data[dbs->count] = *db;
        ++dbs->count;
}

void tdb_db_list_write(struct tdb_db_list_t *dbs, FILE *file)
{

}

void tdb_db_list_delete(struct tdb_db_list_t *dbs)
{
        if(dbs->count)
        {
                count_t i;
                for(i = 0; i < dbs->count; i++)
                {
                        tdb_db_delete(&dbs->data[i]);
                }
                free(dbs->data);
                dbs->count = dbs->size = 0;
        }
}
