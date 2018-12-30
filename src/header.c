#include <tdb/header.h>
#include <string.h>

void tdb_header_parse(struct tdb_header_t *head, byte_t **data)
{
        memset(head->ID, 0, 4);
        head->ver.major = 0;
        head->ver.minor = 0;

        memcpy(head, *data, sizeof(*head));
        *data += sizeof(*head);
}