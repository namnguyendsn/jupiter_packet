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
* @file stack.h
*
* @author
*
* @version
*
* @date
*
* @brief The file Defines Buffer Stack Interface used by Ieee11073 Agent
*        Library
*
*****************************************************************************/
#ifndef _BUFFSTACK_H
#define _BUFFSTACK_H

/******************************************************************************
* Includes
*****************************************************************************/
#include "common_config.h"
#include "stdlib.h"
/******************************************************************************
* Types
*****************************************************************************/
/* Buffer Stack Structure */
typedef struct _BUFFSTACK
{
    uint8_t* top;              /* Pointer to Stack Top */
    uint8_t total_size;    /* Total buffer Size */
    uint8_t current_size;  /* Current Buffer Size */
}BUFFSTACK, *PTR_BUFFSTACK;

/*****************************************************************************
* Global Function Prototypes
*****************************************************************************/
/* This funtion allocates Buffer Stack */
PTR_BUFFSTACK StackInit(
uint32_t StackSize);

/* This funtion de-allocates Buffer Stack */
void StackDeInit(
PTR_BUFFSTACK pBuffStack);

/* This funtion pushes Data Buffer to Buffer Stack */
uint32_t PushStack(
PTR_BUFFSTACK   pBuffStack,
void        *OutBuffSize,
uint8_t     buffer_size);

/* This funtion pops Specified number of bytes from top of Buffer Stack */
uint32_t PopStack(
PTR_BUFFSTACK   pBuffStack,
uint8_t        *pOutBuffSize,
uint8_t        buffer_size);

/* This funtion return Total Buffer Size */
uint32_t GetStackSize(
PTR_BUFFSTACK   pBuffStack);

/* This funtion returns size of valid data in Buffer */
uint32_t GetDataSize(
PTR_BUFFSTACK   pBuffStack);

/* This funtion returns Top of Buffer Stack */
void* GetStackTop(
PTR_BUFFSTACK   pBuffStack);

#endif /* _BUFFSTACK_H */
