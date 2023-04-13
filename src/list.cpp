#include "../include/list.hpp"

int ListCtor(list_t* list, size_t capacity)
{
    if (list     == NULL) return LIST_NULL_PTR;
    if (capacity == 0   ) return BAD_CAPACITY;
    
    capacity = (capacity / BASED_CAPACITY + 1) * BASED_CAPACITY;

    list->data = (node_t*) calloc(capacity + 1, sizeof(node_t));
    if (list->data == NULL) return CAN_NOT_ALLOCATE_MEMORY;

    list->head     = 1;
    list->tail     = 1;
    list->freeHead = 1;
    list->size     = 0;
    list->isSorted = true;
    list->capacity = capacity;
    
    for (size_t index = 1; index < list->capacity; ++index)
    {
        list->data[index].prev = FREEE;
        list->data[index].next = index + 1;
    }

    list->data[list->capacity].prev  = FREEE;
    list->data[list->capacity].next  = 0;
    

    return LIST_STATUS_OK;
}

int ListDtor(list_t* list)
{
    if (list                   == NULL              ) return LIST_NULL_PTR;
    if (ListIsDestructed(list) == LIST_IS_DESTRUCTED) return LIST_IS_DESTRUCTED;
    
    free(list->data);

    list->head     = POISON;
    list->tail     = POISON;
    list->freeHead = POISON;
    list->size     = 0;
    list->capacity = POISON;

    return LIST_IS_DESTRUCTED;
}

int ListIsDestructed(list_t* list)
{
    if (list == NULL) return LIST_NULL_PTR;
    
    if (list->head == POISON && list->tail     == POISON && list->freeHead == POISON &&
        list->size == POISON && list->capacity == POISON)
        return LIST_IS_DESTRUCTED;
    
    return LIST_UB;
}

int ListIsEmpty(list_t* list)
{
    if (list == NULL) return LIST_NULL_PTR;
    
    if (list->head == 1 && list->tail == 1 && list->freeHead == 1 &&
        list->size == 0)
        return LIST_IS_EMPTY;

    return LIST_UB;
}

size_t ReturnPhysicalIndexFromLogicalButItIsBetterIfYouSaveIndexesInOtherPlace(list_t* list, size_t logIndex)
{
    if (list == NULL || logIndex == 0 || logIndex > list->capacity) return size_t (-1);

    if (list->isSorted)
        return list->head - 1 + logIndex;
    
    size_t phys  = list->head;
    size_t index = 1;

    while (index < logIndex) 
    {
        phys = list->data[phys].next;
        index++;
    }

    return phys;
}

size_t ListHead(list_t* list)
{
    return list->head;
}

size_t ListTail(list_t* list)
{
    return list->tail;
}

size_t ListNext(list_t* list, size_t physIndex)
{
    if (physIndex == 0)
        return POISON;

    return list->data[physIndex].next;
}

size_t ListPrev(list_t* list, size_t physIndex)
{
    if (physIndex == 0)
        return POISON;

    return list->data[physIndex].prev;
}

size_t ListInsertAfter(list_t *list, size_t physIndex, elem_t value)
{
    if (physIndex == 0)
    {
        //printf("%s\n", value);
        //printf("%lu\n", list->capacity);
    }
    
    if (physIndex > list->capacity          ||
       (list->data[physIndex].prev == FREEE &&         
       (list->size != 0 || physIndex != list->tail))) //if user want to insert after free node
    {
        return BAD_INSERT;
    }
   
    if (physIndex == 0)
        printf("%s\n", value);

    node_t* dataptr = ListResize(list, UP);
    if (dataptr == NULL)
    {
        list->status |= BAD_INSERT;
        return 0;
    }
    
    list->data = dataptr;
    
    size_t elemIndex = 0;

    if (list->data[list->data[physIndex].next].prev == physIndex)
    {
        list->isSorted = false;
    }
    
    if (list->size == 0)
    {
        elemIndex = list->tail;

        list->freeHead = list->data[list->freeHead].next;

        list->data[list->tail].value = value;
        list->data[list->tail].next  = 0;
        list->data[list->tail].prev  = 0;
        
    }
    else if (physIndex == list->tail) //if insert after tail
    {
        elemIndex = list->freeHead;

        if (list->freeHead != list->tail + 1)
        {
            list->isSorted = false;
        }

        list->data[list->freeHead].prev  = list->tail;
        list->data[list->freeHead].value = value; 
        list->data[list->tail].next      = list->freeHead;
        list->tail                       = list->freeHead;

        size_t oldFreeHead = list->freeHead;

        list->freeHead               = list->data[oldFreeHead].next;
        list->data[oldFreeHead].next = 0; 
    }
    else //if insert after element in body
    {  
        elemIndex   = list->freeHead;

        size_t newFreeHead = list->data[list->freeHead].next;

        list->data[list->freeHead].next  = list->data[physIndex].next;
        list->data[list->freeHead].prev  = physIndex;
        list->data[list->freeHead].value = value;

        list->data[list->data[list->freeHead].prev].next = list->freeHead;
        list->data[list->data[list->freeHead].next].prev = list->freeHead;

        list->isSorted = false; 
        list->freeHead = newFreeHead;

    }

    ++list->size;
    
    return elemIndex;
}

size_t ListInsertBefore(list_t *list, size_t physIndex, elem_t value)
{
    if (list == NULL) return 0;

    if (physIndex == 0 || physIndex >= list->capacity)
    {
        return BAD_INSERT;
    }

   size_t elemIndex = 0;

    node_t* dataptr = ListResize(list, UP);
    if (dataptr == NULL)
    {
        list->status |= BAD_INSERT;
        return 0;
    }
    
    list->data = dataptr;
    
    if (list->size == 0)
        elemIndex = ListInsertAfter(list, physIndex, value);

    if (physIndex == list->head)
    {
        size_t newFreeHead = list->data[list->freeHead].next;

        list->data[list->head].prev      = list->freeHead;
        list->data[list->freeHead].next  = list->head;
        list->data[list->freeHead].prev  = 0;
        list->data[list->freeHead].value = value;

        list->head     = list->freeHead;
        list->freeHead = newFreeHead;
    
        ++list->size;
        
        elemIndex = list->head;
    }
    else
    {
       elemIndex = ListInsertAfter(list, list->data[physIndex].prev, value);
    }
    
    return elemIndex;
}

elem_t ListRemove(list_t* list, size_t physIndex)
{
    elem_t value = 0;
    
    if (list->size == 0)
    {
        list->status |= BAD_REMOVE;
        return nullptr;
    }

    if (physIndex == list->head)
    {
        if (physIndex == list->tail)
        {
            value = list->data[physIndex].value;
                
            list->data[physIndex].prev  = FREEE;
            list->data[physIndex].next  = list->freeHead;
            list->data[physIndex].value = 0;
            list->freeHead              = physIndex;
        }
        else
        {
            value           = list->data[physIndex].value;
            size_t newHead  = list->data[list->head].next;

            list->data[list->head].prev  = FREEE;
            list->data[list->head].value = 0;
            list->data[list->head].next  = list->freeHead;
            
            list->freeHead = physIndex;
            list->head     = newHead;
        }
    }
    else if (physIndex == list->tail)
    {
        value           = list->data[physIndex].value;
        size_t newTail  = list->data[list->tail].prev;

        list->data[list->tail].prev  = FREEE;
        list->data[list->tail].value = 0;
        list->data[list->tail].next  = list->freeHead;
        
        list->freeHead              = physIndex;
        list->tail                  = newTail;
        list->data[list->tail].next = 0;
    }
    else
    {
        value = list->data[physIndex].value;

        size_t next = list->data[physIndex].next;
        size_t prev = list->data[physIndex].prev;
    
        list->data[physIndex].prev  = FREEE;
        list->data[physIndex].next  = list->freeHead;
        list->data[physIndex].value = 0;

        list->freeHead = physIndex;

        list->data[next].prev = prev;
        list->data[prev].next = next;

        list->isSorted = false;

    } 
    
    --list->size;

    if (list->isSorted)
    {
        node_t* dataptr = ListResize(list, DOWN);
        if (dataptr == NULL)
        {
            list->status |= BAD_REMOVE;
            return nullptr;
        }

        list->data = dataptr;
    }

    return value;
}

node_t* ListResize(list_t* list, CapacityMode capMode, DoLinear linearMode)
{
    if (list == NULL) return NULL;
   

    size_t updCapacity = 0;
    
    if (capMode == UP)
    {
        if (list->size >= list->capacity)
        {
            updCapacity = list->capacity * 2;
        }
        else
            return list->data;
        
        if (linearMode && (list->isSorted == false))
        {   
            if (ListLinearize(list))
                return NULL;
        }
 
        node_t* dataptr = (node_t *) realloc(list->data, (1 + updCapacity) * sizeof(node_t));
        if (dataptr == NULL)
        {
            list->status |= BAD_RESIZE | CAN_NOT_ALLOCATE_MEMORY;
            return NULL;
        }

        size_t updFree = list->capacity + 1;
        size_t fHead   = list->freeHead;

        while (dataptr[fHead].next != 0)
        {
            fHead = list->data[fHead].next;
        }

        if (fHead == list->freeHead)
            list->freeHead = updFree;
        else
            dataptr[fHead].next = updFree;

        for (size_t index = updFree; index < updCapacity; ++index)
        {
            dataptr[index].prev  = FREEE;
            dataptr[index].next  = index + 1;
            dataptr[index].value = 0;
        }

        dataptr[updCapacity].next  = 0;
        dataptr[updCapacity].prev  = FREEE;
        dataptr[updCapacity].value = 0;


        list->capacity = updCapacity;
        
        return dataptr;
    }

    else if (capMode == DOWN)
    {
        if (list->capacity > BASED_CAPACITY && list->size <= list->capacity * 3 / 8)
        {
            updCapacity = list->capacity / 2;
        }
        else
            return list->data;
 
        if (linearMode && (list->isSorted == false || (list->isSorted == true && list->tail > updCapacity)))
        {   
            if (ListLinearize(list))
                return NULL;
        }

        list->freeHead = 0;

        for (size_t index = updCapacity; index >= 1; --index)
        {
            if (list->data[index].prev == FREEE)
            {
                if (list->freeHead == 0)
                {
                    list->freeHead         = index;
                    list->data[index].next = 0;
                }
                else
                {
                    list->data[index].next = list->freeHead;
                    list->freeHead         = index;
                }
            }
        }

        node_t* dataptr = (node_t*) realloc(list->data, (1 + updCapacity) * sizeof(node_t));
        if (dataptr == NULL)
        {
            list->status |= BAD_RESIZE | CAN_NOT_ALLOCATE_MEMORY;
            return NULL;
        }

        list->capacity = updCapacity;

        return dataptr;
    }

    list->status |= BAD_RESIZE;


    return NULL;
}

int ListLinearize(list_t *list)
{
    if (list == NULL) return LIST_NULL_PTR;
    

    node_t* dataptr = (node_t*) calloc(1 + list->capacity, sizeof(node_t));
    if (dataptr == NULL) return CAN_NOT_ALLOCATE_MEMORY;

    size_t ptr = list->head;

    if (list->size == 0)
        ptr = 0;

    list->freeHead = 0;

    for (size_t index = 1; index <= list->capacity; ++index)
    {
        if (ptr != 0)
        {
            dataptr[index].prev  = (index == 1          ? 0 : index - 1);
            dataptr[index].next  = (index == list->size ? 0 : index + 1);
            dataptr[index].value = list->data[ptr].value;
        }
        else
        {
            if (list->freeHead == 0) 
                list->freeHead = index;
            
            dataptr[index].prev  = FREEE;
            dataptr[index].next  = (index == list->capacity ? 0 : index + 1);
        }

        ptr = list->data[ptr].next;
    }

    free(list->data);

    list->isSorted = true;
    list->head     = 1;
    list->tail     = (list->size == 0 ? 1 : list->size);
    list->data     = dataptr;


    return LIST_STATUS_OK;
}

size_t ListInsertTail(list_t* list, elem_t value)
{
    return ListInsertAfter(list, ListTail(list), value);
}

size_t ListInsertHead(list_t* list, elem_t value)
{
    return ListInsertBefore(list, ListHead(list), value);
}

elem_t ListRemoveTail(list_t* list)
{
    return ListRemove(list, ListTail(list));
}

elem_t ListRemoveHead(list_t *list)
{
    return ListRemove(list, ListHead(list));
}

size_t FindElemByValue(list_t* list, elem_t value)
{

    size_t physIndex = list->head;

    while (physIndex != 0 && list->data[physIndex].value != value)
    {
        physIndex = list->data[physIndex].next;
    }

    return physIndex;
}

int ListTotalCleaning(list_t* list)
{
    if (list == NULL)
        return LIST_NULL_PTR;


    if (ListIsEmpty(list) == LIST_IS_EMPTY)
        return LIST_IS_EMPTY;
    
    while (list->size != 0)
        ListRemoveTail(list);
    
    list->status |= LIST_IS_EMPTY;

    return LIST_STATUS_OK;
}

int ListVerify(list_t* list)
{
    if (list == NULL)                                 return LIST_NULL_PTR;
    
    if (ListIsEmpty(list) == LIST_IS_EMPTY)           return LIST_IS_EMPTY;

    if (ListIsDestructed(list) == LIST_IS_DESTRUCTED) return LIST_IS_DESTRUCTED;

    int status = LIST_STATUS_OK;

    if (list->size > list->capacity)
        status |= SIZE_MORETHAN_CAPACITY;

    if (list->tail > list->capacity)
        status |= TOO_LONG_TAIL;

    if (list->head > list->capacity)
        status |= TOO_BIG_HEAD;

    if (list->freeHead > list->capacity)
        status |= TOO_MUCH_FREEDOM;

    if (list->data == NULL) 
        status |= LIST_DATA_NULL_PTR;
    
    if (status)
    {
        list->status = status;
        return status;
    }

    if (list->data[0].next != 0 &&
        list->data[0].prev != 0 &&
        list->data[0].value != 0)
    {
        status |= EXTRA_ELEM_RUINED;
    }

    if (list->tail != list->head && list->data[list->head].prev != 0)
        status |= RUINED_HEAD;
    
    if (list->tail != list->head && list->data[list->tail].next != 0)
        status |= RUINED_TAIL;

    if (status)
    {
        list->status = status;
        return status;
    }
    
    for (size_t index = 1; index <= list->capacity; ++index)
    {
        if (list->data[index].next > list->capacity ||
            (list->data[index].prev != FREEE && list->data[index].prev > list->capacity))
        {
            status |= BAD_INDEX;
            break;
        }
    }

    size_t curIndex = list->head;
    size_t size     = 0;

    while (size <= list->capacity)
    {
        if (list->data[curIndex].next == 0)
        {
            if (curIndex != list->capacity && curIndex != list->tail)
            {
                status |= BAD_INDEX;
            }

            ++size;
            break;
        }
        else if (list->data[list->data[curIndex].next].prev != FREEE    &&
                (list->data[list->data[curIndex].next].prev != curIndex ||
                (list->data[curIndex].prev != 0                         && 
                 list->data[list->data[curIndex].prev].next != curIndex)))
        {
            status |= BAD_INDEX;
            break;
        }

        curIndex = list->data[curIndex].next;
        ++size;
    }

    curIndex = list->freeHead;

    while (size < list->capacity && curIndex != 0)
    {
        if (list->data[curIndex].next == 0)
        {
            if (list->data[curIndex].prev  != FREEE)
            {
                status |= LIST_RUINED;
            }

            ++size;
            break;
        }
        else if (list->data[curIndex].prev != FREEE)
        {

            status |= LIST_RUINED;
            break;
        }
        
        curIndex = list->data[curIndex].next;
        ++size;
    }

    if (size != list->capacity)
    {
        status |= LIST_RUINED;
    }
    
    list->status = status;

    return status;
}

