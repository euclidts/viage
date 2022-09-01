## Dependencies

* cmake >= 3.14
* cpp 20 compiler
* qt6 Multimedia

## Changelog
* change paseword in settings, popup + close settings pane
* email, never necescary

## TODO

# Client side

* rent, change interest from 4% to 4.25%
* Habitat completed
* User management

++ timeout for connection (3h)
++ position Title in error header

# Server side

* mail, les space between body and signature
* new password mail: change subject, remove the second "equipe viage"

++ Excel documents for advisors 
++ Filter invert order of filtered item in report
++ Repport: inclusive filter (equivalent to the "contain" option)

## Start the service
cd Euclid/Viage5
dotnet euclid.dll --urls "http://*:6000;https://*:6001"
