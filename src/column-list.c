#include <tdb/column-list.h>
#include <stdlib.h>
#include <string.h>

void tdb_column_list_create(struct tdb_column_list_t *columns)
{
        columns->data = NULL;
        columns->count = columns->size = 0;
}

void tdb_column_list_parse(struct tdb_column_list_t *columns, byte_t **data)
{
        count_t i = 0;

        memcpy(&columns->count, *data, sizeof(columns->count));
        columns->data = malloc(sizeof(struct tdb_column_t) * columns->count);

        *data += sizeof(columns->count);

        for(i = 0; i < columns->count; i++)
        {
                tdb_column_parse(&columns->data[i], data);
        }
        columns->size = columns->count;
}

void tdb_column_list_add(struct tdb_column_list_t *columns, 
        struct tdb_column_t *column)
{
        if(columns->count == columns->size)
        {
                columns->size += TDB_LIST_UPDATE_SIZE;
                columns->data = (struct tdb_column_t *) realloc(columns->data, 
                        sizeof(struct tdb_column_t) * columns->size);
        }
        columns->data[columns->count] = *column;
        ++columns->count;
}

void tdb_column_list_delete(struct tdb_column_list_t *columns)
{
        count_t i = 0;

        if(columns->count)
        {
                for(i = 0; i < columns->count; i++)
                {
                        tdb_column_delete(&columns->data[i]);
                }
                free(columns->data);
                columns->count = columns->size = 0;
        }
}