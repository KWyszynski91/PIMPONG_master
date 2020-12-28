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
        int x=-8;
        int y=-8;
        int odbiciaPilki=0;
        char kto;
        int punktL=0, punktP=0;
        int sekund=0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerBallTimer(TObject *Sender)
{
        AnsiString lewy, prawy, odbicia;
  //okreslenie toru lotu pilki
        ball->Left+=x;
        ball->Top+=y;
  //odbijanie sie pilki od sciany gornej
        if(ball->Top-5 <= tlo->Top)
        {
         y=-y;
         sndPlaySound("snd/sndwall.wav", SND_ASYNC);
        }

  //odbijanie sie pilki od sciany dolnej
        if(ball->Top+ ball->Height+5 > tlo->Height)
        {
         y=-y;
         sndPlaySound("snd/sndwall.wav", SND_ASYNC);
        }

        //odbicie pileczki od lewej paletki lub prawej
        if((ball->Top > paletka1->Top - ball->Height/2 &&
                ball->Top < paletka1->Top + paletka1->Height &&
                ball->Left < paletka1->Left + paletka1->Width)
                ||
                (ball->Top > paletka2->Top - ball->Height/2 &&
                ball->Top < paletka2->Top + paletka2->Height &&
                ball->Left + ball->Width > paletka2->Left))
                {
        //odbicie pi³eczki srodkiem paletki
                  if(ball->Top + ball->Height/2 >= paletka1->Top + paletka1->Height/2 - 10 &&
                  ball->Top + ball->Height/2 <= paletka1->Top + paletka1->Height/2 + 10 ||
                  ball->Top + ball->Height/2 >= paletka2->Top + paletka2->Height/2 - 10 &&
                  ball->Top + ball->Height/2 <= paletka2->Top + paletka2->Height/2 + 10)
                  {
                    x=-x*2;
                    odbiciaPilki++;
                    Form1->TimerBall->Interval--;
                    sndPlaySound("snd/sndhardpong.wav", SND_ASYNC);
                  }
                  else
                  {
                   x=-x;
                   odbiciaPilki++;
                   sndPlaySound("snd/sndpong.wav", SND_ASYNC);
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
                odbicia=IntToStr(odbiciaPilki);
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
                odbicia=IntToStr(odbiciaPilki);
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
        if(paletka1->Top + paletka1->Height < tlo->Height-10)
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
        if(paletka2->Top + paletka2->Height < tlo->Height-10)
        paletka2->Top +=10;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
        if(Application->MessageBox(
        "Witaj w wirtualnym szaleñstwie tenisa sto³owego! \n"
        "\n"
        "Gracz po lewej niech operuje przyciskami >A< oraz >Z< \n"
        "Gracz po prawej przyciskami strza³ek: >GÓRA< oraz >DÓ£< \n"
        "\n"
        "Gdy odbijesz pi³eczkê œrodkiem paletki - jej prêdkoœæ zwiêkszy siê \n"
        "Im d³u¿ej odbijasz, tym prêdkoœæ p³eczki zwiêksza siê \n"
        "\n"
        "Mi³ej Zabawy! \n",
        "PIMPONG Master", MB_OK)==IDOK)
        {

  //wyzerowanie zliczeñ
        odbiciaPilki=0;
        sekund=0;
        punktL=0;
        punktP=0;
        x=-8, y=-8;
  //wysrodkowanie i wypuszczenie pileczki
        Form1->ball->Left=416;
        Form1->ball->Top=200;
        Form1->TimerBall->Enabled=true;
        Form1->TimerBall->Interval=22;
        Form1->ball->Visible=true;
        Form1->TimerGame->Enabled=true;
  //znikniêcie tablic
                Form1->Label1->Visible=false;
                Form1->Label2->Visible=false;
                Form1->Label3->Visible=false;
                Form1->Button1->Visible=false;
                Form1->Button2->Visible=false;
                Form1->menu->Visible=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  //rozegranie kolejnej rundy
  //wysrodkowanie i wypuszczenie pileczki, wyzerowanie odbic:
        odbiciaPilki=0;
        sekund=0;
        Form1->ball->Left=416;
        Form1->ball->Top=200;
        Form1->TimerBall->Enabled=true;
        Form1->TimerBall->Interval=22;
        Form1->ball->Visible=true;
        Form1->TimerGame->Enabled=true;
        x=x*-1, y=y*-1;
  //znikniêcie tablic
        Form1->Label1->Visible=false;
        Form1->Label2->Visible=false;
        Form1->Label3->Visible=false;
        Form1->Button1->Visible=false;
        Form1->Button2->Visible=false;
        Form1->menu->Visible=false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TimerGameTimer(TObject *Sender)
{
        sekund=sekund+10;
        AnsiString sek;
        sek=IntToStr(sekund);
  //instrukcja wyzwalana co 10 sekund
  Form1->TimerBall->Interval--;
}
//---------------------------------------------------------------------------

