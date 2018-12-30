#include <tdb/table-list.h>
#include <string.h>
#include <stdlib.h>

void tdb_table_list_create(struct tdb_table_list_t *tl)
{
        tl->data = NULL;
        tl->count = tl->size = 0;
}

void tdb_table_list_parse(struct tdb_table_list_t *tl, byte_t **data)
{
        count_t i = 0;

        memcpy(&tl->count, *data, sizeof(tl->count));
        tl->data = malloc(sizeof(struct tdb_table_t) * tl->count);

        *data += sizeof(tl->count);

        for(i = 0; i < tl->count; i++)
        {
                tdb_table_parse(&tl->data[i], data);
        }
        tl->size = tl->count;
}

void tdb_table_list_add(struct tdb_table_list_t *tables, 
        struct tdb_table_t *table)
{
        if(tables->count == tables->size)
        {
                tables->size += TDB_LIST_UPDATE_SIZE;
                tables->data = (struct tdb_table_t *) realloc(tables->data, 
                        sizeof(struct tdb_table_t) * tables->size);
        }
        tables->data[tables->count] = *table;
        ++tables->count;
}

void tdb_table_list_delete(struct tdb_table_list_t *tl)
{
        count_t i;
        if(tl->count)
        {
                for(i = 0; i < tl->count; i++)
                {
                        tdb_table_delete(&tl->data[i]);
                }
                free(tl->data);
                tl->count = tl->size = 0;
        }
}