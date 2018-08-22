#include "StdAfx.h"
#include "graphForm.h"
#include "Form1.h"
#include "outputInterface.h"
#include "sourceInterface.h"




namespace vipWS3
{
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;


graphForm::graphForm(void)
 {
	InitializeComponent();
 }

void graphForm::Init(void)
 {
	pB->Image = new Bitmap(pB->Width, pB->Height);
	sourcesUpdate();
	if (cBsources->Items->Count)
		cBsources->SelectedIndex = 0;
 }

System::Void graphForm::graphForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	e->Cancel = true;
	this->Visible = false;
	static_cast<Form1*>(this->MdiParent)->updateChildFormsList();
 }


void graphForm::Dispose(Boolean disposing)
 {
	if (disposing && components)
	{
		components->Dispose();
	}
	__super::Dispose(disposing);
 }

void graphForm::drawSource(Graphics* g, int cX, int cY, int dX, int dY, String* myT)
{
	g->DrawRectangle(new Pen(Color::Red), (float)cX, (float)cY, (float)dX, (float)dY);
	g->FillRectangle(new SolidBrush(Color::DarkCyan), (float)cX, (float)cY, (float)dX, (float)dY);

	Drawing::Font* myF = new Drawing::Font (S"Arial", 8, FontStyle::Regular);
	g->DrawString(myT, myF, new SolidBrush(Color::Black),  RectangleF((float)cX, (float)cY, (float)dX, (float)dY) );

	Drawing::Font* myF2 = new Drawing::Font (S"Times new Roman", 6, FontStyle::Regular);
	StringFormat* dF = new StringFormat(StringFormatFlags::DirectionVertical);
	SizeF textSize2 = g->MeasureString(S"OUT", myF2);
	g->DrawString(S"OUT", myF2, new SolidBrush(Color::Red), (float)(cX+dX) , (float)(cY+dY/2+2), dF);


	myF->Dispose();
	myF2->Dispose();
}

void graphForm::drawOutput(Graphics* g, int cX, int cY, int dX, int dY, String* myT)
 {
	g->DrawRectangle(new Pen(Color::Red), cX, cY, dX, dY);
	g->FillRectangle(new SolidBrush(Color::GreenYellow), cX, cY, dX, dY);

	Drawing::Font* myF = new Drawing::Font (S"Arial", 8, FontStyle::Regular);
	g->DrawString(myT, myF, new SolidBrush(Color::Black),  RectangleF((float)cX, (float)cY, (float)dX, (float)dY) );

	Drawing::Font* myF2 = new Drawing::Font (S"Times new Roman", 6, FontStyle::Regular);
	StringFormat* dF = new StringFormat(StringFormatFlags::DirectionVertical);
	SizeF textSize2 = g->MeasureString(S"OUT", myF2);
	g->DrawString(S"IN", myF2, new SolidBrush(Color::Red), (float)(cX-textSize2.Height-1), (float)(cY+dY/2+2), dF);

	myF->Dispose();
	myF2->Dispose();
 }
void graphForm::drawFilter(Graphics* g, int cX, int cY, int dX, int dY, String* myT)
 {
	g->DrawRectangle(new Pen(Color::Red), cX, cY, dX, dY);
	g->FillRectangle(new SolidBrush(Color::Turquoise), cX, cY, dX, dY);

	Drawing::Font* myF = new Drawing::Font (S"Arial", 10, FontStyle::Regular);
	g->DrawString(myT, myF, new SolidBrush(Color::Black),  RectangleF((float)cX, (float)cY, (float)dX, (float)dY) );

	StringFormat* dF = new StringFormat(StringFormatFlags::DirectionVertical);
	Drawing::Font* myF2 = new Drawing::Font (S"Times new Roman", 6, FontStyle::Regular);
	SizeF textSize = g->MeasureString(S"IN", myF2);
	g->DrawString(S"IN", myF2, new SolidBrush(Color::Black), (float)(cX-textSize.Height-1), (float)(cY+dY/2+2), dF);
	g->DrawString(S"OUT", myF2, new SolidBrush(Color::Black), (float)cX+dX, (float)(cY+dY/2+2), dF);

	myF->Dispose();
	myF2->Dispose();
 }

void graphForm::drawConnector(Graphics* g, int cX, int cY, int dX, int dY, String* myT)
 {
	 g->DrawLine(new Pen(new HatchBrush(HatchStyle::Horizontal, Color::Black, Color::Red), 1), cX, cY+1, dX, dY+1);
	 g->DrawLine(new Pen(Color::Black, 3), cX, cY, dX, dY);
 }

void graphForm::doDrawFilterLoop(sourceInterface* firstSource, Graphics* g,int& pX, int& pY, int& dimX, int& dimY)
 {
	 sourceInterface* currentSource = firstSource;

	 while ( currentSource != NULL && currentSource->getOutputInterface() != NULL )
	 {
		drawConnector(g, pX, pY+dimY/2, pX+40, pY+dimY/2, S"");
		pX = pX + 40;

		Object* nO = currentSource->getOutputInterface()->getObjectInstance();

		if (nO == NULL)
			return;

		if ( nO->GetType()->GetInterface("sourceInterface") )
		 {
			drawFilter(g, pX, pY, dimX, dimY, dynamic_cast<Form*>(nO)->Text);
			pX = pX + dimX;
			currentSource = dynamic_cast<sourceInterface*>(nO);
		 }
		else
		 {
			drawOutput(g, pX, pY, dimX, dimY, dynamic_cast<Form*>(nO)->Text);
			currentSource = NULL;
		 }
	 }

 }

System::Void graphForm::button1_Click(System::Object *  sender, System::EventArgs *  e)
 {
	Graphics* g = Graphics::FromImage(pB->Image);
	g->Clear(Color::Beige);

	if ( sF == NULL )
		return;

	int pX = 120;
	int pY = 20;
	int dimX = 100;
	int dimY = 60;

	drawSource(g, 20, pY, dimX, dimY, dynamic_cast<Form*>(sF)->Text);

	doDrawFilterLoop(sF, g, pX, pY, dimX, dimY);

	this->Refresh();

 }


}