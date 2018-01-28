static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/bt_new.c,v 0.87.2.1 2000/02/05 06:13:07 magrasjc Exp $";
/*
   Original code from "Practical Algorithms for Programmers"
   by Andrew Binstock and John Rex
*/
#include "bt_hdr.h"

/*
 * Create new dataset files. Files are not left open
 *
 * Dataset has one record in it, a record with the maximum key
 * that will ever be used. We populate each index level with
 * this one key and create one data block containing this record.
 */
int bt_new(Btree *bt, void *maxkey, void *maxrec)
{
    char *buffer, *s;
    int i, ret;
    unsigned length, j;
    DISKOFFSET tmp;
    BLKSIZE blksize;
    BlockControl *bc;

    /* Check values, allocate buffers */
    ret = TREE_OK;
    for (i=0; i < 2; i++) {
        if (SIZES(i,block_size) > 10000) { /* seems unlikely */
            bt -> error_code = 2;
            ret = TREE_FAIL;
            break;
        }

        if (SIZES(i,split) > SIZES(i,block_size) ||
            SIZES(i,merge) > SIZES(i,block_size)) {
            bt -> error_code = 3;
            ret = TREE_FAIL;
            break;
        }

        ret = bt_bufinit(bt, i);
        if (ret)
            break;

        /* Open the file */
        bt->fdata[i].file = fopen(bt->fdata[i].filename, "wb");
        if (bt->fdata[i].file == NULL) {
            bt -> error_code = 1;
            ret = TREE_FAIL;
            break;
        }

        /* Steal access to a buffer & initialize file */
        buffer = s = bt->fdata[i].bufferlist->buffer;
        blksize = SIZES(i, block_size);
        memset(buffer, 0, blksize);

        /* Signature string */
        strcpy(s, SIGNATURE);
        strcat(s, i == NDX ? SIG_INDEX : SIG_DATA);
        s += strlen(s) + 1;

        /* Buffer size information */
        memcpy (s, &(bt->fdata[i].sizes), sizeof(Sizes)); 

        /* Offsets to root block and some free blocks */
        s += sizeof(Sizes);

        memcpy (s, &blksize, sizeof (DISKOFFSET));
        memset (s+sizeof(DISKOFFSET), 0, sizeof(DISKOFFSET));

        if (fwrite(buffer, blksize, 1, bt->fdata[i].file) != 1) {
            bt -> error_code = 4;
            ret = TREE_FAIL;
            break;
        }

        memset(buffer, 0, blksize);
        bc = (BlockControl *) buffer;
        bc -> bfree = sizeof(BlockControl);
        bc -> next       = 0L;

        if (i == NDX) {
            /* create a block of maxkey/offset */
            bc -> blockstate = sNode;
            s = buffer + bc -> bfree;
            length = GETKEYSIZE(maxkey);
            memcpy(s, maxkey, length);
            s += length;
            bc -> bfree += length + sizeof(DISKOFFSET);

            /* write out levels blocks,
                                    each pointing to the next */
            for (j = 1; j <= SIZES(i, levels); j++) {
                bc -> parent = (DISKOFFSET) blksize * (j - 1);

                tmp = blksize * (j + 1);
                memcpy (s, &tmp, sizeof (DISKOFFSET));

                /* last block points to data file */
                if (j == SIZES(i, levels)) {
                    bc -> blockstate = sLeaf;

                    tmp = SIZES(DAT, block_size);
                    memcpy (s, &tmp, sizeof (DISKOFFSET));
                }
                if (fwrite(buffer, blksize, 1, bt->fdata[i].file) != 1) {
                                
                    bt -> error_code = 4;
                    ret = TREE_FAIL;
                    break;
                }
            }
        }
        else /* i == DAT */ {
            /* create a block with one entry: maxrec */
            bc -> blockstate = sLeaf;
            bc -> parent = (DISKOFFSET) SIZES(NDX, block_size) *
                                        SIZES(NDX, levels);
            s = buffer + bc -> bfree;
            length = GETRECSIZE(maxrec);
            memcpy(s, maxrec, length);
            bc -> bfree += length;
            if (fwrite(buffer, blksize, 1, bt->fdata[i].file) != 1) {
                                
                bt -> error_code = 4;
                ret = TREE_FAIL;
                break;
            }
        }
        fclose(bt->fdata[i].file);
        bt->fdata[i].file = NULL;

        if (ret)
            break;
    }

    bt_bufrelease(bt, NDX);
    bt_bufrelease(bt, DAT);
    return ret;
}
