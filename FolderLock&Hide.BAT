echo off
cls
title _tzman Folder Locker/Unlocker utility

set password=12345


:menu

echo enter l to lock, u to unlock and e to exit:
set/p "choice=>"
if %choice%==u goto unlocker
if %choice%==U goto unlocker
if %choice%==e goto end
if %choice%==E goto end
if %choice%==l goto locker
if %choice%==L goto locker
echo wrong choice!!
goto menu


:LOCKER

echo enter the name of folder you want to lock:
set /p "name=>"
if not exist %name% (echo folder %name% not found
goto menu)
goto options


:return

rename "%name%" "%option%.%CLSID%"
attrib +h +s "%option%.%CLSID%"
echo folder succesfully locked as %option%.
goto menu


:UNLOCKER

echo SEARCHING FOR ANY LOCKED FILE...

if EXIST "control_panel.{5399E694-6CE5-4D6C-8FCE-1D8870FDCBA0}" (set name=control_panel
set caller=cp
set CLSID={5399E694-6CE5-4D6C-8FCE-1D8870FDCBA0}
goto confirm)
:ACP

if EXIST "Recycle_Bin.{645FF040-5081-101B-9F08-00AA002F954E}" (set name=Recycle_Bin
set caller=RB
set CLSID={645FF040-5081-101B-9F08-00AA002F954E}
goto confirm)
:ARB

if EXIST "Run.{2559A1F3-21D7-11D4-BDAF-00C04F60B9F0}" (set name=Run
set caller=R
set CLSID={2559A1F3-21D7-11D4-BDAF-00C04F60B9F0}
goto confirm)
:AR

if EXIST "Search.{2559A1F0-21D7-11D4-BDAF-00C04F60B9F0}" (set name=Search
set caller=S
set CLSID={2559A1F0-21D7-11D4-BDAF-00C04F60B9F0}
goto confirm)
:AS

if EXIST "flip_3d.{3080F90E-D7AD-11D9-BD98-0000947B0257}" (set name=flip_3d
set caller=F3D
set CLSID={3080F90E-D7AD-11D9-BD98-0000947B0257}
goto confirm)
:AF3D

if EXIST "Internet_Explorer.{871C5380-42A0-1069-A2EA-08002B30309D}" (set name=Internet_Explorer
set caller=IE
set CLSID={871C5380-42A0-1069-A2EA-08002B30309D}
goto confirm)
:AIE

if EXIST "Administrative_Tools.{D20EA4E1-3957-11D2-A40B-0C5020524153}" (set name=Administrative_Tools
set caller=AT
set CLSID={D20EA4E1-3957-11D2-A40B-0C5020524153}
goto confirm)
:AAT

if EXIST "network_connections.{7007ACC7-3202-11D1-AAD2-00805FC1270E}" (set name=network_connections
set caller=NC
set CLSID={7007ACC7-3202-11D1-AAD2-00805FC1270E}
goto confirm)
:ANC

if EXIST "Printers.{2227A280-3AEA-1069-A2DE-08002B30309D}" (set name=Printers
set caller=P
set CLSID={2227A280-3AEA-1069-A2DE-08002B30309D}
goto confirm)
:AP

echo no more locked folders found.
goto menu


:confirm

echo do you want to unlock %name%?(y/n):
set/p "cho=>"
if %cho%==Y goto pswd
if %cho%==y goto pswd
if %cho%==n goto a%caller%
if %cho%==N goto a%caller%
echo Invalid choice.
goto CONFIRM


:pswd

echo enter password:
set/p "pass=>"
if not %pass%==%password% ( echo incorrect password!!
goto pswd )
echo what will be the name of your unlocked folder
set/p "newname=>"
attrib -h -s "%name%.%CLSID%"
rename "%name%.%CLSID%" "%newname%" 
echo %name% succesfully unlocked as %newname%. 
goto menu


:options

echo what do you want your transformed folder to be...
echo 1.control_panel
echo 2.Recycle_Bin
echo 3.Run
echo 4.Search
echo 5.flip_3d 
echo 6.Internet_Explorer
echo 7.Administrative_Tools
echo 8.network_connections
echo 9.Printers
echo 10.main menu

echo enter your choice(1-9):
set/p "choice=>"

if %choice%==1 (set option=control_panel
set CLSID={5399E694-6CE5-4D6C-8FCE-1D8870FDCBA0}
goto return)
if %choice%==2 (set option=Recycle_Bin
set CLSID={645FF040-5081-101B-9F08-00AA002F954E}
goto return)
if %choice%==3 (set option=Run
set CLSID={2559A1F3-21D7-11D4-BDAF-00C04F60B9F0}
goto return)
if %choice%==4 (set option=Search
set CLSID={2559A1F0-21D7-11D4-BDAF-00C04F60B9F0}
goto return)
if %choice%==5 (set option=flip_3d
set CLSID={3080F90E-D7AD-11D9-BD98-0000947B0257}
goto return)
if %choice%==6 (set option=Internet_Explorer
set CLSID={871C5380-42A0-1069-A2EA-08002B30309D}
goto return)
if %choice%==7 (set option=Administrative_Tools
set CLSID={D20EA4E1-3957-11D2-A40B-0C5020524153}
goto return)
if %choice%==8 (set option=network_connections
set CLSID={7007ACC7-3202-11D1-AAD2-00805FC1270E}
goto return)
if %choice%==9 (set option=Printers
set CLSID={2227A280-3AEA-1069-A2DE-08002B30309D}
goto return)
if %choice%==10 goto menu
echo invalid choice!!
goto options


:END

echo ----------------------------
echo --  tzmanish97@gmail.com  --
echo ----------------------------
PAUSE