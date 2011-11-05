/*  This file is part of UKNCBTL.
    UKNCBTL is free software: you can redistribute it and/or modify it under the terms
of the GNU Lesser General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.
    UKNCBTL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for more details.
    You should have received a copy of the GNU Lesser General Public License along with
UKNCBTL. If not, see <http://www.gnu.org/licenses/>. */

// main.cpp

#include "stdafx.h"
#include "Emulator.h"


void Test1_MenuAndSelfTest()
{
    Test_LogInfo(_T("TEST 1: Menu & Self Test"));
    Emulator_Reset();

    Emulator_Run(75);  // Boot: 3 seconds

    Test_CheckScreenshot(_T("data\\test01_1.bmp"));  // Boot menu

    Emulator_KeyboardPressRelease(0152);  // "���"
    Emulator_Run(5);
    Test_CheckScreenshot(_T("data\\test01_2.bmp"));  // Settings menu
    Emulator_KeyboardPressRelease(0134);  // "Down arrow"
    Emulator_Run(3);
    Emulator_KeyboardPressRelease(0134);  // "Down arrow"
    Emulator_Run(3);
    Emulator_KeyboardPressRelease(0134);  // "Down arrow"
    Emulator_Run(3);
    Test_CheckScreenshot(_T("data\\test01_3.bmp"));  // Settings menu: colors
    Emulator_KeyboardPressRelease(0151);  // "���"
    Emulator_Run(5);

    Emulator_KeyboardPressRelease(0016);  // "7"
    Emulator_KeyboardPressRelease(0153);  // "Enter"

    Emulator_Run(20);

    Test_CheckScreenshot(_T("data\\test01_4.bmp"));  // Self test pass 1

    Emulator_Run(25 * 200);

    Test_CheckScreenshot(_T("data\\test01_5.bmp"));  // Self test pass 2
    //Emulator_SaveScreenshot(_T("test01_5.bmp"));
}

void Test2_RomBasic()
{
    Test_LogInfo(_T("TEST 2: Boot ROM BASIC"));
    Emulator_Reset();

    BOOL res = Emulator_LoadROMCartridge(1, _T("romctr_basic.bin"));
    if (!res)
    {
        Test_LogError(_T("Failed to load ROM BASIC cartridge."));
        exit(1);
    }

    Emulator_Run(75);  // Boot: 3 seconds

    Emulator_KeyboardPressRelease(0031);  // "2"
    Emulator_KeyboardPressRelease(0153);  // "Enter"

    Emulator_Run(100);  // Boot BASIC: 5 seconds

    Test_CheckScreenshot(_T("data\\test02_1.bmp"));

    // 10 FOR I=32 TO 255
    Emulator_KeyboardSequence("10 FOR I");
    Emulator_KeyboardPressReleaseShift(0175);  // "="
    Emulator_KeyboardSequence("32 TO 255\n");
    // 20 PRINT CHR$(I);
    Emulator_KeyboardSequence("20 PRINT CHR");
    Emulator_KeyboardPressReleaseShift(0013);  // "$"
    Emulator_KeyboardPressReleaseShift(0017);  // "("
    Emulator_KeyboardPressRelease(0073);  // "I"
    Emulator_KeyboardPressReleaseShift(0177);  // ")"
    Emulator_KeyboardSequence(";\n");
    // 30 IF I MOD 16 = 15 THEN PRINT
    Emulator_KeyboardSequence("30 IF I MOD 16 ");
    Emulator_KeyboardPressReleaseShift(0175);  // "="
    Emulator_KeyboardSequence(" 15 THEN PRINT\n");
    // 50 NEXT I
    Emulator_KeyboardSequence("50 NEXT I\n");

    Emulator_KeyboardPressRelease(0015);  // "K5" == run
    Emulator_Run(25);  // Wait 1 second

    Test_CheckScreenshot(_T("data\\test02_2.bmp"));
}

void Test3_FTMON()
{
    Test_LogInfo(_T("TEST 3: FODOSTM1"));
    Emulator_Reset();

    Test_CopyFile(_T("data\\FODOSTM1.DSK"), _T("temp\\FODOSTM1.DSK"));

    Emulator_AttachFloppyImage(0, _T("temp\\FODOSTM1.DSK"));
    //TODO: Check error

    Emulator_Run(75);  // Boot: 3 seconds
    Emulator_KeyboardSequence("1\n");
    Emulator_Run(200);  // Boot from the disk: 8 seconds

    // Turn off the timer
    Emulator_KeyboardPressRelease(0152);  // "���"
    Emulator_Run(5);
    Emulator_KeyboardPressReleaseChar('8');  // Timer
    Emulator_Run(5);
    Emulator_KeyboardPressRelease(0133);  // Right arrow
    Emulator_Run(5);
    Emulator_KeyboardPressReleaseChar('2');  // Off
    Emulator_Run(5);
    Emulator_KeyboardPressRelease(0151);  // "���"
    Emulator_Run(10);

    // Run the tests
    Emulator_KeyboardSequence("R FTMON\n");
    Emulator_Run(50);  // Loading FTMON
    Emulator_KeyboardSequence("D\n");  // Description
    Emulator_Run(100);
    Test_CheckScreenshot(_T("data\\test03_1.bmp"));
    Emulator_KeyboardSequence("O 791401\n");
    Emulator_Run(50);
    Emulator_KeyboardSequence("O 791402\n");
    Emulator_Run(50);
    Emulator_KeyboardSequence("O 691404\n");
    Emulator_Run(66);
    Test_CheckScreenshot(_T("data\\test03_2.bmp"));

    Emulator_Reset();
}

void Test4_Games()
{
    Test_LogInfo(_T("TEST 4: Games"));
    Emulator_Reset();

    Test_CopyFile(_T("data\\disk1.dsk"), _T("temp\\disk1.dsk"));
    Test_CopyFile(_T("data\\game.dsk"), _T("temp\\game.dsk"));

    Emulator_AttachFloppyImage(0, _T("temp\\disk1.DSK"));
    //TODO: Check error
    Emulator_AttachFloppyImage(1, _T("temp\\game.DSK"));
    //TODO: Check error

    Emulator_Run(75);  // Boot: 3 seconds
    Emulator_KeyboardSequence("1\n");
    Emulator_Run(200);  // Boot: 8 seconds
    Emulator_KeyboardSequence("01-01-99\n\n\n");  // Date
    Emulator_Run(75);  // Boot: 3 seconds
    Emulator_KeyboardSequence("RU MZ1:GOBLIN\n");
    Emulator_Run(200);  // 8 seconds
    Test_CheckScreenshot(_T("data\\test04_1.bmp"));  // Title screen
    Emulator_Run(300);  // 12 seconds
    Emulator_KeyboardPressRelease(0153);  // "Enter"
    Emulator_Run(25);
    Test_CheckScreenshot(_T("data\\test04_2.bmp"));  // Game start screen

    Emulator_Reset();

    Emulator_Run(75);  // Boot: 3 seconds
    Emulator_KeyboardSequence("1\n");
    Emulator_Run(200);  // Boot: 8 seconds
    Emulator_KeyboardSequence("01-01-99\n\n\n");
    Emulator_Run(75);  // Boot: 3 seconds
    Emulator_KeyboardSequence("RU MZ1:DIGGER\n");
    Emulator_Run(400);  // Skip titles
    Emulator_KeyboardSequence("1");  // Game rank
    Emulator_Run(120);
    Test_CheckScreenshot(_T("data\\test04_3.bmp"));

    Emulator_Reset();

    Emulator_Run(75);  // Boot: 3 seconds
    Emulator_KeyboardSequence("1\n");
    Emulator_Run(200);  // Boot: 8 seconds
    Emulator_KeyboardSequence("01-01-99\n\n\n");
    Emulator_Run(75);  // Boot: 3 seconds
    Emulator_KeyboardSequence("RU MZ1:CASTLE\n");
    Emulator_Run(225);  // Wait for title on blue background
    Test_CheckScreenshot(_T("data\\test04_4.bmp"));
    Emulator_KeyboardSequence(" ");
    Emulator_Run(50);
    Emulator_KeyboardSequence("1");  // Game rank
    Emulator_Run(75);
    Emulator_KeyboardPressRelease(0133);  // Right arrow
    Emulator_Run(5);
    Test_CheckScreenshot(_T("data\\test04_5.bmp"));

    Emulator_Reset();

    Emulator_Run(75);  // Boot: 3 seconds
    Emulator_KeyboardSequence("1\n");
    Emulator_Run(200);  // Boot: 8 seconds
    Emulator_KeyboardSequence("01-01-99\n\n\n");
    Emulator_Run(75);  // Boot: 3 seconds
    Emulator_KeyboardSequence("RU MZ1:SOUCOB\n");
    Emulator_Run(275);
    Test_CheckScreenshot(_T("data\\test04_6.bmp"));
    Emulator_KeyboardSequence(" ");
    Emulator_Run(50);
    Test_CheckScreenshot(_T("data\\test04_7.bmp"));

    Emulator_Reset();
}

int _tmain(int argc, _TCHAR* argv[])
{
    Test_LogInfo(_T("Initialization..."));
    BOOL init = Emulator_Init();
    if (!init)
    {
        Test_LogError(_T("Initialization failed."));
        return 1;
    }

    //Test1_MenuAndSelfTest();
    //Test2_RomBasic();
    Test3_FTMON();
    //Test4_Games();

    Test_LogInfo(_T("Finalization..."));
    Emulator_Done();

	return 0;
}
