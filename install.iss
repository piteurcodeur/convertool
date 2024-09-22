#define MyAppName "Convertool"
   #define MyAppVersion "1.0"
   #define MyAppExeName "Convertool.exe"

   [Setup]
   AppName={#MyAppName}
   AppVersion={#MyAppVersion}
   DefaultDirName={autopf}\{#MyAppName}
   DefaultGroupName={#MyAppName}
   OutputDir=Output
   OutputBaseFilename=ConvertoolSetup

   [Files]
   ; Exécutable principal
   Source: ".\bin\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion

   ; Fichiers principaux de l'application
   Source: ".\src\*"; DestDir: "{app}"; Flags: recursesubdirs

   ; Dossier include
   Source: ".\include\*"; DestDir: "{app}\include"; Flags: recursesubdirs

   ; Dossier lib
   Source: ".\lib\*"; DestDir: "{app}\lib"; Flags: recursesubdirs

   ; Dossier share
   Source: ".\share\*"; DestDir: "{app}\share"; Flags: recursesubdirs

   ; Dossier res
   Source: ".\res\*"; DestDir: "{app}\res"; Flags: recursesubdirs

   Source: ".\bin\*.dll"; DestDir: "{app}"; Flags: ignoreversion

   [Icons]
   Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
   Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
   Name: "{userdesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"

   