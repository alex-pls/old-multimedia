#pragma once

namespace vipPS
{

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Xml;

	public __gc class vipClassType
	{
	private:

		int id;
		String* friendlyName;
		String* interfaceFileName;
		String* classPrefix;
		String* implementationsDirName;
		String* templateFileName;
		String* comment;

	public:
		vipClassType(void)
		{
			id = 0;
			friendlyName = S"";
			interfaceFileName  = S"";
			classPrefix = S"";
			implementationsDirName = S"";
			templateFileName = S"";
			comment = S"";
		}

		vipClassType(int i, String *fn, String *ifn, String *cp, String *idn, String *tfn, String *c)
		{
			id = i;
			friendlyName = fn;
			interfaceFileName  = ifn;
			classPrefix = cp;
			implementationsDirName = idn;
			templateFileName = tfn;
			comment = c;
		}


		int load( XmlNodeList* items )
		 {
			int ret = 0;
			 for (int i=0; i<items->Count; i++)
			  {
				  XmlNode* cN = items->Item(i);

				  if ( !cN->Name->CompareTo(S"classPrefix") )
					  classPrefix = cN->Attributes->Item(0)->Value;
				  else if ( !cN->Name->CompareTo(S"friendlyName") )
					  friendlyName = cN->Attributes->Item(0)->Value;
				  else if ( !cN->Name->CompareTo(S"interfaceFileName") )
					  interfaceFileName = cN->Attributes->Item(0)->Value;
				  else if ( !cN->Name->CompareTo(S"implementationsDirName") )
					  implementationsDirName = cN->Attributes->Item(0)->Value;
				  else if ( !cN->Name->CompareTo(S"templateFileName") )
					  templateFileName = cN->Attributes->Item(0)->Value;
				  else if ( !cN->Name->CompareTo(S"classID") )
					  id = Convert::ToInt32(cN->Attributes->Item(0)->Value);
				  else if ( !cN->Name->CompareTo(S"comment") )
					  comment = cN->InnerText;
				  else
					  ret++;
			  }
			return ret;
		 }

		__property int get_ItemID()
		{
			return id;
		}

		__property void set_ItemID(int value)
		{
			id = value;
		}

		__property String *get_FriendlyName()
		{
			return friendlyName;
		}

		__property void set_FriendlyName(String *value)
		{
			friendlyName = value;
		}

		__property String *get_InterfaceFileName()
		{
			return interfaceFileName;
		}

		__property void set_InterfaceFileName(String *s)
		{
			interfaceFileName = s;
		}

		__property String *get_ClassPrefix()
		{
			return classPrefix;
		}

		__property void set_ClassPrefix(String *s)
		{
			classPrefix = s;
		}

		__property String *get_ImplementationsDirName()
		{
			return implementationsDirName;
		}

		__property void set_ImplementationsDirName(String *s)
		{
			implementationsDirName = s;
		}

		__property String *get_TemplateFileName()
		{
			return templateFileName;
		}

		__property void set_TemplateFileName(String *s)
		{
			templateFileName = s;
		}

		__property void set_Comment(String *s)
		{
			comment = s;
		}

		__property String *get_Comment()
		{
			return comment;
		}

		virtual String *ToString()
		{
			return String::Concat(friendlyName, S" [", interfaceFileName, S"]");
		}

		String* ToBigString()
		{
			StringBuilder* strB = new StringBuilder(1024);
			strB->Append(S"\r\n");
			strB->AppendFormat(S" ItemID:\t\t{0}\r\n", id.ToString() );
			strB->AppendFormat(S" FriendlyName:\t{0}\r\n", friendlyName );
			strB->AppendFormat(S" interfaceFileName:\t{0}\r\n", interfaceFileName );
			strB->AppendFormat(S" templateFileName:\t{0}\r\n", templateFileName );
			strB->AppendFormat(S" ClassPrefix:\t{0}\r\n", classPrefix);
			strB->AppendFormat(S" ImplementationsDirName:\t{0}\r\n", implementationsDirName );
			strB->AppendFormat(S" Comment:\t{0}\r\n", comment );

			String* val = strB->ToString();
			strB = NULL;
			return val;
		}

	};

}

