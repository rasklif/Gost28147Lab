#pragma once
/**
@file gost.h
��������� ������� ���������� ����28147-89
*/
/**
@mainpage ���������� ����28147-89
@details ��������� ������� ����������, �������������
�� ���� �������: "��������� ������������", "������� ������",
"������������","������������ � �������� ������".
���, ��� ���� ����� ��� ������ ������ � ����������� ������� � ����� gost.h
@author �.�. ���������� (mailto: faddistr@gmail.com)
*/
#ifndef GOST_H
#define GOST_H
#include "stdint.h"
/**
  ���������� ����� ������
*/
#define _GOST_TABLE_NODES 8
/**
  ���������� ��������� � ���� ������, ��� ��������� ������������ 128 ������� ������� ������,
  � ������ �������� ������� �������� 0.
*/
#define _GOST_TABLE_MAX_NODE_VALUE 16
/**
  ������ ������� �����(��) � ������
*/
#define _GOST_TABLE_SIZE _GOST_TABLE_NODES*_GOST_TABLE_MAX_NODE_VALUE//128(in orig 64) to optimize code
/**
  ��������� ���������� N1 � ������������ ������ GOST_Data_Part
*/
#define _GOST_Data_Part_N1_Half 1
/**
  ��������� ���������� N2 � ������������ ������ GOST_Data_Part
*/
#define _GOST_Data_Part_N2_Half 0
/**
  ���� �� ���������.
*/
#define _GOST_Def_Byte 0
/**
@union GOST_Data_Part
����������� ������ ��� ����� ���������� ����, ��������� ��������� 64������ ������ ������
*/
//to make code understandable
typedef union
{
	/**
	 * @brief parts 8������ ������������� ������ ������ ��� ���������������
	*/
	uint8_t  parts[8];
	/**
	 * @brief half 32������� ������������� ������ ������ ��� ���������������
	*/
	uint32_t half[2];
	// uint64_t full; //��� � �51
} GOST_Data_Part;
/**
  ������ ������ ������ ��� ���������������
*/
#define _GOST_Part_Size sizeof(GOST_Data_Part)
/**
  ������ ������������
*/
#define _GOST_Imitta_Size   _GOST_Part_Size
/**
  ������ �������������
*/
#define _GOST_Synchro_Size  _GOST_Part_Size
/**
  ������ �����(��) � ������(256 ���)
*/
#define _GOST_Key_Size   32
/**
  ��������� ��� ��������������������
*/
#define _GOST_Next_Step false
/**
  ��������� ��� ��������������������
*/
#define _GOST_Last_Step true
/**
  C������������ � ������������ ���������� ���������
*/
#define _GOST_ROT 1
/**
  ������������� � ������� ������������� ���������� ���������
*/
#define _GOST_ROT_Synchro_GAMMA 1
/**
  ����� ����������
*/
#define _GOST_Mode_Encrypt true
/**
  ����� �������������
*/
#define _GOST_Mode_Decrypt false

/**
@details GOST_Imitta
����������� ������� ������������
@param *Open_Data - ��������� �� ������ ��� ������� ��������� ��������� �����������.
@param *Imitta - ��������� �� ������ �������� _GOST_Imitta_Size(64 ����), ���� ����� ������� ���������
������� ������������.
@param Size - ������ ������
@param *GOST_Table - ��������� �� ������� ������ ����(��) � 128 ������� �������
(������ �������� ��������� 0)
@param *GOST_Key - ��������� �� 256 ������ ������ �����(��).
@attention  ��� ������� ������ ������ Imitta ������ ���� �������� _GOST_Def_Byte!
*/
void GOST_Imitta(uint8_t *Open_Data, uint8_t *Imitta, uint32_t Size, uint8_t *GOST_Table, uint8_t *GOST_Key);

/**
@details GOST_Encrypt_SR
������� ����������/������������� � ������ ������� ������.
@param *Data - ��������� �� ������ ��� ����������, ����� ���� ��������� ���������.
@param Size - ������ ������
@param Mode - ���� _GOST_Mode_Encrypt ����������, _GOST_Mode_Decrypt - �������������
@param *GOST_Table - ��������� �� ������� ������ ����(��) � 128 ������� �������
(������ �������� ��������� 0)
@param *GOST_Key - ��������� �� 256 ������ ������ �����(��).
*/
void GOST_Encrypt_SR(uint8_t *Data, uint32_t Size, bool Mode, uint8_t *GOST_Table, uint8_t *GOST_Key);



#if _GOST_ROT_Synchro_GAMMA==1
/**
@details GOST_Crypt_G_PS
������� ���������� ������������� ��� ������ ������������. ������ ���� ������� �� ������� ������
GOST_Crypt_G_Data. ���� ������� ������������� � ��� "�����������" ���� (�������� ������� 32������ �����), �� ������� ����� ������
� ������� ������ ���������� ���� ��������������������, ��� ���� � ����� gost.h ����������
��������� _GOST_ROT_Synchro_GAMMA=0. ������������� ��� ��������� ������, ��� ��� ����� �������
������ � ������������� � ������� ���������� ���������.
@param *Synchro - ��������� �� ������ ��� ����������, ����� ���� ��������� ���������.
@param *GOST_Table - ��������� �� ������� ������ ����(��) � 128 ������� �������
(������ �������� ��������� 0)
@param *GOST_Key - ��������� �� 256 ������ ������ �����(��).
*/
void GOST_Crypt_G_PS(uint8_t *Synchro, uint8_t *GOST_Table, uint8_t *GOST_Key);
#else
void GOST_Crypt_32_E_Cicle(GOST_Data_Part *DATA, uint8_t *GOST_Table, uint32_t *GOST_Key);
/**
  ���������� �������������. ��. ������� GOST_Crypt_G_PS
*/
#define GOST_Crypt_G_PS(GOST_Synchro, GOST_Table, GOST_Key) GOST_Crypt_32_E_Cicle((GOST_Data_Part *) GOST_Synchro, GOST_Table, (uint32_t *) GOST_Key)
#endif

/**
@details GOST_Crypt_G_Data
����������\������������� ����� ������ � ������ ������������.
@param *Data - ��������� �� ������ ��� ����������\�������������, ����� ���� ��������� ��������� ������.
@param Size - ������ ������
@param *Synchro - ��������� �� �������������, ����� ���� ��������� ������� �������� �������������.
@param *GOST_Table - ��������� �� ������� ������ ����(��) � 128 ������� �������(������ �������� ��������� 0).
@param *GOST_Key - ��������� �� 256 ������ ������ �����(��).
@attention ������������� Synchro ��� ������� ������ ������ ���� ������������ ��������/�������� GOST_Crypt_G_PS.
*/
void GOST_Crypt_G_Data(uint8_t *Data, uint32_t Size, uint8_t *Synchro, uint8_t *GOST_Table, uint8_t *GOST_Key);

#if _GOST_ROT_Synchro_GAMMA==1
/**
@details GOST_Crypt_GF_Prepare_S
������� ���������� ������������� ��� ������ ������������ � �������� ������.
������ ������� 32������ ����� �������������. ���������� ������ ������������, ���� �������������
�������� � "�����������" ����(32� ������ ����� �������� �������) �� ������� ����� ��������.
������������� ��� ��������� ������, ��� ��� ����� ������� ������ � ������������� �
������� ���������� ���������. ��� ��������� ����� ����������� ���������� ��������� ���������
_GOST_ROT_Synchro_GAMMA=0 � gost.h.
@param *Synchro - ��������� �� ������ ��� ����������, ����� ���� ��������� ���������.
*/
void GOST_Crypt_GF_Prepare_S(uint8_t *Synchro);
#endif

/**
@details GOST_Crypt_GF_Data
������� ���������� � ������ ������������ � �������� ������.
@param *Data - ��������� �� ������ ��� ����������/�������������.
@param Size - ������ ������
@param *Synchro - ��������� �� �������������,
����� ���� ��������� ������� �������� �������������.
@param Mode - ���� _GOST_Mode_Encrypt ����� ��������� ���������� ������,
���� _GOST_Mode_Decrypt �������������
@param *GOST_Table - ��������� �� ������� ������ ����(��) � 128 ������� �������
(������ �������� ��������� 0).
@param *GOST_Key - ��������� �� 256 ������ ������ �����(��).
@attention ���� ������������ ����� ������������� � ������� ���������� ���������, �� �������������
Synchro ��� ������� ������ ������ ���� ������������ �������� GOST_Crypt_GF_Prepare_S.
*/
void GOST_Crypt_GF_Data(uint8_t *Data, uint32_t Size, uint8_t *Synchro, bool Mode, uint8_t *GOST_Table, uint8_t *GOST_Key);




#endif // GOST_H
