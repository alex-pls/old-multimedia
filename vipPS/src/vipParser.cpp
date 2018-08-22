#include "StdAfx.h"
#include ".\vipparser.h"



namespace vipPS
{

vipParser::vipParser(void)
{
	strBuilder = NULL;
	strBuilder = new StringBuilder(1024);
}

vipParser::~vipParser(void)
{
	strBuilder = NULL;
}

void vipParser::AppendText(String* text)
{
	strBuilder->Append(text);
}

void vipParser::ReplaceString(String* tag, String* newText)
{
	strBuilder->Replace(tag, newText);
}
VETRESULT vipParser::RemoveTaggedText(String* startTag, String* endTag, bool recursive, unsigned int maxChars)
{
	String* data = strBuilder->ToString();
	VETRESULT ret = VETRET_OK;
	if (!recursive)
		ret = RemoveFirstTaggedText(data, startTag, endTag, maxChars);
	else
	 {
		while (ret == VETRET_OK)
		 ret += RemoveFirstTaggedText(data, startTag, endTag, maxChars);
	 }
	if (ret == VETRET_OK)
	 {
		strBuilder = NULL;
		strBuilder = new StringBuilder(data);
	 }
	return ret;
}

VETRESULT vipParser::RemoveFirstTaggedText(String* data, String* startTag, String* endTag, unsigned int maxChars)
{
	if (data == NULL)
		return VETRET_PARAM_ERR;
	if (data->Lenght == 0)
		return VETRET_PARAM_ERR;

	int start, end;
	start = data->IndexOf(startTag);

	if (start == -1)
		return VETRET_ILLEGAL_USE;

	if ( maxChars && (start + maxChars < data->Length) )
		end = data->IndexOf(endTag, start, maxChars);
	else
		end = data->IndexOf(endTag, start);

	if (end == -1)
		return VETRET_ILLEGAL_USE;

	if ( end-start < 0)
		return VETRET_INTERNAL_ERR;

	data->Remove(start, end-start);

	return VETRET_OK;
}





VETRESULT vipParser::ApplyTagHash(vipTagHash* hTable)
{
	if (hTable== NULL)
		return VETRET_PARAM_ERR;

		vipTagVal* cST = NULL;
	int i=0;
	while( hTable->simpleTags[i++] != NULL && i<MAXTAGS )
	 {
		cST = hTable->simpleTags[i-1];
		if ( cST->enabled )
			strBuilder->Replace( cST->tag, cST->value);
	 }

	vipDoubleTag* cDT = NULL;
	i=0;
	while( hTable->doubleTags[i++] != NULL && i<MAXTAGS )
	 {
		cDT = hTable->doubleTags[i-1];
		if ( cDT->enabled )
			strBuilder->Replace( cDT->startTag , cDT->endTag, cDT->maxChars );
	 }


}




}