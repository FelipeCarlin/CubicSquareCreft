@echo off

call ..\cubicsquarecreft\misc\shell.bat

pushd cubicsquarecreft\code
call build.bat
popd

cd scripts 