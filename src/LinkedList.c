#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this=(LinkedList*)malloc(sizeof(LinkedList));
    if(this!=NULL)
    {
        this->pFirstNode=NULL;
        this->size=0;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        returnAux=this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode=NULL;
    int len;
    int i;
    if(this!=NULL && nodeIndex>=0)//verifico que nodeIndex no sea menor a 0
    {
        //verifico que this no sea NULL
        len=ll_len(this);
        if(len>nodeIndex)//verifico que nodeIndex No sea mayor al len
        {
            pNode=this->pFirstNode;//pNode apunta al primer nodo de la lista
            for(i=0; i<nodeIndex; i++)//recorro hasta llegar al nodeIndex
            {
                pNode=pNode->pNextNode;//pNode apuntara al sig elemento de la lista
            }
        }
    }

    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* pNode=(Node*)malloc(sizeof(Node));//creo en memoria un nuevo Node
    Node* pNodeAux=NULL;
    int len;
    if(this!=NULL && pNode!=NULL && nodeIndex>=0)//verifico que nodeIndex no sea menor a 0
    {
        // y que this y pNode no sean NULL
        //verifico que this no sea NULL
        len=ll_len(this);//obtengo el largo de la lista
        if(nodeIndex<=len)//Verifico que el nodeIndex sea menor o igual al largo de la lista
        {
            pNodeAux=getNode(this,nodeIndex-1);//mi auxiliar apunta al elemento Anterior de  nodeIndex
            pNode->pElement=pElement;//asigno  a mi pNode el pElement
            if(nodeIndex==0)//si nodeInde es igual  a 0
            {
                pNode->pNextNode=this->pFirstNode;//obtengo el Nodo al  que apunta this para no perder la referencia
                // asignandola en mi pNode
                this->pFirstNode=pNode;//hago que this->pFirstNode Apunte a mi pNode
            }
            else if(nodeIndex>0 && nodeIndex<len)//si nodeIndex es mayor a 0 y menor al largo de la lista
            {
                pNode->pNextNode=pNodeAux->pNextNode;//Asigno a mi pNode->pNextNode el anterior Node
                //del cual hace referencia el nodeIndex
                //ahora pNodeaux y pNode apuntan al mismo Node

                pNodeAux->pNextNode=pNode;//ahora que guarde la referencia del anterior Node
                // asigno a pNodeAux->pNextNode Mi pNode
            }
            else if(nodeIndex==len)//si nodeIndex hace referencia al ultimo Node
            {
                pNode->pNextNode=NULL;//como es el ultimo Node su pNextNode apunta a NULL
                pNodeAux->pNextNode=pNode;
            }
            len++;//como agrege un Node mas hago un ++ del len
            this->size=len;// y se lo asigno al size de la lista
            returnAux=0;
        }
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux=-1;
    int len;
    if(this!=NULL)
    {
        len=ll_len(this);//obtengo el largo de la lista
        returnAux=addNode(this,len,pElement);//agrego el elemento al final de la lista
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* pNode = NULL;

    if(this != NULL && index >=0)//verifico que no sea NULL y que el index sea mayor o igual a 0
    {
        int len = ll_len(this);//obtengo el largo de la lista
        if(index<len)//index sea menor al len de la lista
        {
            pNode = getNode(this,index);//obtengo el Node en el indice indicado
            if(pNode!=NULL)//verifico que lo obtuve
            {
                returnAux = pNode->pElement;//retorno el elemento del Node
            }
        }
    }
    return returnAux;
}

/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* pNode = NULL;
    int len;
    if(this != NULL && index >=0)//verifico que no sea NULL o index sea mayor o igual a 0
    {
        len=ll_len(this);
        if(index<len)//que index sea menor a la lista
        {
            pNode = getNode(this,index);//obtengo el Node en el indice indicado
            pNode->pElement = pElement;//asigno el pElement pasado como parametro
            returnAux = 0;//retorno 0 si se realizo el seteo
        }
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pNodeAux=NULL;
    Node* pNodeAux2=NULL;
    int len;
    if(this!=NULL &&  index>=0)//verifico que nodeIndex no sea menor a 0
    {
        // y que this y pNode no sean NULL
        //verifico que this no sea NULL
        len=ll_len(this);//obtengo el largo de la lista
        if(index<len)//verifico que index sea menor al len
        {
            pNodeAux=getNode(this,index-1);//obtengo el Node anterior
            pNodeAux2=getNode(this,index);//obtengo el Node a ser removido
            if(index==0)//si el removido esta al principio de la lista
            {
                this->pFirstNode=pNodeAux2->pNextNode;//this ahora apunta al sig Node de la lista
                free(pNodeAux2);
                pNodeAux2=NULL;
            }
            else if(index>0 && index<len)
            {
                pNodeAux->pNextNode=pNodeAux2->pNextNode;//el Node anterior ahora apunta al sig Node de la lista
                free(pNodeAux2);
                pNodeAux2=NULL;
            }
            else if(index==len)
            {
                pNodeAux->pNextNode=NULL;
                free(pNodeAux2);
                pNodeAux2=NULL;
            }
            len--;
            this->size=len;
            returnAux=0;
        }
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int len;
    int i;
    if(this!=NULL)
    {
        len=ll_len(this);//obtengo el largo de la lista
        for(i=0; i<len; i++)//recorro la lista
        {
            ll_remove(this,i);//elimino los elemento de la lista
        }
        this->pFirstNode=NULL;//hago que el pFistNode apunte a NULL
        returnAux=0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        ll_clear(this);//elimino los elemento de la lista
        free(this);//libero el espacio de la lista
        returnAux=0;
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    void* pAux;
    int i;
    int len;
    if(this!=NULL)//verifico que no sea NULL
    {
        len=ll_len(this);//obengo el largo de la lista
        for(i=0; i<len; i++)//recorro la lista
        {
            pAux=ll_get(this,i);//por cada iteracion obtengo el elemento de cada Node
            if(pElement==pAux)//verifico que el elemento sea igual a pElement
            {
                returnAux=i;//retorno la posicion si fue encontrado
            }
        }
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        if(this->pFirstNode==NULL)//verifico que donde apunta this->pFirstNode sea NULL
        {
            returnAux=1;//1 si la lista esta vacia
        }
        else
        {
            returnAux=0;//la lista no esta vacia
        }

    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int len;
    if(this!=NULL && index>=0)//verifico que no sea NULL y que index sea >= a 0
    {
        len=ll_len(this);//obtengo el largo de la lista
        if(index<=len)//index sea < al largo de la lista
        {
            returnAux=addNode(this,index,pElement);//agrego el elemento en la posicion indicada
        }
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    if(this!=NULL)
    {
        returnAux=ll_get(this,index);//retorno el elemeto
        ll_remove(this,index);//elimino el elemento en la posicion indicada
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int retorno;
    if(this!=NULL)
    {
        returnAux=1;//retono 1 si contiene el elemento
        retorno=ll_indexOf(this,pElement);//ll_indexOf verifica que contenga el elemento
        if(retorno==-1)//si retorna -1 es que no contiene el elemento pasado
        {
            returnAux=0;//retorno 0 porque no lo contiene
        }
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int len;
    int i;
    void* pElement;
    if(this2!=NULL && this!=NULL)
    {
        len=ll_len(this2);//obtengo el largo de la lista this2
        returnAux=1;//retorno 1 si los elementos estan contenidos
        for(i=0; i<len; i++)//recorro this2
        {
            pElement=ll_get(this2,i);//obtengo los elementos de this 2
            if(pElement!=NULL)
            {
                if(ll_contains(this,pElement)==0)//verifico que el elemento de this2 este en this
                {
                    returnAux=0;//retorno 0 si el elemento no exta en this
                    break;//rompo porque ya no es valido
                }
            }
        }
    }

    return returnAux;
}

    int i;
/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int len;
    int i;
    void* pElement=NULL;
    if(this!=NULL && from>=0 && to>=from)//hago las validaciones
    {
        len=ll_len(this);
        if(from<=len && to<=len)
        {
            cloneArray=ll_newLinkedList();//creo una nueva lista
            for(i=from;i<to;i++)//recorro desde(from) hasta(to)
            {
                pElement=ll_get(this,i);//obtengo el elemento de this en el indice indicado
                if(pElement!=NULL)
                {
                    addNode(cloneArray,i,pElement);//lo agrego a mi nueva lista
                }
            }
        }
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int len;
    if(this!=NULL)
    {
        len=ll_len(this);//obtngo el largo de la lista de this
        cloneArray=ll_subList(this,0,len);//agrego a mi nueva lista desde la posicion 0 hasta el len todos los elementos
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;

    return returnAux;
}

