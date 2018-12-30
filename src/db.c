#include <tdb/db.h>
#include <string.h>
#include <stdlib.h>

void tdb_db_create(struct tdb_db_t *db)
{
        db->name = NULL;
        tdb_table_list_create(&db->tables);
}

void tdb_db_set_name(struct tdb_db_t *db, const char *name)
{
        const count_t len = strlen(name);
        if(db->name)
        {
                free(db->name);
        }
        db->name = (char *) malloc(sizeof(char) * (len + 1));
        memcpy(db->name, name, len);
        db->name[len] = 0;
}

void tdb_db_parse(struct tdb_db_t *db, byte_t **data)
{
        // max name len = 255 chars
        count_t len = 0;

        memcpy(&len, *data, sizeof(len));
        *data += sizeof(len);

        db->name = (char *) malloc(sizeof(char) * (len + 1));
        memcpy(db->name, *data, sizeof(char) * len);
        
        *data += sizeof(char) * len;

        db->name[len] = 0;

        tdb_table_list_parse(&db->tables, data);
}

void tdb_db_delete(struct tdb_db_t *db)
{
        if(db->name)
        {
                free(db->name);
        }
        tdb_table_list_delete(&db->tables);
}
