#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

void main()
{
	ifstream fin;
	fstream fout;
	unsigned int i;
	struct FileHdr
	{
		unsigned int signature;
		unsigned int sender;
		unsigned int owner;
		unsigned int msgcount;
	} FH;
	struct MsgHdr
	{
		unsigned int sender;
		double dt;
		unsigned int flag;
		unsigned int msglen;
		char message[];
	} MH;
	fin.open("D:\\Net Speakerphone\\UINS\\399281\\History\\399281.nsh",ios::binary);
	fin.read((char*)&FH,16); fin.ignore(16);
	if (FH.signature != 0xAA550401) {
		cout << "Это не файл истории NetSph!\r\n";
		exit(1);
	}
	printf("Сигнатура=%08X\r\nОтправитель=%d\r\nПолучатель=%d\r\nКол-во=%d\r\n\r\n",FH.signature,FH.sender,FH.owner,FH.msgcount);
	for (i=0;i<FH.msgcount;i++) {
	fin.read((char*)&MH,4);	fin.ignore(4);
	fin.read((char*)&MH.dt,12);	fin.ignore(4);
	fin.read((char*)&MH.msglen,4); fin.ignore(4);
	fin.read(MH.message,MH.msglen);
	MH.message[MH.msglen]='\0';
	printf("Отправитель=%d\r\nДата=%f\r\nФлаг=%08X\r\nДлина=%d\r\n%s\r\n\r\n",MH.sender,MH.dt,MH.flag,MH.msglen,MH.message);
	}
	fin.close();
	exit(0);
}