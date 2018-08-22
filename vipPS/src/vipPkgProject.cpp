#include "StdAfx.h"
#include ".\vipPkgProject.h"
//#using <mscorlib.dll>

namespace vipPS
{

vipPkgProject::vipPkgProject(void)
 {
	friendlyName = S"";
	os = S"";
	comment = S"";
	directory = S"";
	id = 0;
	myHash = NULL;

	filesCount = 0;
	myFiles = new vipPKGFile*[MAXFILES];
	for (int i=0; i<MAXFILES; i++)
		myFiles[i] = NULL;

 }

vipPkgProject::vipPkgProject(vipPkgProject* source)
 {
	myHash = NULL;
	if (source->myHash != NULL)
		myHash = new vipTagHash(source->myHash);

	filesCount = source->filesCount;
	myFiles = new vipPKGFile*[MAXFILES];
	for (int i=0; i<MAXFILES; i++)
	 {
		 if (source->myFiles[i] == NULL)
			myFiles[i] = NULL;
		 else
			myFiles[i] = new vipPKGFile(source->myFiles[i]);
	 }

	id = source->id;
	friendlyName = String::Copy(source->friendlyName);
	os = String::Copy(source->os);
	comment = String::Copy(source->comment);
	directory = String::Copy(source->directory);
 }


vipPkgProject::~vipPkgProject(void)
{
	for (int i=0; i<MAXFILES; i++)
		myFiles[i] = NULL;
}

vipPKGFile* vipPkgProject::Files(unsigned int index)
 {
	if (index >= filesCount)
		return NULL;

	return myFiles[index];
 }

VETRESULT vipPkgProject::SetOutputNameFromClassName(String* name)
 {
	for (int i=0; i<MAXFILES; i++)
	 {
		if (myFiles[i] == NULL)
			continue;

		String* tmpName = Path::GetFileName(myFiles[i]->FileTemplate)->Replace(S"Template", name);
		myFiles[i]->FileOutput = String::Concat(directory, tmpName);
	 }
	return 0;
 }
VETRESULT vipPkgProject::loadFiles()
 {
	for (int i=0; i<MAXFILES; i++)
	 {
		if (myFiles[i] == NULL)
			continue;

		myFiles[i]->loadData();
	 }
	return 0; }

VETRESULT vipPkgProject::ApplyHashes()
 {
	VETRESULT ret = VETRET_OK;

	for (int i=0; i<MAXFILES; i++)
		if ( myFiles[i] != NULL)
		 {
			 if (myFiles[i]->myHash == NULL)
				 myFiles[i]->myHash = myHash;

			 ret += myFiles[i]->ApplyTagHash();
		 }

	 return ret;
 }

VETRESULT vipPkgProject::SaveOutputs()
 {
	VETRESULT ret = VETRET_OK;

	for (int i=0; i<MAXFILES; i++)
		if ( myFiles[i] != NULL)
			ret += myFiles[i]->SaveOutputFile();
	return ret;
 }

VETRESULT vipPkgProject::load( XmlNodeList* items )
 {
	int ret = 0;
	for (int i=0; i<items->Count; i++)
	{
		XmlNode* cN = items->Item(i);

		if ( !cN->Name->CompareTo(S"friendlyName") )
			friendlyName = cN->Attributes->Item(0)->Value;
		else if ( !cN->Name->CompareTo(S"id") )
			id = Convert::ToInt32(cN->Attributes->Item(0)->Value);
		else if ( !cN->Name->CompareTo(S"os") )
			os = cN->Attributes->Item(0)->Value;
		else if ( !cN->Name->CompareTo(S"comment") )
			comment = cN->InnerText;
		else if ( !cN->Name->CompareTo(S"files") )
			{
			for (int j=0; j<cN->ChildNodes->Count; j++)
				{
					XmlNode* fN = cN->ChildNodes->Item(j);
					if (fN == NULL)
						continue;
					vipPKGFile* newFile = new vipPKGFile();
					newFile->load(fN);
					newFile->FileTemplate = String::Concat(templateDirectory, newFile->FileTemplate);
					addFile( newFile );
				}
			}
		else
			ret++;
	}
	return ret;
 }

}