#pragma once
#include ".\vipTagHash.h"

using namespace System;
using namespace System::Text;
using namespace System::IO;

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

public __gc class vipParser
{
protected:

	StringBuilder* strBuilder;
public:
	vipParser(void);
	~vipParser(void);


	void AppendText(String* text);

	void ReplaceString(String* tag, String* newText);

	VETRESULT ApplyTagHash(vipTagHash* hTable);


	VETRESULT RemoveTaggedText(String* startTag, String* endTag, bool recursive, unsigned int maxChars);

	VETRESULT RemoveFirstTaggedText(String* data, String* startTag, String* endTag, unsigned int maxChars);

};


}