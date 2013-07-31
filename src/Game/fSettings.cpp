// ---------------------------------------------------------------------------
// Russian Roulette is PC version of popular television game show.
// Copyright (C) 2010-2013 Popovskiy Andrey
// Copyright (C) 2010-2013 Boytsov Sergey

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ---------------------------------------------------------------------------
#include "pch.h"
#include "fSettings.h"
#include "MainForm.h"
#include "audio.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingsForm *SettingsForm;

// ---------------------------------------------------------------------------
__fastcall TSettingsForm::TSettingsForm(TComponent *Owner) : TForm(Owner) { }

// ---------------------------------------------------------------------------
void __fastcall TSettingsForm::FormShow(TObject *) {
    TSettings *Settings = TSettings::Instance();
    cmbListOfBases->Items->Assign(Settings->BaseNames);

    std::map <String, String> ::iterator it;
    for (it = Settings->BaseFiles.begin(); it != Settings->BaseFiles.end(); ++it) {
        if (it->second == Settings->LastBase) {
            for (int i = 0; i < cmbListOfBases->Items->Count; ++i) {
                if (it->first == cmbListOfBases->Items->Strings[i]) {
                    cmbListOfBases->ItemIndex = i;
                    break;
                }
            }
        }
    }

    edPlayer0->Text = Settings->PlayerNames[0];
    edPlayer1->Text = Settings->PlayerNames[1];
    edPlayer2->Text = Settings->PlayerNames[2];
    edPlayer3->Text = Settings->PlayerNames[3];
    edPlayer4->Text = Settings->PlayerNames[4];

    cmbPlayerType0->ItemIndex = (int)(Settings->PlayerType[0]);
    cmbPlayerType1->ItemIndex = (int)(Settings->PlayerType[1]);
    cmbPlayerType2->ItemIndex = (int)(Settings->PlayerType[2]);
    cmbPlayerType3->ItemIndex = (int)(Settings->PlayerType[3]);
    cmbPlayerType4->ItemIndex = (int)(Settings->PlayerType[4]);

	cbSoundOnOff->Checked = Settings->SoundEnabled;
	cbMusicOnOff->Checked = Settings->MusicEnabled;

    cbFullscreen->Checked = Settings->Fullscreen;

    tbSoundVolume->Position = Settings->SoundVolume;
	tbMusicVolume->Position = Settings->MusicVolume;

    // «режим ведущего» отныне и навеки работает ТОЛЬКО при наличии
    // 2-х и более подключенных мониторов к ПК
    if (Screen->MonitorCount > 1) {
        cbHostModeOnOff->Checked = Settings->HostMode;
        cbHostModeOnOff->Enabled = 1;
    } else {
        cbHostModeOnOff->Checked = false;
        cbHostModeOnOff->Enabled = false;
    }

}
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::FormCreate(TObject *) {
    btnCancel->Caption = "Cancel";
    btnOK->Caption = "OK";
    gbPlayerNames->Caption = "Имена игроков";
    gbChooseQuestionBase->Caption = "База вопросов для игры";
    gbOptions->Caption = "Опции игры";
    cbSoundOnOff->Caption = "Включить звук";
    cbMusicOnOff->Caption = "Включить музыку";
    cbFullscreen->Caption = "Полный экран";
    cbHostModeOnOff->Caption = "Режим ведущего";
    tbSoundVolumeChange(NULL);
    tbMusicVolumeChange(NULL);
    cbSoundOnOffClick(NULL);
    cbMusicOnOffClick(NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::btnCancelClick(TObject *) {
    SettingsForm->Hide();
    SettingsForm->Close();
}

// -----------------------------------------------------------------------------
void __fastcall TSettingsForm::btnOKClick(TObject *) {
    TSettings *Settings = TSettings::Instance();
    Settings->PlayerNames[0] = edPlayer0->Text;
    Settings->PlayerNames[1] = edPlayer1->Text;
    Settings->PlayerNames[2] = edPlayer2->Text;
    Settings->PlayerNames[3] = edPlayer3->Text;
    Settings->PlayerNames[4] = edPlayer4->Text;

    Settings->PlayerType[0] = (TBotType)cmbPlayerType0->ItemIndex;
    Settings->PlayerType[1] = (TBotType)cmbPlayerType1->ItemIndex;
    Settings->PlayerType[2] = (TBotType)cmbPlayerType2->ItemIndex;
    Settings->PlayerType[3] = (TBotType)cmbPlayerType3->ItemIndex;
    Settings->PlayerType[4] = (TBotType)cmbPlayerType4->ItemIndex;

	Settings->SoundEnabled = cbSoundOnOff->Checked;
    Settings->SoundVolume = tbSoundVolume->Position;
	if (Settings->SoundEnabled) {
		SetVolumeSFX(tbSoundVolume->Position / (float) tbSoundVolume->Max);
	}
	else { SetVolumeSFX(0); }
	Settings->MusicEnabled = cbMusicOnOff->Checked;
	Settings->MusicVolume = tbMusicVolume->Position;
	if (Settings->MusicEnabled) {
		SetVolumeMusic(tbMusicVolume->Position / (float) tbMusicVolume->Max);
	}
	else { SetVolumeMusic(0); }
	SetVolumeMusic(tbMusicVolume->Position / (float) tbMusicVolume->Max);
    Settings->Fullscreen = cbFullscreen->Checked;
    Settings->HostMode = cbHostModeOnOff->Checked;

    Settings->LastBase = Settings->BaseFiles[cmbListOfBases->Items->Strings[cmbListOfBases->ItemIndex]];
    Settings->SaveToFile();

    SettingsForm->Hide();
    SettingsForm->Close();
}
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::tbSoundVolumeChange(TObject *) {
    lblSoundVolume->Caption = "Громкость звука: " + IntToStr(tbSoundVolume->Position) + "%"; }
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::tbMusicVolumeChange(TObject *) {
    lblMusicVolume->Caption = "Громкость музыки: " + IntToStr(tbMusicVolume->Position) + "%"; }
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::cbSoundOnOffClick(TObject *) {
    tbSoundVolume->Enabled = cbSoundOnOff->Checked;
    lblSoundVolume->Enabled = cbSoundOnOff->Checked;
}
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::cbMusicOnOffClick(TObject *) {
    tbMusicVolume->Enabled = cbMusicOnOff->Checked;
    lblMusicVolume->Enabled = cbMusicOnOff->Checked;
}
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::addBaseClick(TObject *) {
    if (OpenDialog1->Execute()) {
        WCHAR *from = (OpenDialog1->FileName).w_str();
        WCHAR *to = (".\\Base\\" + ExtractFileName(OpenDialog1->FileName)).w_str();
        if (CopyFileW(from, to, 0)) {
            String name = InputBox("Русская рулетка :: Добавить базу", "Введите имя новой базы",
                ExtractFileName(OpenDialog1->FileName));
            TSettings *Settings = TSettings::Instance();
            Settings->BaseFiles[name] = OpenDialog1->FileName;

            cmbListOfBases->Clear();

            std::map <String, String> ::iterator it;
            for (it = Settings->BaseFiles.begin(); it != Settings->BaseFiles.end(); ++it) {
                cmbListOfBases->Items->Add(it->first);
            }
            cmbListOfBases->ItemIndex = cmbListOfBases->Items->Count - 1;
        } else {
            ShowMessage("Ошибка добавления базы =(");
        }
    }
}

// ---------------------------------------------------------------------------
void LoadFormPosition(TForm *form) {
	TSettings *Settings = TSettings::Instance();

	if (Settings->Fullscreen) {
		form->BorderStyle = bsNone;
		form->Width = Screen->Width;
		form->Height = Screen->Height;
		form->Top = 0;
		form->Left = 0;
	} else {
		form->BorderStyle = bsSizeable;
		form->Width = Settings->FormsWidth;
		form->Height = Settings->FormsHeight;
		form->Left = Settings->FormsLeft;
		form->Top = Settings->FormsTop;
	}
}

void SaveFormPosition(TForm *form) {
    TSettings *Settings = TSettings::Instance();

    if (!Settings->Fullscreen) {
        Settings->FormsWidth = form->Width;
        Settings->FormsHeight = form->Height;
        Settings->FormsTop = form->Top;
        Settings->FormsLeft = form->Left;
    }
}
// ---------------------------------------------------------------------------

void CoolPositionFix(TForm *form) {
    /* АЦЦКИЙ КОСТЫЛЬ
     суть в том, что после перевода формы в состояние Borderless
     она самопроизвольно сдвигается влево, что не есть гут
     при этом контролировать это смещение из LoadFormPosition()
     не представляется возможным =(
     */
    if (form->Top < 0) {
        form->Top = 0;
    }
    if (form->Left < 0) {
        form->Left = 0;
    }
}
// ---------------------------------------------------------------------------

void SwitchFullscreen(TForm *form) {
    TSettings *Settings = TSettings::Instance();

    Settings->Fullscreen = !Settings->Fullscreen;
    LoadFormPosition(form);
}
