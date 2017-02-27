TASKKILL /F /IM Car* /IM SystemServer*
start /d"C:\CarUnitySystem\backstage\dist\SystemServer" /min "" "SystemServer.exe"
ping 127.0.0.1 -n 3 >nul 
start /d"C:\CarUnitySystem\onstage" "" "autorun.bat"