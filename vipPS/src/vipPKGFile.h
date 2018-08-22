#pragma once
#include ".\vipTagHash.h"

using namespace System;
using namespace System::Text;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Xml;

 #define VETRET_OK					0     /* no errors found */
 #define VETRET_PARAM_ERR			1     /* illegal parameter(s) */
 #define VETRET_INTERNAL_ERR		2     /* internal routine error */
 #define VETRET_ILLEGAL_USE			4     /* illegal use of function (forbidden, empty video/frame, ..) */
 #define VETRET_DEPRECATED_ERR		8     /*  */
 #define VETRET_OK_DEPRECATED		16     /*  */
 #define VETRET_NOT_IMPLEMENTED		666     /*  */

typedef int VETRESULT;

namespace vipPS
{

public __gc class vipPKGFile
{
protected:

	String* fileTemplate;
	String* fileOutput;

	String* description;

	StringBuilder* strBuilder;

public:
	vipTagHash* myHash;
	Form* myForm;

	vipPKGFile(void);
	vipPKGFile(vipPKGFile* source);

	vipPKGFile(String* templateFile, String* outputFile);

	~vipPKGFile(void);

	int load( XmlNode* items );

	VETRESULT loadData();

	VETRESULT SaveOutputFile();
	VETRESULT SaveOutputFileTo(String* exportFile);


	void AppendText(String* text);
	void SetText(String* text);
	void ClearText(String* text);


	void ReplaceString(String* tag, String* newText);

	VETRESULT ApplyTagHash() { return ApplyTagHash(myHash); };
	VETRESULT ApplyTagHash(vipTagHash* hTable);


	VETRESULT RemoveTaggedText(vipDoubleTag* dt, bool recursive);

	VETRESULT RemoveFirstTaggedText(String* data, String* startTag, String* endTag, unsigned int maxChars);

	String* getData()
	 {
		if (strBuilder == NULL)
			return String::Empty;
		return strBuilder->ToString();
	 }

	__property String* get_FileTemplate()
	{
		return fileTemplate;
	}

	__property void set_FileTemplate(String* value)
	{
		fileTemplate = value;
	}

	__property String* get_FileOutput()
	{
		return fileOutput;
	}

	__property void set_FileOutput(String* value)
	{
		fileOutput = value;
	}

	__property String* get_Description()
	{
		return description;
	}

	__property void set_Description(String* value)
	{
		description = value;
	}


	String __gc* ToString()
	 {
		if (fileOutput != NULL)
			return Path::GetFileName(fileOutput);
		else if (strBuilder != NULL)
			return String::Concat(S"Unsaved from ", Path::GetFileName(fileTemplate));
		else
			return __gc new String("Empty file");
	 }
};


}