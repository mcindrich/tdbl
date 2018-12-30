#include <tdb/column.h>
#include <stdlib.h>
#include <string.h>

void tdb_column_create(struct tdb_column_t *column)
{
        column->name = NULL;
        tdb_value_list_create(&column->values, tdb_values_type_null);
}

void tdb_column_set_name(struct tdb_column_t *column, const char *name)
{
        const count_t len = strlen(name);
        if(column->name)
        {
                free(column->name);
        }
        column->name = (char *) malloc(sizeof(char) * (len + 1));
        memcpy(column->name, name, len);
        column->name[len] = 0;
}

void tdb_column_parse(struct tdb_column_t *column, byte_t **data)
{
        count_t len = 0;
        enum tdb_values_type_t type;

        memcpy(&len, *data, sizeof(len));
        *data += sizeof(len);

        column->name = (char *) malloc(sizeof(char) * (len + 1));
        memcpy(column->name, *data, sizeof(char) * len);
        
        *data += sizeof(char) * len;
        column->name[len] = 0;

        // get values type ==> int, string, double...

        memcpy(&type, *data, sizeof(type));
        *data += sizeof(type);

        tdb_value_list_parse(&column->values, type, data);
}

void tdb_column_delete(struct tdb_column_t *column)
{
        if(column->name)
        {
                free(column->name);
                tdb_value_list_delete(&column->values);
        }
}