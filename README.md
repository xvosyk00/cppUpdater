# Disclaimer
!! Do not use, project is not complete (see Todos). 

# Updater
C++ library for automatic self update of your app. 

- can check and update app
- updates all files in folder and subfolders
- server-client architecture (project contains both client API and server)
- client api can be statically linked to your app
- currently supports linux only

## Use cases
- client connects to server and compares versions
- client connects to server and updates to the newest version available

## How update works
- server transfers only new and changed files since clients version
- server stores database of changed files between versions of app
- if client is multiple versions behind, server can merge changes from all updates to not download same files twice


## Todos:
- missing function to insert new version into server db
- better client api (maybe function based for C and ABI compatibility)
- better error handling
- progress report
- possible future improvement: differential file update (transfer only changed parts of files)
