#include <tdb/value-list.h>
#include <stdlib.h>
#include <string.h>

void tdb_value_list_create(struct tdb_value_list_t *values, 
        enum tdb_values_type_t type)
{
        values->data = 0;
        values->count = values->size = 0;
        values->type = type;
}

void tdb_value_list_parse(struct tdb_value_list_t *values, 
        enum tdb_values_type_t type, byte_t **data)
{
        size_t i = 0;
        // for now string value size will be unsigned char ==> 255 chars
        count_t inc = 0, temp_str_size;

        values->type = type;
        memcpy(&values->count, *data, sizeof(values->count));

        switch(type)
        {
        case tdb_values_type_null:
                break;
        case tdb_values_type_int:
                values->data = malloc(sizeof(int) * values->count);
                break;
        case tdb_values_type_string:
                values->data = malloc(sizeof(char *) * values->count);
                break;
        case tdb_values_type_double:
                values->data = malloc(sizeof(double) * values->count);
                break;
        }

        *data += sizeof(values->count);

        for(i = 0; i < values->count; i++)
        {
                switch(type)
                {
                case tdb_values_type_null:
                        break;
                case tdb_values_type_int:
                        memcpy(((int *)values->data + i), *data, sizeof(int));
                        inc = sizeof(int);
                        break;
                case tdb_values_type_string:
                        memcpy(&temp_str_size, *data, sizeof(temp_str_size));
                        *data += sizeof(temp_str_size);
                        *((char **)values->data + i) = malloc(sizeof(char) * 
                                (temp_str_size + 1));
                        memcpy(*((char **)values->data + i), *data, 
                                temp_str_size);
                        *(*((char **)values->data + i) + temp_str_size) = 0;
                        inc = sizeof(char) * temp_str_size;
                        break;
                case tdb_values_type_double:
                        memcpy(((double *)values->data + i), *data, sizeof(double));
                        inc = sizeof(double);
                        break; 
                }
                *data += inc;
        }
        values->size = values->count;
}

void tdb_value_list_add(struct tdb_value_list_t *values, void *value)
{
        // len if the value is a string
        count_t len;

        if(values->count == values->size)
        {
                values->size += TDB_LIST_UPDATE_SIZE;
                switch(values->type)
                {
                case tdb_values_type_null:
                        break;
                case tdb_values_type_int:
                        values->data = realloc(values->data, 
                                sizeof(int) * values->size);
                        break;
                case tdb_values_type_string:
                        values->data = realloc(values->data, 
                                sizeof(char *) * values->size);
                        break;
                case tdb_values_type_double:
                        values->data = realloc(values->data, 
                                sizeof(double) * values->size);    
                        break; 
                }
        }
        switch(values->type)
        {
        case tdb_values_type_null:
                break;
        case tdb_values_type_int:
                *((int*)values->data + values->count) = *((int *)value); 
                break;
        case tdb_values_type_string:
                len = strlen((char *)value);

                *((char **)values->data + values->count) = malloc(sizeof(char) * 
                        (len + 1));
                memcpy(*((char **)values->data + values->count), value, 
                        len);
                *(*((char **)values->data + values->count) + len) = 0;
                break;
        case tdb_values_type_double:
                *((double*)values->data + values->count) = *((double *)value);   
                break; 
        }
        ++values->count;
}

void *tdb_value_list_get(struct tdb_value_list_t *values, size_t pos)
{
        void *ret = NULL;
        if(pos < values->count)
        {
                switch(values->type)
                {
                case tdb_values_type_null:
                        break;
                case tdb_values_type_int:
                        ret = ((int *)values->data + pos);
                        break;
                case tdb_values_type_string:
                        ret = ((char **)values->data + pos);
                        break;
                case tdb_values_type_double:
                        ret = ((double *)values->data + pos);  
                        break;
                }
        }
        return ret;
}

void tdb_value_list_delete(struct tdb_value_list_t *values)
{
        size_t i;

        if(values->count)
        {
                if(values->type == tdb_values_type_string)
                {
                        for(i = 0; i < values->count; i++)
                        {
                                free(*((char **)values->data + i));
                        }
                }
                free(values->data);
                values->count = values->size = 0;
        }
}