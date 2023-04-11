#pragma once

#include <stdlib.h>

#define TYPE_ARG_FMT "%s"


typedef char* elem_t;

const size_t POISON         = 0;
const size_t BASED_CAPACITY = 10;
const size_t FREEE          = 31415;
const size_t MAX_STR_SIZE   = 20;

enum ListStatus
{
    LIST_STATUS_OK          = 0 << 0,
    LIST_NULL_PTR           = 1 << 0,
    LIST_DATA_NULL_PTR      = 1 << 1,
    CAN_NOT_ALLOCATE_MEMORY = 1 << 2,
    LIST_IS_DESTRUCTED      = 1 << 3,
    LIST_IS_EMPTY           = 1 << 4,
    BAD_RESIZE              = 1 << 5,
    BAD_CAPACITY            = 1 << 6,
    LIST_UB                 = 1 << 7,
    BAD_INSERT              = 1 << 8,
    BAD_REMOVE              = 1 << 9,
    EXTRA_ELEM_RUINED       = 1 << 10,
    SIZE_MORETHAN_CAPACITY  = 1 << 11,
    TOO_LONG_TAIL           = 1 << 12,
    TOO_BIG_HEAD            = 1 << 13,
    TOO_MUCH_FREEDOM        = 1 << 14,
    RUINED_HEAD             = 1 << 15,
    RUINED_TAIL             = 1 << 16,
    BAD_INDEX               = 1 << 17, 
    LIST_RUINED             = 1 << 18,
};

struct node_t
{
    size_t    prev;
    elem_t    value;
    size_t    next;
};

struct list_t
{
    node_t* data;
    size_t  head;
    size_t  tail;
    size_t  freeHead;
    size_t  size;
    size_t  capacity;
    bool    isSorted;
    int     status;
};

enum CapacityMode
{
    DOWN = 0,
    UP   = 1,
};

enum EditMode
{
    BEFORE = 0,
    AFTER  = 1,
};

enum DoLinear
{
    NO_SORT = 0, 
    SORT    = 1,
};

int ListCtor(list_t* list, size_t capacity);
int ListDtor(list_t* list);
node_t* ListResize(list_t* list, CapacityMode capMode, DoLinear linearMode = NO_SORT);
size_t ListTail(list_t* list);
size_t ListHead(list_t* list);
size_t ListPrev(list_t* list, size_t physIndex);
size_t ListNext(list_t* list, size_t physIndex);
size_t ReturnPhysicalIndexFromLogicalButItIsBetterIfYouSaveIndexesInOtherPlace(list_t* list, size_t logIndex);
int ListIsEmpty(list_t* list);
int ListIsDestructed(list_t* list);
int ListLinearize(list_t *list);
size_t ListInsertAfter(list_t *list, size_t physIndex, elem_t value);
size_t ListInsertBefore(list_t *list, size_t physIndex, elem_t value);
size_t ListInsertTail(list_t* list, elem_t value);
size_t ListInsertHead(list_t* list, elem_t value);
elem_t ListRemove(list_t* list, size_t physIndex);
elem_t ListRemoveTail(list_t* list);
elem_t ListRemoveHead(list_t* list);
size_t FindElemByValue(list_t* list, elem_t value);
int ListVerify(list_t* list);
int ListTotalCleaning(list_t* list);
