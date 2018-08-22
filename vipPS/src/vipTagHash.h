#pragma once
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
public __gc class vipTagVal
{
public:
	bool enabled;

	String* tag;
	String* value;

	String* comment;

	vipTagVal(String* t) : tag(t) { value=NULL; comment=NULL; enabled=false; };
	vipTagVal(String* t, String* v) : tag(t), value(v) { comment=NULL; enabled=false;};
	vipTagVal(String* t, String* v, String* c) : tag(t), value(v), comment(c) { enabled=false; };

	vipTagVal(vipTagVal* source)
	 {
		enabled = source->enabled;
		tag = String::Copy(source->tag);
		value = String::Copy(source->value);
		comment = String::Copy(source->comment);
	 }

	~vipTagVal() { tag = NULL; value=NULL; comment=NULL;}
};

public __gc class vipDoubleTag
{
public:
	bool enabled;

	String* startTag;
	String* endTag;
	unsigned int maxChars;

	String* comment;

	vipDoubleTag(String* s, String* e) : startTag(s), endTag(e) { maxChars=0; comment=NULL; enabled=false; };
	vipDoubleTag(String* s, String* e, unsigned int m) : startTag(s), endTag(e), maxChars(m) { comment=NULL; enabled=false; };
	vipDoubleTag(String* s, String* e, unsigned int m, String* c) : startTag(s), endTag(e), maxChars(m), comment(c) { enabled=false; };

	vipDoubleTag(vipDoubleTag* source)
	{
		enabled = source->enabled;
		startTag = String::Copy(source->startTag);
		endTag = String::Copy(source->endTag);
		maxChars =  source->maxChars;
		comment = String::Copy(source->comment);
	}

	~vipDoubleTag(){};
};

#define MAXTAGS 64

public __gc class vipTagHash
{
//protected:
public:
	vipTagVal* simpleTags[];
	vipDoubleTag* doubleTags[];

public:
	vipTagHash(void);
	vipTagHash(vipTagHash* source);

	~vipTagHash(void);

	void reset(void);


	VETRESULT loadHash(String* filePah);

	void loadDefaultHash(void);

	VETRESULT addSimpleTag(vipTagVal* data);
	VETRESULT addDoubleTag(vipDoubleTag* data);

	VETRESULT removeSimpleTag(vipTagVal* data);
	VETRESULT removeDoubleTag(vipDoubleTag* data);

	VETRESULT editSimpleTag(String* tag, String* value, bool enabled);
	VETRESULT editDoubleTag(String* starttag, bool enabled);

	void enableAllSimpleTags();
	void enableAllDoubleTags();

	void disableAllSimpleTags();
	void disableAllDoubleTags();

	void disableAll() { disableAllSimpleTags(); disableAllDoubleTags(); };
	void enableAll() { enableAllSimpleTags(); enableAllDoubleTags(); };

	String* ToString();
};



}