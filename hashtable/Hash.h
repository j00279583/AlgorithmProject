#include <stdio.h>
#include <malloc.h>

#define VOS_OK 1
#define VOS_ERROR 0xffff
#define INITKEY   0xffffffff

#define VOS_SUCCESS   1
#define VOS_FAILED   0

#define CHECK_PTR1(ptr)          \
if ((ptr) == NULL)                \
{                                 \
	printf("ptr is NULL \r\n");   \
	return VOS_ERROR;             \
}



typedef struct Tag_HasTable
{	
	int  iHashLength;
	int *puiHashDataBase;
	
}HashTalbe_S;


int Agent_InitHashTable(HashTalbe_S *pstHashTable);
int *Agent_GetUserInput(int *piLength);
int Agent_GetUserSerchData(int *puiData);
int Agent_Hash_Covert_Line(int key);
int Agent_InSertHashTable(HashTalbe_S *pstHashTable, int *piArrayData, 
	int length);
int Agent_HashTableDataIsExist(HashTalbe_S *pstHashTable, int key);
int Agent_UpdateHashLength(int length);
