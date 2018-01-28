static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/bt_open.c,v 0.87.2.1 2000/02/05 06:13:08 magrasjc Exp $";
/*
   Original code from "Practical Algorithms for Programmers"
   by Andrew Binstock and John Rex
*/

#include "bt_hdr.h"

#if defined(HELP1)
#define SHOW(x) x
#else
#define SHOW(x)
#endif

/* Open files, allocate buffers */
int bt_open(Btree *bt)
{
    int i, ret;
    char buffer[512], *s;

    /* Check values, allocate buffers */
    ret = TREE_OK;
    for (i=0; i < 2; i++) {
        bt->fdata[i].file = fopen(bt->fdata[i].filename, "r+b");
        if (bt->fdata[i].file == NULL) {
            bt -> error_code = 6;
            ret = TREE_FAIL;
            break;
        }
        bt->fdata[i].modified = 0;
        SHOW(printf("bt_open file: %s, file: %Fp\n",
                        bt->fdata[i].filename, bt->fdata[i].file);)

        if (fread(buffer, 512, 1, bt->fdata[i].file) != 1) {
            bt -> error_code = 7;
            ret = TREE_FAIL;
            break;
        }

        s = buffer;
        if (strcmp(s, i == NDX ?
                   SIGNATURE SIG_INDEX : SIGNATURE SIG_DATA)) {
            bt -> error_code = 8;
            ret = TREE_FAIL;
            break;
        }

        s += strlen(s) + 1;
        memcpy (&(bt->fdata[i].sizes), s, sizeof(Sizes));
        s += sizeof(Sizes);
        memcpy (&(bt->fdata[i].root_block), s, sizeof(long));
        s += sizeof(long);
        memcpy (&(bt->fdata[i].free_block), s, sizeof(long));

        ret = bt_bufinit(bt, i);
        if (ret)
            break;
    }

    return ret;
}

/* Flush buffers and shut down */
int bt_close(Btree *bt)
{
    int i, ret;

    ret = bt_flush(bt);
    for (i=0; i<2; i++) {
        if (bt->fdata[i].file) {
            if (fclose(bt->fdata[i].file)) {
                bt -> error_code = 9;
                ret = TREE_FAIL;
            }
            bt->fdata[i].file = NULL;
        }
        bt_bufrelease(bt, i);
    }

    return ret;
}
