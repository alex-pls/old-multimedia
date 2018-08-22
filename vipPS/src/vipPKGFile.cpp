#include "StdAfx.h"
#include ".\vipPKGFile.h"



namespace vipPS
{

vipPKGFile::vipPKGFile(void)
{
	strBuilder = NULL;
	strBuilder = __gc new StringBuilder(1024);
	myForm = NULL;
	myHash = NULL;

	fileTemplate = S"";
	fileOutput = S"";
	description = S"";
}

vipPKGFile::vipPKGFile(vipPKGFile* source)
{
	strBuilder = NULL;
	strBuilder = __gc new StringBuilder(1024);
	strBuilder->Append(source->getData());

	myForm = NULL;

	myHash = NULL;
	if (source->myHash != NULL)
		myHash = new vipTagHash(source->myHash);

	fileTemplate = String::Copy(source->fileTemplate);
	fileOutput = String::Copy(source->fileOutput);
	description = String::Copy(source->description);
}


vipPKGFile::vipPKGFile(String* templateFile, String* outputFile)
{
	strBuilder = NULL;
	myForm = NULL;
	myHash = NULL;

	fileTemplate = String::Copy(templateFile);
	fileOutput = String::Copy(outputFile);

	loadData();
}

vipPKGFile::~vipPKGFile(void)
{
	strBuilder = NULL;
}


int vipPKGFile::load( XmlNode* item )
 {
	fileTemplate = item->Attributes->Item(0)->Value;
	return 0;
 }

VETRESULT vipPKGFile::loadData()
 {
	if (strBuilder)
		strBuilder = NULL;

	if ( File::Exists(fileTemplate) )
	 {
		StreamReader* sr = new StreamReader(fileTemplate);
		try {
			String* line;
			strBuilder = new StringBuilder(1024);
			while ( line = sr->ReadLine() )
				strBuilder->Append(String::Concat(line, S"\r\n"));
		} __finally {
			sr = NULL;
		}
	 }

	if ( File::Exists(fileOutput) )
	{
		if ( File::Exists( String::Concat(fileOutput, S".bak") ) )
			File::Delete(String::Concat(fileOutput, S".bak"));
		File::Move(fileOutput, String::Concat(fileOutput, S".bak"));
	}
	return 0;
 }

VETRESULT vipPKGFile::SaveOutputFile()
{
	if ( strBuilder == NULL )
		return VETRET_ILLEGAL_USE;

	StreamWriter* fWriter = File::CreateText(fileOutput);
	fWriter->Write(strBuilder->ToString());
	fWriter->Close();
	fWriter=NULL;

	return VETRET_OK;
}
VETRESULT vipPKGFile::SaveOutputFileTo(String* exportFile)
{
	if ( strBuilder == NULL )
		return VETRET_ILLEGAL_USE;

	StreamWriter* fWriter = File::CreateText(exportFile);
	fWriter->Write(strBuilder->ToString());
	fWriter->Close();
	fWriter=NULL;

	return VETRET_OK;
}

void vipPKGFile::AppendText(String* text)
{
	if (strBuilder == NULL)
		strBuilder = new StringBuilder(1024);
	strBuilder->Append(text);
}

void vipPKGFile::SetText(String* text)
{
	if (strBuilder != NULL)
		strBuilder = NULL;
	strBuilder = new StringBuilder(1024);
	strBuilder->Append(text);
}

void vipPKGFile::ClearText(String* text)
{
	if (strBuilder != NULL)
		strBuilder = NULL;
	strBuilder = new StringBuilder(1024);
}


void vipPKGFile::ReplaceString(String* tag, String* newText)
{
	strBuilder->Replace(tag, newText);
}
VETRESULT vipPKGFile::RemoveTaggedText(vipDoubleTag* dt, bool recursive)
{
	VETRESULT ret = VETRET_OK;
	String* data = strBuilder->ToString();

	if (!recursive)
		ret = RemoveFirstTaggedText(data, dt->startTag, dt->endTag, dt->maxChars);
	else
	 {
		while (ret == VETRET_OK)
		 ret += RemoveFirstTaggedText(data, dt->startTag, dt->endTag, dt->maxChars);
	 }

	 data->Replace(dt->startTag, S"");
	 if ( dt->endTag->CompareTo(S"*/") )
		data->Replace(dt->endTag, S"");

	 if (ret == VETRET_OK)
	 {
		strBuilder = NULL;
		strBuilder = new StringBuilder(data);
	 }
	return ret;
}

VETRESULT vipPKGFile::RemoveFirstTaggedText(String* data, String* startTag, String* endTag, unsigned int maxChars)
{
	if (data == NULL)
		return VETRET_PARAM_ERR;
	if (data->Length == 0)
		return VETRET_PARAM_ERR;

	unsigned int start, end;
	start = data->IndexOf(startTag);

	if (start == -1)
		return VETRET_ILLEGAL_USE;

	if ( maxChars && (start + maxChars < (unsigned int)data->Length) )
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





VETRESULT vipPKGFile::ApplyTagHash(vipTagHash* hTable)
{
	if (hTable== NULL)
		return VETRET_PARAM_ERR;

	if (strBuilder== NULL)
		return VETRET_PARAM_ERR;

	vipTagVal* cST = NULL;
	int i=0;
	for (i=0; i<MAXTAGS; i++)
	 {
		cST = hTable->simpleTags[i];

		if ( cST == NULL )
			continue;

		if ( cST->enabled )
			strBuilder->Replace( cST->tag, cST->value);
	 }

	vipDoubleTag* cDT = NULL;
	for (i=0; i<MAXTAGS; i++)
	 {
		cDT = hTable->doubleTags[i];

		if ( cDT == NULL )
			continue;

		if ( cDT->enabled )
			RemoveTaggedText( cDT, true);
		else
		 {
			strBuilder->Replace(cDT->startTag, S"");
			if ( cDT->endTag->CompareTo(S"*/") )
				strBuilder->Replace(cDT->endTag, S"");
		 }
	 }
//maxchar bug
	return 0;
}




}