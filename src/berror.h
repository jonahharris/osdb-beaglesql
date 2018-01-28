/*
 
 berror.h
     
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


#define GENERAL 0
#define IDLENGTH 1
#define OPENING_PAREN 2
#define BADID 3
#define CLOSING_PAREN 4
#define BADFIELDTYPE 5
#define INCOMPLETE 6
#define CANTDROP 7
#define VALUES_EXPECTED 8
#define GETTABLE 9
#define MEMORY 10
#define BAD_DELIMITER 11
#define TABLENOTFOUND 12
#define AMBIGUOUS_FIELD 13
#define KEYWORD_EXPECTED_ON 14
#define KEYWORD_EXPECTED_USING 15
#define INVALID_FIELD 16
#define READONLY_TABLE 17

#define MAXIDSIZE 256
#define MAX_ERROR_LENGTH 81
#define ERROR -999
#define TIMEOUT -999
