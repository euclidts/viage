## Dependencies

* cmake >= 3.14
* cpp 20 compiler
* qt6 Multimedia
* libdrogon
* jsoncpp
**TODO : faire le ménage dans les dépendances de drogon
* sqlite3
* postgresql
* maria/mysql
* brotli
* libhiredis
* yalm
* kbd

## Changelog
* change paseword in settings, popup + close settings pane
* email, never necescary
* page 6 out
* Vertical allignement in calaulation document 
* reinit calculation evry time
* User management
* rent, change interest from 4% to 4.25%
* choose camera input
* better regexp handling files
* onboarding document: _ Espace entre contacts et partenaires
                       _ date de naissance avec heure pas necessaire
                       _ inversement de contact et parteniare
                       _ Exterieur : types de places
                       _ Equipement de proximite dans Exterieur
                       _ Bordure bien net des carres
* mail, les space between body and signature
* block download document button
* transmission du dossier au CA de Viager Swiss SA (en 2eme)
* last modification on top of the filter list
* corect text input color
* login popup when changing screen

## TODO

# Client side

* credits -> Mention Legal (smaller police)
* scroll inertia
* Habitat completed

* ASFDE52 FERDGR52

++ timeout for connection (3h)
++ position Title in error header

* line skipt in calculation document
* pull list of new teams when one is added

# Server side

* notify unique download in the onboarding mail
* last modification on top of the filter list
* order of items in exterior on the onboarding document
* enfants on the onboarding document 
* equiment de proximite stacked verticaly on the onborading document

* new password mail: change subject, remove the second "equipe viage"

++ Excel documents for advisors 
++ Filter invert order of filtered item in report
++ Repport: inclusive filter (equivalent to the "contain" option)
++ get email from all users

## Start the service
cd Euclid/Viage5
dotnet euclid.dll --urls "http://*:6000;https://*:6001"
