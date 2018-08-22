#pragma once
#include ".\vipPKGFile.h"
#include ".\vipTagHash.h"


typedef int VETRESULT;

namespace vipPS
{
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Xml;


#define MAXFILES 16

public __gc class vipPkgProject
{
protected:

	int id;
	String* friendlyName;
	String* os;
	String* comment;
	String* directory;

	String* templateDirectory; // used only on xml loading (template filename)

	unsigned int filesCount;

	vipPKGFile* myFiles[];
	vipTagHash* myHash;

public:

	vipPkgProject(void);

	vipPkgProject(vipPkgProject* source);

	~vipPkgProject(void);

	VETRESULT load( XmlNodeList* items );

	VETRESULT loadFiles();


	VETRESULT SetOutputNameFromClassName(String* name);

	VETRESULT addFile( vipPKGFile* newFile)
	{
		if ( newFile == NULL )
			return 1;
		if (filesCount >= MAXFILES)
			return 2;

		myFiles[filesCount++] = newFile;

		if (newFile->myHash == NULL)	//use shared hash
			newFile->myHash = myHash;

		return 0;
	}

	VETRESULT ApplyHashes();

	VETRESULT SaveOutputs();

	vipPKGFile* Files(unsigned int index);

	__property vipTagHash* get_TagHash()
	{
		return myHash;
	}

	__property void set_TagHash(vipTagHash* sharedHash)
	{
		myHash = NULL;
		myHash = sharedHash;
	}


	__property int get_ID()
	{
		return id;
	}

	__property int get_FilesCount()
	{
		return filesCount;
	}

	__property String* get_FriendlyName()
	{
		return friendlyName;
	}

	__property void set_FriendlyName(String* value)
	{
		friendlyName = value;
	}

	__property String* get_Directory()
	{
		return directory;
	}

	__property void set_Directory(String* value)
	{
		directory = value;
	}

	__property String* get_TemplateDirectory()
	{
		return templateDirectory;
	}

	__property void set_TemplateDirectory(String* value)
	{
		templateDirectory = value;
	}


	__property String* get_OS()
	{
		return os;
	}

	__property void set_OS(String* value)
	{
		os = value;
	}


	__property String* get_Comment()
	{
		return comment;
	}

	__property void set_Comment(String* value)
	{
		comment = value;
	}

	String* ToString()
	{
		return friendlyName;
	}

	String* ToBigString()
	{
		StringBuilder* strB = new StringBuilder(1024);
		strB->Append(S"\r\n");
		strB->AppendFormat(S" ID:\t\t{0}\r\n", id.ToString() );
		strB->AppendFormat(S" FriendlyName:\t{0}\r\n", friendlyName );
		strB->AppendFormat(S" OS:\t\t{0}\r\n", os );
		strB->AppendFormat(S" Comment:\t{0}\r\n", comment );
		strB->AppendFormat(S" Directory:\t{0}\r\n", directory );
		strB->AppendFormat(S" FilesCount:\t{0}\r\n", filesCount.ToString() );
		for (unsigned int i=0; i<filesCount; i++)
		{
			strB->AppendFormat(S"  File {0}", i.ToString() );
			strB->AppendFormat(S"\t FileOutput:\t{0}\r\n", myFiles[i]->FileOutput );
			strB->AppendFormat(S"\t FileTemplate:\t{0}\r\n", myFiles[i]->FileTemplate );
			strB->AppendFormat(S"\t Description:\t{0}\r\n", myFiles[i]->Description );
		}

	String* val = strB->ToString();
	 strB = NULL;
	 return val;
	}



};



}