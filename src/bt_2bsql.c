static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/bt_2bsql.c,v 0.87.2.1 2000/02/05 06:13:02 magrasjc Exp $";
/*
   Original code from "Practical Algorithms for Programmers"
   by Andrew Binstock and John Rex
*/
#include "bt_hdr.h"
#include <ctype.h>
#include "bt_2bsql.h"
#include "log.h"

void bt_driver (int action, char *inbuf);

/*#define TESTSIZES*/ /* use small block limits to force splits */

/*
 * A record with a maximal key
 */
UR MaxRec = { "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff", 0L };

/*
 * The support routines that the btree routines call
 */
unsigned UserGetKeySize(void *k) {
    return strlen( (char *) k ) + 1;
}

unsigned UserGetKeyNRecSize(void *k) {
    return strlen( ((UR *) k) -> key ) + 1;
}

unsigned UserGetRecSize(void *r) {
    return sizeof(UR);
}

int UserKey2KeyCmp(void *k1, void *k2) {
    return strncmp((char *) k1, (char *) k2, strlen(k1));
}

int UserKey2RecCmp(void *k, void *r) {
    return strncmp((char *) k, ((UR *) r)->key, strlen (k));
}

void UserRec2KeyCpy(void *rec, void *key) {
    strcpy((char *) key, ((UR *) rec) -> key);
}

/*
 * Some tree display routines
 */
char *BlockStates[] = { "sAvail", "sNode", "sLeaf" };
BLKSIZE index_blksize;
FILE *outfile;

/*
 * Given index block is at given level. Display contents
 * and then recursively examine the children.
 */
void prefix(int level) {
    for (; level; level--) fprintf(outfile, " * ");
}

void walk_down(Btree *bt, int f, DISKOFFSET block,
                int level, int mode) {
    char *s, *key;
    BlockControl *bc;
    unsigned offset, keysize, keycount = 0;
    DISKOFFSET *pDof;

    prefix(level);
    if (f == NDX)
        fprintf(outfile,
                "Level %d index block %ld at offset %ld.",
                level, block/index_blksize, block);
    else
        fprintf(outfile, "Data block %ld at offset %ld.",
                          block/SIZES(DAT, block_size), block);

    if (mode)
        fprintf(outfile, "\n");

    s = bt_getblock4read(bt, f, block);
    if (!s) {
        bt->error_code = 7;
        return;
    }

    bc = (BlockControl *) s;

    if (mode) {
        prefix(level);
        fprintf(outfile,
           "blockstate: %s, free data: "
           "%d, parent: %ld, next: %ld\n",
           BlockStates[bc->blockstate],
           bc->bfree,
           bc->parent,
           bc->next);
    }

    if (f == NDX) {
        offset = sizeof(BlockControl);
        while (offset < bc->bfree) {
            keysize = GETKEYSIZE(s + offset);
            key = s + offset;
            pDof = (DISKOFFSET *) (key + keysize);
            if (mode) {
                prefix(level);
                fprintf(outfile,
                       "Offset %d: key '%s', DISKOFFSET %ld\n",
                        offset, key, *pDof);
            }
            offset += keysize + sizeof(DISKOFFSET);
            keycount++;
        }
        if (!mode)
            fprintf(outfile, " %u entries\n", keycount);

        offset = sizeof(BlockControl);
        while (offset < bc->bfree) {
            keysize = GETKEYSIZE(s + offset);
            walk_down(bt,
                      bc->blockstate == sLeaf ? DAT : NDX,
                      *((DISKOFFSET *) (s + offset + keysize)),
                      level + 1, mode);

            /* recursive calls may invalidate our buffer */
            s = bt_getblock4read(bt, f, block);
            bc = (BlockControl *) s;
            offset += keysize + sizeof(DISKOFFSET);
        }
    }
    else { /* f == DAT */
        offset = sizeof(BlockControl);
        while (offset < bc->bfree) {
            keysize = GETRECSIZE(s + offset);
            if (mode) {
                prefix(level);
                fprintf(outfile,
                    "Offset %d: key '%s', offset: %ld\n",
                    offset,
                       ((UR *) (s + offset))->key,
                       ((UR *) (s + offset))->offset);
            }
            offset += keysize;
            keycount++;
        }
        if (!mode)
            fprintf(outfile, " %u entries\n", keycount);
    }
}

/*
 * Sample display function
 */
int DataCount = 0;
int DisplayFunc(Btree *bt, void *rec) {
    UR *ur;
    ur = (UR *) rec;
    fprintf(outfile, "k:'%-10s', o:'%ld'\n",
                      ur->key, ur->offset);
    DataCount++;
    return TREE_OK;
}

/*
 * Make a new dataset
 */
int make_dataset(char *name)
{
    Btree bt;
    int retval;
    /*
     * Fill in parts of the structure. For the sizes, we
     * give what we want. The only real restriction is that
     * block_size - split must leave enough room to insert
     * the largest possible record or key.
     */
    strcpy(bt.fdata[NDX].filename, name);
    strcat(bt.fdata[NDX].filename, ".ndx");
    bt.fdata[NDX].modified = 0;
    bt.fdata[NDX].bufferlist = NULL;
    bt.fdata[NDX].sizes.block_size = (unsigned) 2048;
    #if defined(TESTSIZES)
    bt.fdata[NDX].sizes.split      = (unsigned) 80;
    bt.fdata[NDX].sizes.merge      = (unsigned) 45;
    #else
    bt.fdata[NDX].sizes.split      = (unsigned) 2000; /* room for one key */
    bt.fdata[NDX].sizes.merge      = (unsigned) 1024;
    #endif
    bt.fdata[NDX].sizes.levels     = (unsigned) 4;

    strcpy(bt.fdata[DAT].filename, name);
    strcat(bt.fdata[DAT].filename, ".dat");
    bt.fdata[DAT].modified = 0;
    bt.fdata[DAT].bufferlist = NULL;
    bt.fdata[DAT].sizes.block_size  = (unsigned) 4096;
    #if defined(TESTSIZES)
    bt.fdata[DAT].sizes.split       = (unsigned) 500;
    bt.fdata[DAT].sizes.merge       = (unsigned) 300;
    #else
    bt.fdata[DAT].sizes.split       = (unsigned) 3950; /* room for a rec */
    bt.fdata[DAT].sizes.merge       = (unsigned) 2048;
    #endif
    bt.fdata[DAT].sizes.levels      = (unsigned) 0; /* any value is OK */

    bt.getkeysize     = UserGetKeySize; /* user.c */
    bt.getkeyNrecsize = UserGetKeyNRecSize;
    bt.getrecsize     = UserGetRecSize;
    bt.key2keycmp     = UserKey2KeyCmp;
    bt.key2reccmp     = UserKey2RecCmp;
    bt.rec2keycpy     = UserRec2KeyCpy;

    bt.error_code   = 0;
    bt.duplicatesOK = 1;

    retval = bt_new(&bt, MaxRec.key, &MaxRec);
    if(retval == TREE_OK)
        lprintf("BT: Data files created");
    else
        lprintf("BT: Create failed: %s",
                ErrorText[bt.error_code]);

    return retval;
}

/*
 * Open a dataset
 */
Btree *open_dataset(char *name)
{
	Btree *bt;

	bt = malloc(sizeof(Btree));
	if (!bt)
		return NULL;

	strcpy(bt->fdata[NDX].filename, name);
	strcat(bt->fdata[NDX].filename, ".ndx");
	bt->fdata[NDX].bufferlist = NULL;

	strcpy(bt->fdata[DAT].filename, name);
	strcat(bt->fdata[DAT].filename, ".dat");
	bt->fdata[DAT].bufferlist = NULL;

    bt->getkeysize     = UserGetKeySize; /* user.c */
    bt->getkeyNrecsize = UserGetKeyNRecSize;
    bt->getrecsize     = UserGetRecSize;
    bt->key2keycmp     = UserKey2KeyCmp;
    bt->key2reccmp     = UserKey2RecCmp;
    bt->rec2keycpy     = UserRec2KeyCpy;

	bt->error_code = 0;
	bt->duplicatesOK = 1;

	if (bt_open(bt)) {
        lprintf("BT: Open failed: %s",
				ErrorText[bt->error_code]);
		free(bt);
		bt = NULL;
	}
    else
        lprintf("BT: Opened");
	return bt;
}


/*
 * A sample driver
 */
int DoData(Btree *bt, char *buffer, int mode) {

    UR ur;
    char *s;

    s = strchr(buffer, ';');
    if (!s) {
        if (mode != 0)
          return TREE_FAIL; /* trying to add partial data */
    }
    else
        *s++ = '\0';

    strcpy(ur.key, buffer); /* key is first 10 characters */

    if (mode == 0)
        return bt_delete(bt, ur.key);
    else {
        ur.offset = atol (s);
        return bt_add(bt, &ur, ur.key);
    }
}

void bt_driver (int action, char *inbuf)
{
    static Btree *bt = NULL;
    UR record;

    if (!bt && strchr("adf", action)) {
        lprintf("BT: **no open dataset");
        return;
    }

    switch (action) {

        case 'a':
            if (DoData(bt, inbuf, 1) == TREE_FAIL)
                lprintf("BT: ** Insertion failed");
            else
                lprintf("BT: Insertion Successfull");
            break;

        case 'u':

            if (inbuf[0] == '0' || inbuf[0] == '1')
                bt -> duplicatesOK = inbuf[0] == '0' ? 0 : 1;
            break;

        case 'd':

            if (DoData(bt, inbuf, 0) == TREE_FAIL)
                lprintf("BT: ** Delete failed");
            break;

        case 'f':

            if (bt_find(bt, &record, inbuf) == TREE_FAIL)
                lprintf("BT: ** Find failed");
            else
                lprintf("BT: found %s;%ld", record.key, record.offset);
            break;

        case 'n':
            make_dataset(inbuf);
            break;

        case 'o':

            if (bt) {
                if (bt_close(bt))
                    lprintf("BT: Close failed: %s", ErrorText[bt->error_code]);
                else
                    lprintf("BT: Data files closed.");
                bt = NULL;
            }
            bt = open_dataset(inbuf);
            break;

        case 'q':

            if (bt) {
                if (bt_close(bt))
                    lprintf("BT: Close failed: %s", ErrorText[bt->error_code]);
                else
                    lprintf("BT: Data files closed");
            }
            return;

        default:
            lprintf("BT: Not a valid command");
            break;
    }
    if (bt && bt->error_code) {
        lprintf("BT: ERROR: %s", ErrorText[bt->error_code]);
        bt->error_code = 0;
    }
}
