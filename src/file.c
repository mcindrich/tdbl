#include <tdb/file.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void tdb_file_create(struct tdb_file_t *file)
{
        tdb_db_list_create(&file->dbs);
}

void tdb_file_parse(struct tdb_file_t *file, const char *name) 
{
        byte_t *data = NULL, *bkp_data;
        size_t fsize = 0;
        FILE* f = fopen(name, "rb");

        if(f)
        {
                fseek(f, 0, SEEK_END);
                fsize = ftell(f);
                fseek(f, 0, SEEK_SET);
                
                data = (char *) malloc(sizeof(char) * (fsize + 1));
                bkp_data = data;

                fread(data, sizeof(char), fsize, f);

                fclose(f);

                tdb_header_parse(&file->header, &data);
                tdb_db_list_parse(&file->dbs, &data);

                free(bkp_data);
        }
        else 
        {
                // error opening file
        }
}

void tdb_file_write(struct tdb_file_t *file, const char *fn)
{
        // open the FILE and pass the fptr to other types to write to it
        count_t len, i, j, k;
        size_t l;

        struct tdb_db_t *temp_db;
        struct tdb_table_t *temp_table;
        struct tdb_column_t *temp_col;
        void *temp_val;

        FILE* f = fopen(fn, "wb");

        if(f)
        {
                fwrite(&file->header, sizeof(file->header), 1, f);
                fwrite(&file->dbs.count, sizeof(file->dbs.count), 1, f);
                for(i = 0; i < file->dbs.count; i++)
                {
                        temp_db = &file->dbs.data[i];
                        len = strlen(temp_db->name);
                        fwrite(&len, sizeof(len), 1, f);
                        fwrite(temp_db->name, sizeof(char), len, f);
                        fwrite(&temp_db->tables.count,
                                sizeof(temp_db->tables.count), 1, f);
                        for(j = 0; j < temp_db->tables.count; j++)
                        {
                                temp_table = &file->dbs.data[i].tables.data[j];
                                len = strlen(temp_table->name);
                                fwrite(&len, sizeof(len), 1, f);
                                fwrite(temp_table->name, sizeof(char), len, f);
                                fwrite(&temp_table->columns.count, 
                                        sizeof(temp_table->columns.count), 
                                        1, f);
                                for(k = 0; k < temp_table->columns.count; k++)
                                {
                                        temp_col = &temp_table->columns.data[k];
                                        len = strlen(temp_col->name);
                                        fwrite(&len, sizeof(len), 1, f);
                                        fwrite(temp_col->name, sizeof(char), 
                                                len, f);
                                        fwrite(&temp_col->values.type, 
                                                sizeof(temp_col->values.type), 
                                                1, f);
                                        fwrite(&temp_col->values.count, 
                                                sizeof(temp_col->values.count),
                                                1, f);
                                        for(l = 0; l < temp_col->values.count;
                                                l++)
                                        {
                                                temp_val = tdb_value_list_get(
                                                        &temp_col->values, l);
                                                switch(temp_col->values.type)
                                                {
                                                case tdb_values_type_null:
                                                        break;
                                                case tdb_values_type_int:
                                                        fwrite(temp_val, 
                                                                sizeof(int), 
                                                                1, f);
                                                        break;
                                                case tdb_values_type_string:
                                                        len = strlen(
                                                                TDB_VALUE2STRING
                                                                (temp_val));
                                                        fwrite(&len, 
                                                                sizeof(len), 
                                                                1, f);
                                                        fwrite(TDB_VALUE2STRING
                                                                (temp_val), 
                                                                sizeof(char), 
                                                                len, f);
                                                        break;
                                                case tdb_values_type_double:
                                                        fwrite(temp_val, 
                                                                sizeof(double), 
                                                                1, f);
                                                        break;
                                                }
                                        }
                                }
                        }
                }
                fclose(f);
        }
        else
        {
                fprintf(stderr, "Unable to open file '%s'.\n", fn);
        }
}

void tdb_file_delete(struct tdb_file_t *file)
{
        tdb_db_list_delete(&file->dbs);       
}

