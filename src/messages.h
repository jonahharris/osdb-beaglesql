/*
 
 messages.h
     
 Copyright (c) 1996 Robert Klein

 Permission to use, copy, modify and distribute this software and its
 documentation, is hereby granted to educational institutions, their
 faculty, and full-time students, non-commercial research organizations,
 registered charities, and registered not-for-profit and non-profit
 organizations without fee provided that this license agreement and
 copyright information appears in all copies.

 Permission to use this software by any other person or organization 
 is hereby granted for the current version of the software and it's
 documentation provided that this license agreement and copyright
 information appears in all copies.
 
 Commercial redistribution of this software, by itself or as part of
 another application is allowed only under express written permission of
 Robert Klein and may entail licensing fees.
 
 ROBERT KLEIN DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
 INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO 
 EVENT SHALL ROBERT KLEIN BE LIABLE FOR ANY SPECIAL, INDIRECT OR 
 CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF 
 USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR 
 OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR 
 PERFORMANCE OF THIS SOFTWARE.
 
*/


/* Messages sent to the server from the beagle library functions */
#define CMDSIZE 1
#define LENSIZE 10

#define MSG_BEGIN       "a"
#define MSG_END         "b"
#define MSG_SETDB       "c"
#define MSG_GETDB       "d"
#define MSG_QUERY       "e"
#define MSG_FIRSTFIELD  "f"
#define MSG_NEXTFIELD   "g"
#define MSG_FIRSTTUPLE  "h"
#define MSG_NEXTTUPLE   "i"
#define MSG_GETNTUPLES  "j"
#define MSG_GETNFIELDS  "k"
#define MSG_EXIT        "l"
