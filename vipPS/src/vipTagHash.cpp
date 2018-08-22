#include "StdAfx.h"
#include ".\viptaghash.h"


namespace vipPS
{


vipTagHash::vipTagHash(void)
{
	simpleTags = new vipTagVal*[MAXTAGS];
	doubleTags = new vipDoubleTag*[MAXTAGS];
	reset();
}

vipTagHash::vipTagHash(vipTagHash* source)
{
	simpleTags = new vipTagVal*[MAXTAGS];
	doubleTags = new vipDoubleTag*[MAXTAGS];
	reset();
	for (int i=0; i<MAXTAGS; i++)
	 {
		if (source->simpleTags[i] == NULL)
			continue;

		simpleTags[i] = new vipTagVal( source->simpleTags[i] );
	 }

	for (int i=0; i<MAXTAGS; i++)
	 {
		if (source->doubleTags[i] == NULL)
			continue;

		doubleTags[i] = new vipDoubleTag( source->doubleTags[i] );
	 }

}

vipTagHash::~vipTagHash(void)
{
//	simpleTags = __gc new vipTagVal[MAXTAGS];
//	doubleTags = __gc new vipDoubleTag[MAXTAGS];
	reset();
}

void vipTagHash::reset(void)
{
	for (int i=0; i<MAXTAGS; i++)
	 {
		simpleTags[i] = NULL;
		doubleTags[i] = NULL;
	 }
}


VETRESULT vipTagHash::loadHash(String* filePath)
{
//	simpleTags->Add()
	return 1;
}

void vipTagHash::loadDefaultHash(void)
{
	reset();

	simpleTags[0] = new vipTagVal(S"%FILENAME%");
	simpleTags[1] = new vipTagVal(S"%CLASSNAME%");
	simpleTags[2] = new vipTagVal(S"%VERSION%");
	simpleTags[3] = new vipTagVal(S"%TODAY%");
	simpleTags[4] = new vipTagVal(S"%AUTHOR%");
	simpleTags[5] = new vipTagVal(S"%CLASSDEFINE%");
	simpleTags[6] = new vipTagVal(S"%SOURCEDIR%");
	simpleTags[7] = new vipTagVal(S"%LIBDIR%");
	simpleTags[8] = new vipTagVal(S"%VETTYPE%");
//	simpleTags[] = new vipTagVal(S"");

	doubleTags[0] = new vipDoubleTag(S"%VFI_START%", S"%VFI_END%");
	doubleTags[1] = new vipDoubleTag(S"%EFI_START%", S"%EFI_END%");
	doubleTags[2] = new vipDoubleTag(S"%DOCVAR%", S"*/");
	doubleTags[3] = new vipDoubleTag(S"%DOCFUN%", S"*/");
//	doubleTags[] = vipDoubleTag(S"", S"");

}

VETRESULT vipTagHash::addSimpleTag(vipTagVal* data)
 {
	int i=0;
//	while( simpleTags[i++] != NULL && i<MAXTAGS ) ;
return 1;


 }
VETRESULT vipTagHash::addDoubleTag(vipDoubleTag* data)
 {
	int i=0;
//	while( simpleTags[i++] != NULL && i<MAXTAGS ) ;

return 1;
 }

VETRESULT vipTagHash::removeSimpleTag(vipTagVal* data)
 {
return 1;
 }

VETRESULT vipTagHash::removeDoubleTag(vipDoubleTag* data)
 {
return 1;
 }


VETRESULT vipTagHash::editSimpleTag(String* tag, String* value, bool enabled)
 {
	for(int i=0; i<MAXTAGS; i++)
	 {
		if (simpleTags[i] == NULL)
			continue;

		if ( simpleTags[i]->tag->CompareTo(tag) )
			continue;

		simpleTags[i]->value = value;
		simpleTags[i]->enabled = enabled;

		return VETRET_OK;
	 }

	 return VETRET_PARAM_ERR;
 }

VETRESULT vipTagHash::editDoubleTag(String* starttag, bool enabled)
 {
	for(int i=0; i<MAXTAGS; i++)
	 {
		if (doubleTags[i] == NULL)
			continue;

		if ( doubleTags[i]->startTag->CompareTo(starttag) )
			continue;

		doubleTags[i]->enabled = enabled;

		return VETRET_OK;
	 }

	 return VETRET_PARAM_ERR;
 }

void vipTagHash::enableAllSimpleTags()
 {
	for(int i=0; i<MAXTAGS; i++)
	 {
		if (doubleTags[i] == NULL)
			continue;

		doubleTags[i]->enabled = true;
	 }
 }

 void vipTagHash::enableAllDoubleTags()
 {
	for(int i=0; i<MAXTAGS; i++)
	 {
		if (simpleTags[i] == NULL)
			continue;

		simpleTags[i]->enabled = true;
	 }

 }

void vipTagHash::disableAllSimpleTags()
 {
	for(int i=0; i<MAXTAGS; i++)
	 {
		if (doubleTags[i] == NULL)
			continue;

		doubleTags[i]->enabled = false;
	 }
 }

 void vipTagHash::disableAllDoubleTags()
 {
	for(int i=0; i<MAXTAGS; i++)
	 {
		if (simpleTags[i] == NULL)
			continue;

		simpleTags[i]->enabled = false;
	 }

 }

 String* vipTagHash::ToString()
  {
	StringBuilder* strB = new StringBuilder(1024);
	strB->Append(S"Simple Tags:\r\n");

	for (int i=0; i<MAXTAGS; i++)
	 {
		if (simpleTags[i] == NULL)
			continue;

		strB->Append(S"_______________ITEM\r\n");
		strB->AppendFormat(S" tag:\t{0}\r\n", simpleTags[i]->tag);
		strB->AppendFormat(S" value:\t{0}\r\n", simpleTags[i]->value);
		strB->AppendFormat(S" enabled:\t{0}\r\n", simpleTags[i]->enabled.ToString());
		strB->AppendFormat(S" comment:\t{0}\r\n", simpleTags[i]->comment);
	 }

	strB->Append(S"\r\nDouble Tags:\r\n");

	for (int i=0; i<MAXTAGS; i++)
	 {
		if (doubleTags[i] == NULL)
			continue;

		strB->Append(S"_______________ITEM\r\n");
		strB->AppendFormat(S" endTag:\t{0}\r\n", doubleTags[i]->endTag);
		strB->AppendFormat(S" startTag:\t{0}\r\n", doubleTags[i]->startTag);
		strB->AppendFormat(S" enabled:\t{0}\r\n", doubleTags[i]->enabled.ToString());
		strB->AppendFormat(S" maxChars:\t{0}\r\n", doubleTags[i]->maxChars.ToString());
		strB->AppendFormat(S" comment:\t{0}\r\n", doubleTags[i]->comment);

	 }

	 String* val = strB->ToString();
	 strB = NULL;
	 return val;
  }




}