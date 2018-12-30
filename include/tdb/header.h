#ifndef __TDB_HEADER_H__
#define __TDB_HEADER_H__

#include <tdb/common.h>

struct tdb_version_t 
{
        u8_t minor;
        u8_t major;
};

struct tdb_header_t
{
        char ID[4];
        struct tdb_version_t ver;
};

void tdb_header_parse(struct tdb_header_t *, byte_t **);

#endif
