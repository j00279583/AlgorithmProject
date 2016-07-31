#include "Hash.h"

int g_uiHashLength = 12;

/***************************************************************/
/***************************************************************/
/***������:main                                
/***������������:  ������
/***�����������:
						Input:  void
						output:
/***��������:  Agent
/***������������: 2016-07-01

/***************************************************************/
/***************************************************************/
void main()
{	
    int *puiTempData = NULL;
	int iDataLength = 0;
	int iTempData = 0;
	
	HashTalbe_S stHashTable = { 0 };

	puiTempData = Agent_GetUserInput(&iDataLength);
	Agent_InitHashTable(&stHashTable);
	Agent_InSertHashTable(&stHashTable,puiTempData,iDataLength);
	Agent_GetUserSerchData(&iTempData);
	Agent_HashTableDataIsExist(&stHashTable,iTempData);

	free(puiTempData);
	
}

/***************************************************************/
/***************************************************************/
/***������:Agent_InitHashTable                                
/***������������:  ��ʼ����ϣ��
/***�����������:
						Input:  pstHashTable
						output:
/***��������:  Agent
/***������������: 2016-07-01

/***************************************************************/
/***************************************************************/
int Agent_InitHashTable(HashTalbe_S *pstHashTable)
{	
	int iLoop = 0;
	CHECK_PTR1(pstHashTable);

	pstHashTable->iHashLength = g_uiHashLength;
	pstHashTable->puiHashDataBase = (int *)malloc(sizeof(int) *g_uiHashLength);
	
	CHECK_PTR1(pstHashTable->puiHashDataBase);

	for(iLoop = 0; iLoop < g_uiHashLength; iLoop++)
	{
		pstHashTable->puiHashDataBase[iLoop] = INITKEY;	
	}

	return VOS_OK;
}

/***************************************************************/
/***************************************************************/
/***������:Agent_InSertHashTable                               
/***������������:  �����ݲ����ϣ��  
						Input:  pstHashTable
						output:
/***��������:  Agent
/***������������: 2016-07-01                               

/***************************************************************/
/***************************************************************/
int Agent_InSertHashTable(HashTalbe_S *pstHashTable, int *piArrayData, 
	int length)
{	
	int iLoop = 0;
	int iCovertAddr = 0;
	int iKeyValue = 0;
	
	CHECK_PTR1(pstHashTable);
	for (iLoop = 0; iLoop <length; iLoop++)
	{	
		iKeyValue = piArrayData[iLoop];
		iCovertAddr = Agent_Hash_Covert_Line(iKeyValue);

		while(pstHashTable->puiHashDataBase[iCovertAddr] != INITKEY)
		{
			iCovertAddr = (iCovertAddr+1) % g_uiHashLength;
		}

		pstHashTable->puiHashDataBase[iCovertAddr] = iKeyValue;
	}

	return VOS_OK;
}

/***************************************************************/
/***************************************************************/
/***������:Agent_HashTableDataIsExist                               
/***������������:  ����keyֵ���������Ƿ���� 
						Input:  pstHashTable
						output:
/***��������:  Agent
/***������������: 2016-07-01                               

/***************************************************************/
/***************************************************************/
int Agent_HashTableDataIsExist(HashTalbe_S *pstHashTable, int key)
{
	int iCovertSearchAddr = 0;

	iCovertSearchAddr = Agent_Hash_Covert_Line(key);

	while(pstHashTable->puiHashDataBase[iCovertSearchAddr] != key)
	{
		iCovertSearchAddr = (iCovertSearchAddr +1) %g_uiHashLength;

		if (iCovertSearchAddr == Agent_Hash_Covert_Line(key)) /*����һȦ*/
		{	
			printf("the data is not exist\r\n");
			return VOS_FAILED;
		}
	}
	
	printf("the data is  exist, addr is = 0x%x\r\n",iCovertSearchAddr);
	
	return VOS_SUCCESS;
}

/***************************************************************/
/***************************************************************/
/***������:Agent_Hash_Covert_Line                               
/***������������:��keyֵ������������ת�� 
						Input:  key
						output:
/***��������:  Agent
/***������������: 2016-07-01                               

/***************************************************************/
/***************************************************************/
int Agent_Hash_Covert_Line(int key)
{
	int iCovertAddr = 0;
	iCovertAddr = key % g_uiHashLength;

	return iCovertAddr;
}

/***************************************************************/
/***************************************************************/
/***������:Agent_UpdateHashLength                               
/***������������:���¹�ϣ���ʵ�ʳ���Ĭ��Ϊ12 
						Input:  length
						output:
/***��������:  Agent
/***������������: 2016-07-01                               

/***************************************************************/
/***************************************************************/
int Agent_UpdateHashLength(int length)
{	
	g_uiHashLength = length;
	
	return VOS_OK;
}

/***************************************************************/
/***************************************************************/
/***������:Agent_GetUserInput                               
/***������������:��ȡ�û�������
						Input:  piLength
						output:
/***��������:  Agent
/***������������: 2016-07-01                               

/***************************************************************/
/***************************************************************/
int *Agent_GetUserInput(int *piLength)
{	
	int iNumber = 0;
	int *puiDataArray = NULL;
	
	printf("Please input the record number\r\n");
	
	scanf("%d",&iNumber);

	puiDataArray = (int *)malloc(iNumber *sizeof(int));


	Agent_UpdateHashLength(iNumber);
	*piLength = iNumber;

	printf("Please input the data \r\n");

	for (int i = 0 ; i < iNumber; i++)
	{
		scanf("%2d",&puiDataArray[i]);
	}
	
	return puiDataArray;	
}

/***************************************************************/
/***************************************************************/
/***������:Agent_GetUserSerchData                               
/***������������:��ȡ�û�������Ĳ�������
						Input:  puiData
						output:
/***��������:  Agent
/***������������: 2016-07-01                               

/***************************************************************/
/***************************************************************/
int Agent_GetUserSerchData(int *puiData)
{	
	int iTempData = 0;
	
	printf("Please input the data you want search\r\n");

	scanf("%d",&iTempData);

	*puiData = iTempData;

	return VOS_OK;	
}

