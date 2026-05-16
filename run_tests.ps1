# powershell -ExecutionPolicy Bypass -File .\run_tests.ps1

Write-Host "Running valid test..."
Copy-Item tests\valid_1.txt input.txt
.\compiler.exe

Write-Host "Running invalid test..."
Copy-Item tests\invalid_1.txt input.txt
.\compiler.exe