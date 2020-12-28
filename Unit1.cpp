//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "mmsystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

  //tor pikseli
        int x=8;
        int y=8;
        //zmiana prêdkosci:
        int xFast=16;
        int xSlow=12;
        int bounceCounts=0;
        int bounceFasterCounts=0;
        int fasterMoveAfterXBounce=1;
        int acceleration=1;
        int initialBallInterval=30;
        char kto;
        int punktL=0, punktP=0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        //powitanie:
        AnsiString strHello ="Witaj w wirtualnym szaleñstwie tenisa sto³owego!";
        AnsiString strLeftPlayer ="Gracz po lewej niech operuje przyciskami >A< oraz >Z<";
        AnsiString strRightPlayer ="Gracz po prawej przyciskami strza³ek: >GÓRA< oraz >DÓ£<";
        AnsiString strInfo1 ="Gdy odbijesz pi³eczkê œrodkiem paletki - jej prêdkoœæ zwiêkszy siê";
        AnsiString strInfo2 ="Im d³u¿ej odbijasz, tym prêdkoœæ p³eczki zwiêksza siê";
        AnsiString strFinal ="Mi³ej Zabawy!";

        ShowMessage(strHello +sLineBreak+sLineBreak+ strLeftPlayer +sLineBreak+ strRightPlayer +sLineBreak+sLineBreak+
        strInfo1 +sLineBreak+ strInfo2 +sLineBreak+sLineBreak+ strFinal);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerBallTimer(TObject *Sender)
{
        AnsiString lewy, prawy, odbicia;
  //okreslenie toru lotu pilki
        ball->Left+=x;
        ball->Top+=y;
  //odbijanie sie pilki od sciany gornej
        if(ball->Top-5 <= background->Top)
        {
         y=-y;
         sndPlaySound("snd/sndwall.wav", SND_ASYNC);
        }

  //odbijanie sie pilki od sciany dolnej
        if(ball->Top+ ball->Height+5 > background->Height)
        {
         y=-y;
         sndPlaySound("snd/sndwall.wav", SND_ASYNC);
        }

        //odbicie pileczki od lewej paletki
                if(ball->Top > paletka1->Top - ball->Height/2 &&
                   ball->Top < paletka1->Top + paletka1->Height &&
                   ball->Left < paletka1->Left + paletka1->Width)
                {
                   if(x<0)
                    {
                     bounceCounts++;
        //odbicie pi³eczki srodkiem paletki lewej:
                  if(ball->Top + ball->Height/2 >= paletka1->Top + paletka1->Height/2 - 10 &&
                  ball->Top + ball->Height/2 <= paletka1->Top + paletka1->Height/2 + 10)
                   {
                    x=xFast;
                    sndPlaySound("snd/sndhardpong.wav", SND_ASYNC);
                   }
                  else
                   {
                    x=xSlow;
                    sndPlaySound("snd/sndpong.wav", SND_ASYNC);
                   }
                        if (bounceFasterCounts >= fasterMoveAfterXBounce)
                         {
                           bounceFasterCounts=0;
                            if (TimerBall->Interval-acceleration > 0)
                                TimerBall->Interval -= acceleration;
                          }
                         else
                           bounceFasterCounts++;
                     }
                   }

        //odbicie pileczki od prawej paletki:
                if(ball->Top > paletka2->Top - ball->Height/2 &&
                   ball->Top < paletka2->Top + paletka2->Height &&
                   ball->Left + ball->Width > paletka2->Left)
                   {
                   if(x>0)
                    {
                     bounceCounts++;
        //odbicie pi³eczki srodkiem paletki prawej:
                  if(ball->Top + ball->Height/2 >= paletka2->Top + paletka2->Height/2 - 10 &&
                     ball->Top + ball->Height/2 <= paletka2->Top + paletka2->Height/2 + 10)
                     {
                       x=-xFast;
                       sndPlaySound("snd/sndhardpong.wav", SND_ASYNC);
                     }
                  else
                   {
                    x=-xSlow;
                    sndPlaySound("snd/sndpong.wav", SND_ASYNC);
                   }
                        if (bounceFasterCounts >= fasterMoveAfterXBounce)
                         {
                           bounceFasterCounts=0;
                            if (TimerBall->Interval-acceleration > 0)
                                TimerBall->Interval -= acceleration;
                          }
                         else
                           bounceFasterCounts++;
                     }
           }

  //skucha paletki lewej lub prawej:
        else if(ball->Left < paletka1->Left )
        {
          TimerBall->Enabled=false;
          ball->Visible=false;
          kto='L';  //kto skusi³
          punktP++; //kto zdobywa punkt
                lewy=IntToStr(punktL);
                prawy=IntToStr(punktP);
                odbicia=IntToStr(bounceCounts);
                Form1->menu->Visible=true;
                Form1->Label1->Caption="Punkt zdobywa gracz po prawej! >>";
                Form1->Label1->Visible=true;
                Form1->Label2->Caption= lewy+" : "+prawy;
                Form1->Label2->Visible=true;
                Form1->Label3->Caption="Odbicia pi³eczki: "+odbicia;
                Form1->Label3->Visible=true;
                Form1->Button1->Visible=true;
                Form1->Button2->Visible=true;
        }
        else if(ball->Left >= paletka2->Left + paletka2->Width+15)
        {
          TimerBall->Enabled=false;
          ball->Visible=false;
          kto='P';  //kto skusi³
          punktL++; //kto zdobywa punkt
                lewy=IntToStr(punktL);
                prawy=IntToStr(punktP);
                odbicia=IntToStr(bounceCounts);
                Form1->menu->Visible=true;
                Form1->Label1->Caption="<< Punkt zdobywa gracz po lewej!";
                Form1->Label1->Visible=true;
                Form1->Label2->Caption= lewy+" : "+prawy;
                Form1->Label2->Visible=true;
                Form1->Label3->Caption="Odbicia pi³eczki: "+odbicia;
                Form1->Label3->Visible=true;
                Form1->Button1->Visible=true;
                Form1->Button2->Visible=true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::p1goraTimer(TObject *Sender)
{
  //przesuwanie paletki1 w górê:
        if(paletka1->Top>10)
        paletka1->Top -=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::p1dolTimer(TObject *Sender)
{
  //przesuwanie paletki1 w dó³:
        if(paletka1->Top + paletka1->Height < background->Height-10)
        paletka1->Top +=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  //wymuszenie ruchu paletki1:
        if(Key == 'A' ) p1gora->Enabled=true;
        if(Key == 'Z' ) p1dol->Enabled=true;
  //wymuszenie ruchu paletki2:
        if(Key == VK_UP ) p2gora->Enabled=true;
        if(Key == VK_DOWN ) p2dol->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  //zatrzymanie ruchu paletki1:
        if(Key == 'A' ) p1gora->Enabled=false;
        if(Key == 'Z' ) p1dol->Enabled=false;
  //zatrzymanie ruchu paletki2:
        if(Key == VK_UP ) p2gora->Enabled=false;
        if(Key == VK_DOWN ) p2dol->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::p2goraTimer(TObject *Sender)
{
  //przesuwanie paletki2 w górê:
        if(paletka2->Top>10)
        paletka2->Top -=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::p2dolTimer(TObject *Sender)
{
  //przesuwanie paletki2 w dó³:
        if(paletka2->Top + paletka2->Height < background->Height-10)
        paletka2->Top +=10;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{

  //wyzerowanie zliczeñ
        bounceCounts=0;
        bounceFasterCounts=0;
        punktL=0;
        punktP=0;
        if(x<0)
        x=xSlow;
        else
        x=-xSlow;
  //wysrodkowanie i wypuszczenie pileczki
        paletka1->Top=160;
        paletka2->Top=160;
        Form1->ball->Left=416;
        Form1->ball->Top=200;
        Form1->TimerBall->Enabled=true;
        Form1->TimerBall->Interval=initialBallInterval;
        Form1->ball->Visible=true;
  //znikniêcie tablic
                Form1->Label1->Visible=false;
                Form1->Label2->Visible=false;
                Form1->Label3->Visible=false;
                Form1->Button1->Visible=false;
                Form1->Button2->Visible=false;
                Form1->menu->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  //rozegranie kolejnej rundy
  //wysrodkowanie i wypuszczenie pileczki, wyzerowanie odbic:
        bounceCounts=0;
        bounceFasterCounts=0;
        Form1->ball->Left= background->Width/2;
        Form1->ball->Top=background->Height/2;
        Form1->TimerBall->Enabled=true;
        Form1->TimerBall->Interval=initialBallInterval;
        Form1->ball->Visible=true;
        if(x<0)
          x=xSlow;
        else
          x=-xSlow;
  //wysrodkowanie paletek:
        paletka1->Top=160;
        paletka2->Top=160;
  //znikniêcie tablic
        Form1->Label1->Visible=false;
        Form1->Label2->Visible=false;
        Form1->Label3->Visible=false;
        Form1->Button1->Visible=false;
        Form1->Button2->Visible=false;
        Form1->menu->Visible=false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

