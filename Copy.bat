@echo off 
xcopy D:\Project\GM\WIn\EngineBase\*.h C:\a\EngineBase\ /e /h /k /y
xcopy D:\Project\GM\WIn\EngineCore\*.h C:\a\EngineCore\ /e /h /k /y
xcopy D:\Project\GM\WIn\EnginePlatform\*.h C:\a\EnginePlatform\ /e /h /k /y

@echo off 
xcopy D:\Project\GM\WIn\EngineBase\*.cpp C:\a\EngineBase\ /e /h /k /y
xcopy D:\Project\GM\WIn\EngineCore\*.cpp C:\a\EngineCore\ /e /h /k /y
xcopy D:\Project\GM\WIn\EnginePlatform\*.cpp C:\a\EnginePlatform\ /e /h /k /y
