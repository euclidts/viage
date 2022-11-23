#include <QJsonDocument>
#include <wobjectimpl.h>

#include "c_exterior.hpp"
#include <client.hpp>

using namespace Client;

namespace Data
{
namespace Places
{
W_OBJECT_IMPL(c_exterior)

c_exterior::c_exterior(QObject *parent)
    : c_base_data{parent}
    , exterior_item{}
{
}

void c_exterior::read(const Json::Value& json)
{
    bool prev_hasParking{hasParking};
    int prev_parkingSpots{parkingSpots};
    parkingTypes prev_parkingType{parkingType};
    int prev_parkingSurface{parkingSurface};
    std::string prev_terrainDescription{terrainDescription};
    int prev_terrainSurface{terrainSurface};
    equipements prev_equipement{equipement};
    int prev_rating{rating};

    exterior_item::read(json);

    if (prev_hasParking != hasParking)
        emit hasParkingChanged();

    if (prev_parkingSpots != parkingSpots)
        emit parkingSpotsChanged();

    if (prev_parkingType != parkingType)
        emit parkingTypeChanged();

    if (prev_parkingSurface != parkingSurface)
        emit parkingSurfaceChanged();

    if (prev_terrainDescription != terrainDescription)
        emit terrainDescriptionChanged();

    if (prev_terrainSurface != terrainSurface)
        emit terrainSurfaceChanged();

    if (prev_equipement != equipement)
        emit equipementsChanged();

    if (prev_rating != rating)
        emit ratingChanged();

    emit loaded();
    checkCompleted();
}

void c_exterior::write(Json::Value& json) const
{
    exterior_item::write(json);
}

void c_exterior::clear()
{
    hasParking = false;
    emit hasParkingChanged();
    parkingSpots = 0;
    emit parkingSpotsChanged();
    parkingType = NoParking;
    emit parkingTypeChanged();
    parkingSurface = 0;
    emit parkingSurfaceChanged();
    terrainDescription = "";
    emit terrainDescriptionChanged();
    terrainSurface = 50;
    emit terrainSurfaceChanged();
    equipement = None;
    emit equipementsChanged();
    rating = 0;
    emit ratingChanged();
    completed = false;
    emit completedChanged();
}

int c_exterior::getParkingSpots() const
{
    return parkingSpots;
}

void c_exterior::setParkingSpots(int newParkingSpots)
{
    if (parkingSpots == newParkingSpots)
        return;
    parkingSpots = newParkingSpots;
    emit parkingSpotsChanged();
}

const c_exterior::parkingTypes &c_exterior::getParkingType() const
{
    return parkingType;
}

void c_exterior::setParkingType(const parkingTypes &newParkingType)
{
    if (parkingType == newParkingType)
        return;
    parkingType = newParkingType;
    emit parkingTypeChanged();
}

int c_exterior::getParkingSurface() const
{
    return parkingSurface;
}

void c_exterior::setParkingSurface(int newParkingSurface)
{
    if (parkingSurface == newParkingSurface)
        return;
    parkingSurface = newParkingSurface;
    emit parkingSurfaceChanged();
}

const QString c_exterior::getTerrainDescription() const
{
    return to_QString(terrainDescription);
}

void c_exterior::setTerrainDescription(const QString& newTerrainDescription)
{
    const std::string str{to_string(newTerrainDescription)};

    if (terrainDescription == str)
        return;
    terrainDescription = str;
    emit terrainDescriptionChanged();
}

int c_exterior::getTerrainSurface() const
{
    return terrainSurface;
}

void c_exterior::setTerrainSurface(int newTerrainSurface)
{
    if (terrainSurface == newTerrainSurface)
        return;
    terrainSurface = newTerrainSurface;
    emit terrainSurfaceChanged();
}

bool c_exterior::getHasParking() const
{
    return hasParking;
}

void c_exterior::setHasParking(bool newHasParking)
{
    if (hasParking == newHasParking)
        return;
    hasParking = newHasParking;
    emit hasParkingChanged();
}

const c_exterior::equipements& c_exterior::getEquipements() const
{
    return equipement;
}

void c_exterior::setEquipements(const equipements& newEquipement)
{
    if (equipement == newEquipement)
        return;
    equipement = newEquipement;
    emit equipementsChanged();
}

int c_exterior::getRating() const
{
    return rating;
}

void c_exterior::setRating(int newRating)
{
    if (rating == newRating)
        return;
    rating = newRating;
    emit ratingChanged();
    checkCompleted();
}

void c_exterior::checkCompleted()
{
    setCompleted(exterior_item::is_completed());
}

}
}
