#include "StdAfx.h"
#include "intSourceImageForm.h"
#include "Form1.h"


namespace vipWS3
{

intSourceImageForm::intSourceImageForm(void)
 {
	InitializeComponent();
	buffer = NULL;
	vF = NULL;
 }

System::Void intSourceImageForm::intSourceImageForm_Load(System::Object *  sender, System::EventArgs *  e)
 {
	lastPath = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\samples");
	lastPath->Copy( tBfolder->Text );

	String* path = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\reference\\internalSourceImage.info.rtf");
	if ( File::Exists(path) )
		rTBinfo->LoadFile(path , RichTextBoxStreamType::RichText);
	else
	{
		rTBinfo->Text = "ERROR\r\n\r\nCouln't load data file: \r\n";
		rTBinfo->AppendText(path);
	}

	 viewsUpdate();
	 if (cBviews->Items->Count)
		cBviews->SelectedIndex = 0;

 }

System::Void intSourceImageForm::intSourceImageForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->updateChildFormsList();
 }



void intSourceImageForm::Dispose(Boolean disposing)
 {
	myImage = NULL;

	if (buffer != NULL)
	 {
		static_cast<Form1*>(this->MdiParent)->writeLog(S"Freeing Buffer..", this);
		delete buffer;
	 }

	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying Interface..", this);

	if (disposing && components)
	{
		components->Dispose();
	}
	__super::Dispose(disposing);
 }


System::Void intSourceImageForm::button4_Click(System::Object *  sender, System::EventArgs *  e)
 {
	lBfiles->Items->Clear();
	if (!tBfolder->Text->Substring(tBfolder->Text->Length-1, 1)->CompareTo("\\") )
		tBfolder->Text = String::Concat(tBfolder->Text, S"\\");
	if ( Directory::Exists(tBfolder->Text) )
	 {
		DirectoryInfo* di = new DirectoryInfo(tBfolder->Text);
		FileInfo* fi[] = di->GetFiles();
		Collections::IEnumerator* myEnum = fi->GetEnumerator();
		while ( myEnum->MoveNext() )
		 {
			FileInfo* fiTemp = __try_cast<FileInfo*>(myEnum->Current);
			if (!cBfilter->Checked)
                lBfiles->Items->Add(fiTemp->Name);
			else
			 {
				if (fiTemp->Extension->ToUpper()->CompareTo("BMP") ||
					fiTemp->Extension->ToUpper()->CompareTo("JPG") ||
					fiTemp->Extension->ToUpper()->CompareTo("JPEG") ||
					fiTemp->Extension->ToUpper()->CompareTo("GIF") ||
					fiTemp->Extension->ToUpper()->CompareTo("WMF") ||
					fiTemp->Extension->ToUpper()->CompareTo("TIFF") ||
					fiTemp->Extension->ToUpper()->CompareTo("EMF") ||
					fiTemp->Extension->ToUpper()->CompareTo("EXIF") ||
					fiTemp->Extension->ToUpper()->CompareTo("PNG")
					)

						lBfiles->Items->Add(fiTemp->Name);
			}
		 }
	 }
 }

System::Void intSourceImageForm::button5_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (lBfiles->SelectedIndex == -1)
	 {
		MessageBox::Show(this, S"Select an image first..", this->Text, MessageBoxButtons::OK );
		return;
	 }

	static_cast<Form1*>(this->MdiParent)->writeLog(String::Format(S"Loading image.. [{0}]", tBfile->Text), this);

	String* path = String::Concat( tBfile->Text );
	if ( File::Exists(tBfile->Text) )
	 {
		if (myImage != 0)
			myImage->Dispose();

		myImage = new Bitmap(path);
		pictureBox1->Image = myImage;

		loadData();

		updateImageInfos();

	 }
	else
	 {
		MessageBox::Show(this, S"File not found", this->Text, MessageBoxButtons::OK );
		return;
	 }

 }


System::Void intSourceImageForm::button6_Click(System::Object *  sender, System::EventArgs *  e)
 {
	openFileDialog1->InitialDirectory = lastPath;

	if ( openFileDialog1->ShowDialog() == DialogResult::OK )
	 {
		if (myImage != 0)
			myImage->Dispose();

		myImage = new Bitmap(openFileDialog1->FileName);
		pictureBox1->Image = myImage;

		tBfile->Text = openFileDialog1->FileName;

		if (buffer != NULL)
			delete buffer;

		buffer = new vipFrameRGB24(myImage->Width, myImage->Height);

		loadData();
		updateImageInfos();
	 }
 }


void intSourceImageForm::loadData(void)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Updating buffer..", this);

	if (buffer != NULL && myImage->Width != buffer->width && myImage->Height != buffer->height)
	 {
		delete buffer;
		buffer = new vipFrameRGB24(myImage->Width, myImage->Height);
	 }
	else if (buffer == NULL)
		buffer = new vipFrameRGB24(myImage->Width, myImage->Height);

	static_cast<Form1*>(this->MdiParent)->writeLog(S"Filling buffer..", this);

	// slow but done only once
	Color pxCol;
	for (unsigned int x=0; x< buffer->width; x++)
	 {
		for (unsigned int y=0; y< buffer->height; y++)
		 {
			pxCol = myImage->GetPixel(x, y);
			buffer->data[y*buffer->width+x][0] = pxCol.R;
			buffer->data[y*buffer->width+x][1] = pxCol.G;
			buffer->data[y*buffer->width+x][2] = pxCol.B;
		 }
	 }
 }


System::Void intSourceImageForm::button1_Click(System::Object *  sender, System::EventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"PUSHING frame..", this);
	if (vF && buffer)
		vF->importFrom(buffer);
 }





VIPRESULT intSourceImageForm::extractTo(vipFrameRGB24* img)
 {
	if (buffer != NULL)
	 {
		if (img == NULL)
		 {
			static_cast<Form1*>(this->MdiParent)->writeLog(S"Extracting frame.. (got NULL, so a new frame will be created)", this);
			img = new vipFrameRGB24(*buffer);
		 }
		else
		 {
			static_cast<Form1*>(this->MdiParent)->writeLog(S"Extracting frame.. (copying frame data)", this);
			*img = *buffer; // copy constr
		 }
		return VIPRET_OK;
	 }
	else
	 {
		static_cast<Form1*>(this->MdiParent)->writeLog(S"FALIED: Extracting frame! (buffer is EMPTY)", this);
	 }
	return VIPRET_ILLEGAL_USE;
 }







}