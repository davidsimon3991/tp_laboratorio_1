#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ArrayList.h"

// funciones privadas
int resizeUp(ArrayList*);
int expand(ArrayList* this,int index);
int contract(ArrayList* this,int index);

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10
//___________________

/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void)
{
    ArrayList* this;
    ArrayList* returnAux = NULL;
    void* pElements;
    this = (ArrayList *)malloc(sizeof(ArrayList));

    if(this != NULL)
    {
        pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );
        if(pElements != NULL)
        {
            this->size=0;
            this->pElements=pElements;
            this->reservedSize=AL_INITIAL_VALUE;
            this->add=al_add;
            this->len=al_len;
            this->set=al_set;
            this->remove=al_remove;
            this->clear=al_clear;
            this->clone=al_clone;
            this->get=al_get;
            this->contains=al_contains;
            this->push=al_push;
            this->indexOf=al_indexOf;
            this->isEmpty=al_isEmpty;
            this->pop=al_pop;
            this->subList=al_subList;
            this->containsAll=al_containsAll;
            this->deleteArrayList = al_deleteArrayList;
            this->sort = al_sort;
            returnAux = this;
        }
        else
        {
            free(this);
        }
    }

    return returnAux;
}


/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* pList,void* pElement)
{
    int returnAux = -1;
    if(pList!=NULL && pElement!=NULL)
    {
        if(resizeUp(pList)==0)
        {
            pList->pElements[pList->size]=pElement;
            pList->size+=1;
            returnAux=0;
        }
    }
    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* this)
{
    int returnAux = -1;
    if(this !=NULL)
    {
        free(this);
        returnAux=0;
    }

    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [pList is NULL pointer]
 *
 */
int al_len(ArrayList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        returnAux= this->size;
    }

    return returnAux;
}


/** \brief  Get an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [pList is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* this, int index)
{
    void* returnAux = NULL;
    if(this !=NULL)
    {
        if(index < this->size && index >=0)
        {
            returnAux=this->pElements[index];
        }

    }

    return returnAux;
}


/** \brief  Find if pList contains at least one element pElement
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL && pElement!=NULL)
    {
        for(int i=0; i<(this->size); i++)
        {
            returnAux=0;
            if(*(this->pElements+i)==pElement)
            {
                returnAux = 1;
                break;
            }
        }

    }

    return returnAux;
}


/** \brief  Set a element in pList at index position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* this, int index,void* pElement)
{
    int returnAux = -1;
    if((this!=NULL && pElement!=NULL)&&index>=0)
    {
        if(index==this->size)
        {
            if(this->add(this,pElement)==0)
            {
                returnAux=0;
            }
        }
        else
        {
            if(index < this->size)
            {
                this->pElements[index]=pElement;
                returnAux=0;
            }
        }
    }

    return returnAux;
}


/** \brief  Remove an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* this,int index)
{
    int returnAux = -1;
    if(this!=NULL && this->pElements!=NULL)
    {
        if(index < this->size && index>=0)
        {
            if(contract(this,index)==0)
            {
                returnAux = 0;
            }
        }
    }
    return returnAux;
}



/** \brief Removes all of the elements from this list
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* this)
{
    int returnAux = -1;
    if(this !=NULL && this->pElements!=NULL)
    {
        free(this->pElements);
        this->size=0;
        this->reservedSize = AL_INITIAL_VALUE;
        this->pElements=(void**)malloc(sizeof(void*)*AL_INITIAL_VALUE);
        returnAux=0;
    }

    return returnAux;
}



/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* this)
{
    ArrayList* returnAux = NULL;
<<<<<<< HEAD
    void* aux=NULL;

    if(this != NULL)
    {
        returnAux = al_newArrayList();
        if(returnAux!=NULL)
        {
            for(int i = 0; i< this->size; i++)
            {
                if(resizeUp(returnAux)==0)
                {
                    aux = this->get(this,i);
                    returnAux->add(returnAux,aux);
                }
            }
        }
    }
=======
>>>>>>> 16519056a874d9ff6db07831aa32c9324d00035b

    return returnAux;
}




/** \brief Inserts the element at the specified position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* this, int index, void* pElement)
{
    int returnAux=-1;
    if(this!=NULL && pElement!=NULL && index>=0)
    {
        if(index==this->size)
        {
            if(this->add(this,pElement)==0)
            {
                returnAux=0;
            }
        }
        else
        {
            if(index<this->size)
            {
                if(expand(this,index)==0)
                {
                    if(this->set(this,index,pElement)==0)
                    {
                        returnAux=0;
                    }
                }
            }
        }
    }
    return returnAux;
}



/** \brief Returns the index of the first occurrence of the specified element
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL && pElement!=NULL)
    {
        for(int i= 0; i< this->size; i++)
        {
            if(pElement== this->pElements[i])
            {
                returnAux=i;
            }
        }
    }


    return returnAux;
}



/** \brief Returns true if this list contains no elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        if(this->len(this)==0)
        {
            returnAux=1;
        }
        else
        {
           returnAux=0;
        }
    }

    return returnAux;
}




/** \brief Remove the item at the given position in the list, and return it.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* this,int index)
{
    void* returnAux = NULL;
    if(this!=NULL)
    {
        if(index < this->size &&index >=0)
        {
            returnAux = *(this->pElements+index);
            contract(this,index);
        }
    }

    return returnAux;
}


/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* this,int from,int to)
{
<<<<<<< HEAD
    ArrayList* returnAux = NULL;
    void* aux=NULL;

    if(this !=NULL && from >=0 && (to >=from && to <=this->size))
    {
        returnAux = al_newArrayList();
        if(returnAux!=NULL)
        {
            for(int i = from; i < to; i++)
            {
                if(resizeUp(returnAux)==0)
                {
                    aux = this->get(this,i);
                    returnAux->add(returnAux,aux);
                }
            }
        }
    }
=======
    void* returnAux = NULL;
>>>>>>> 16519056a874d9ff6db07831aa32c9324d00035b

    return returnAux ;
}





/** \brief Returns true if pList list contains all of the elements of pList2
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
<<<<<<< HEAD
int al_containsAll(ArrayList* pList,ArrayList* pList2)
{
    int returnAux = -1;
    int cont=0;

    if(pList!=NULL && pList2!=NULL)
    {
        for(int i=0; i<pList->size; i++)
        {
            for(int j=0; j<pList2->size; j++)
            {
                if(pList->pElements[i] == pList2->pElements[j])
                {
                    cont++;
                }
            }
        }
        if(cont == pList2->size)
        {
            returnAux=1;
        }
        else
        {
            returnAux=0;
        }
    }
=======
int al_containsAll(ArrayList* this,ArrayList* this2)
{
    int returnAux = -1;

>>>>>>> 16519056a874d9ff6db07831aa32c9324d00035b
    return returnAux;
}

/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */

int al_sort(ArrayList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux = -1;
    void* elementAux=NULL;
    void* pElementA;
    void* pElementB;
    int i,j;
    if(this!=NULL && pFunc!=NULL && (order==1 || order==0))
    {
        for(i=0;i<this->size-1;i++)
        {
            for(j=i+1;j<this->size;j++)
            {
                pElementA=this->get(this,i);
                pElementB=this->get(this,j);
                if(order==1)
                {
                    if(pFunc(pElementA,pElementB)==1)
                    {
                        elementAux=this->pElements[i];
                        this->pElements[i]=this->pElements[j];
                        this->pElements[j]=elementAux;
                    }
                }
                else
                {
                    if(pFunc(pElementA,pElementB)==-1)
                    {
                        elementAux=this->pElements[i];
                        this->pElements[i]=this->pElements[j];
                        this->pElements[j]=elementAux;
                    }
                }
            }
        }
        returnAux=0;
    }
    return returnAux;
}


/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* pList)
{
    int returnAux = 0;
    void* aux=NULL;
    if(pList->size==pList->reservedSize)
    {
        aux=(void*)realloc(pList->pElements,sizeof(void*)*(pList->reservedSize+AL_INCREMENT));
        if(aux!=NULL)
        {
            pList->reservedSize+=AL_INCREMENT;
            pList->pElements=aux;
        }
        else
        {
            returnAux=-1;
        }
    }
    return returnAux;

}

/** \brief  Expand an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* this,int index)
{
    int returnAux = -1;

    if(this!=NULL)
    {
        this->size+=1;
        resizeUp(this);

        for(int i=this->size; i>index; i--)
        {
            this->pElements[i]=this->pElements[i-1];
        }
        returnAux = 0;

    }
    return returnAux;
}

/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* this,int index)
{
    int returnAux = -1;

    if(this!=NULL && this->pElements!=NULL)
    {
        for(int i=index; i < this->size; i++)
        {
            this->pElements[i]=this->pElements[i+1];
        }
        this->size-=1;
        returnAux = 0;
    }
    return returnAux;
}
