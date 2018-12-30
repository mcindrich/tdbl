#include <tdb.h>
#include <stdio.h>
#include <stdlib.h>

void write_file()
{
        struct tdb_version_t ver;
        ver.major = 1;
        ver.minor = 0;
        count_t dbs = 1, table_count = 1, column_count = 1;
        count_t temp_len = 5, table_name_len = 5, column_name_len = 2, tstr_size = 5;
        size_t num_of_values = 3000;
        enum tdb_values_type_t id_type = tdb_values_type_string;

        const char *tsrt = "value";

        FILE* file = fopen("examples/example.tdb", "wb");

        int *arr = (int *) malloc(sizeof(int) * num_of_values), i;

        for(i = 0; i < num_of_values; i++)
        {
                arr[i] = i+1;
        }

        fwrite("TDBL", sizeof(char), 4, file);
        fwrite(&ver, sizeof(ver), 1, file);
        fwrite(&dbs, sizeof(dbs), 1, file);

        fwrite(&temp_len, sizeof(temp_len), 1, file);
        fwrite("ex_db", sizeof(char), temp_len, file);

        fwrite(&table_count, sizeof(table_count), 1, file);

        fwrite(&table_name_len, sizeof(table_name_len), 1, file);
        fwrite("ex_tb", sizeof(char), table_name_len, file);

        fwrite(&column_count, sizeof(column_count), 1, file);

        fwrite(&column_name_len, sizeof(column_name_len), 1, file);
        fwrite("ID", sizeof(char), column_name_len, file);

        fwrite(&id_type, sizeof(id_type), 1, file);
        fwrite(&num_of_values, sizeof(num_of_values), 1, file);

        //fwrite(arr, sizeof(int), num_of_values, file);
        for(i = 0; i < num_of_values; i++)
        {
                fwrite(&tstr_size, sizeof(tstr_size), 1, file);
                fwrite(tsrt, sizeof(char), tstr_size, file);
        }

        free(arr);
        fclose(file);
}

int main(int argc, char *argv[]) 
{
        //write_file();
        struct tdb_file_t file;
        tdb_file_create(&file);
        tdb_file_parse(&file, argv[1]);

        //tdb_file_execute_query(&file, "get * from ex_tb", func_ptr); ==> plan
        tdb_file_write(&file, argv[1]);
        /*struct tdb_value_list_t *list = &file.dbs.data[0].tables.data[0].columns.data[0].values;
        int i = 0;
        for(i = 0; i < list->count; i++)
        {
                void *val = tdb_value_list_get(list, i);
                printf("String: %s\n", TDB_VALUE2STRING(val));
        }*/
        tdb_file_delete(&file);
        return 0;
}
