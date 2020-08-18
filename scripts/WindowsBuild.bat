@echo off

call ..\astroids\misc\shell.bat

pushd astroids\code
call build.bat
popd

cd scripts 