/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004 - 2010, 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
******************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************//*!
*
* @file stack.c
*
* @author
*
* @version
*
* @date 
*
* @brief The file contains Buffer stack implementation for IEEE11073 Library.
*
*****************************************************************************/
/******************************************************************************
* Includes
*****************************************************************************/
#include <string.h>
#include "stack.h"
/******************************************************************************
* Local Types - None
*****************************************************************************/

/*****************************************************************************
* Local Functions Prototypes - None
*****************************************************************************/

/*****************************************************************************
* Local Variables - None
*****************************************************************************/

/*****************************************************************************
* Local Functions - None
*****************************************************************************/

/*****************************************************************************
* Global Functions
*****************************************************************************/
/**************************************************************************//*!
*
* @name  StackInit
*
* @brief This funtion allocates Buffer Stack
*
* @param StackSize  :   Buffer Size
*
* @return Pointer to Buffer Stack if successful otherwise NULL
******************************************************************************
* This funtion allocates Buffer Stack
*****************************************************************************/
PTR_BUFFSTACK StackInit(
    uint32_t StackSize  /* [IN] Buffer Size */
)
{
    uint32_t MemSize = StackSize + sizeof(BUFFSTACK);
    /* Memory Required */
    PTR_BUFFSTACK pvOutBuffer = (PTR_BUFFSTACK)malloc(MemSize);
    memset(pvOutBuffer, 0, MemSize);
    if(pvOutBuffer == NULL)
    {
        return NULL;
    }
    pvOutBuffer->top = (uint8_t *)pvOutBuffer + sizeof(BUFFSTACK)
    + StackSize;
    pvOutBuffer->current_size = 0;
    pvOutBuffer->total_size = StackSize;
    return pvOutBuffer;
}

/**************************************************************************//*!
*
* @name  StackDeInit
*
* @brief This funtion de-allocates Buffer Stack
*
* @param pBuffStack :   Pointer to Buffer Stack
*
* @return None
******************************************************************************
* This funtion de-allocates Buffer Stack
*****************************************************************************/
void StackDeInit(
    PTR_BUFFSTACK pBuffStack    /* [IN] Pointer to Buffer Stack */
)
{
    if(pBuffStack != NULL)
    {
        /* Compute Pool Stack */
        free(pBuffStack);
    }
}

/**************************************************************************//*!
*
* @name  PushStack
*
* @brief This funtion pushes Data Buffer to Buffer Stack
*
* @param pBuffStack :   Pointer to Buffer Stack
* @param pvOutBuffer    :   Pointer to Data Buffer
* @param OutBuffSize    :   Data Buffer Size
*
* @return ERR_CODE
*   ERROR_SUCCESS   : if Successful
*   ERROR_INSUFFICIENT_MEMORY   : if Failed
******************************************************************************
* This funtion pushes Data Buffer to Buffer Stack
*****************************************************************************/
uint32_t PushStack(
    PTR_BUFFSTACK   pBuffStack,     /* [IN] Pointer to Buffer Stack */
    void        *OutBuffSize,     /* [IN] Data Buffer Size */
    uint8_t     buffer_size
)
{
    if((pBuffStack->total_size - pBuffStack->current_size) < buffer_size)
    {
        /* No Enough Memory in Stack */
        return -1;
    }
    pBuffStack->top = (uint8_t *)pBuffStack->top - buffer_size;
    memcpy(pBuffStack->top, OutBuffSize, buffer_size);
    pBuffStack->current_size += buffer_size;
    return 0;
}

/**************************************************************************//*!
*
* @name  PopStack
*
* @brief This funtion pops Specified number of bytes from top of Buffer Stack
*
* @param pBuffStack :   Pointer to Buffer Stack
* @param nBytes :   Number of Bytes to be Poped
* @param pvOutBuffer    :   Pointer to Stack Top
* @param OutBuffSize    :   Data Buffer Size
*
* @return ERR_CODE
*   ERROR_SUCCESS   : if Successful
******************************************************************************
* This funtion pops Specified number of bytes from top of Buffer Stack. Also 
* adjusts Buffer Stack TOP Pointer.
*****************************************************************************/
uint32_t PopStack(
PTR_BUFFSTACK   pBuffStack,     /* [IN] Pointer to Buffer Stack */
uint8_t        * pOutBuffSize,  /* [OUT] Data Buffer Size */
uint8_t        buffer_size
)
{
    *(uint8_t * *)pOutBuffSize = &(((uint8_t *)(pBuffStack->top))[0]);

    pBuffStack->top = (void*)&(((uint8_t *)(pBuffStack->top))[buffer_size]);
    pBuffStack->current_size -= buffer_size;

    return 0;
}

/**************************************************************************//*!
*
* @name  GetStackSize
*
* @brief This funtion return Total Buffer Size
*
* @param pBuffStack :   Pointer to Buffer Stack
*
* @return Total Buffer Size
******************************************************************************
* This funtion return Total Buffer Size 
*****************************************************************************/
uint32_t GetStackSize(
    PTR_BUFFSTACK pBuffStack    /* [IN] Pointer to Buffer Stack */
)
{
    return pBuffStack->total_size;
}

/**************************************************************************//*!
*
* @name  GetDataSize
*
* @brief This funtion returns size of valid data in Buffer
*
* @param pBuffStack :   Pointer to Buffer Stack
*
* @return size of valid data in Buffer
******************************************************************************
* This funtion returns size of valid data in Buffer 
*****************************************************************************/
uint32_t GetDataSize(
    PTR_BUFFSTACK pBuffStack    /* [IN] Pointer to Buffer Stack */
)
{
    return pBuffStack->current_size;
}

/**************************************************************************//*!
*
* @name  GetStackTop
*
* @brief This funtion returns Top of Buffer Stack
*
* @param pBuffStack :   Pointer to Buffer Stack
*
* @return Top of Buffer Stack
******************************************************************************
* This funtion returns Top of Buffer Stack
*****************************************************************************/
void* GetStackTop(
    PTR_BUFFSTACK pBuffStack    /* [IN] Pointer to Buffer Stack */
)
{
    return pBuffStack->top;
}
