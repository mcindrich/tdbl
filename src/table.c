#include <tdb/table.h>
#include <string.h>
#include <stdlib.h>

void tdb_table_create(struct tdb_table_t *table)
{
        table->name = NULL;
        tdb_column_list_create(&table->columns);
}

void tdb_table_set_name(struct tdb_table_t *table, const char *name)
{
        const count_t len = strlen(name);
        if(table->name)
        {
                free(table->name);
        }
        table->name = (char *) malloc(sizeof(char) * (len + 1));
        memcpy(table->name, name, len);
        table->name[len] = 0;
}

void tdb_table_parse(struct tdb_table_t *table, byte_t **data) 
{
        // max name len = 255 chars
        count_t len = 0;

        memcpy(&len, *data, sizeof(len));
        *data += sizeof(len);

        table->name = (char *) malloc(sizeof(char) * (len + 1));
        memcpy(table->name, *data, sizeof(char) * len);
        
        *data += sizeof(char) * len;

        table->name[len] = 0;

        tdb_column_list_parse(&table->columns, data);
        // create columns for a table
        // ...
}

void tdb_table_delete(struct tdb_table_t *table)
{
        if(table->name)
        {
                free(table->name);
                tdb_column_list_delete(&table->columns);
        }
}