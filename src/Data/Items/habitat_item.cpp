#include <QJsonDocument>
#include <wobjectimpl.h>

#include "habitat_item.hpp"

namespace Data
{
namespace Places
{
W_OBJECT_IMPL(habitat_item)

habitat_item::habitat_item(QObject *parent)
    : base_item{parent}
    , address{}
{
}

void habitat_item::read(const QJsonObject& json)
{
    if (json.contains("address") && json["address"].isObject())
    {
        address.read(json["address"].toObject());
        emit streetChanged();
        emit cityChanged();
        emit zipChanged();
        emit cantonChanged();
    }

    if (json.contains("habitatType") && json["habitatType"].isDouble())
        setHabitatType(habitatTypes(json["habitatType"].toInt()));

    if (json.contains("rooms") && json["rooms"].isDouble())
        setRooms(json["rooms"].toInt());

    if (json.contains("rawSurface") && json["rawSurface"].isDouble())
        setRawSurface(json["rawSurface"].toInt());

    if (json.contains("surface") && json["surface"].isDouble())
        setSurface(json["surface"].toInt());

    if (json.contains("m2Constructed") && json["m2Constructed"].isDouble())
        setM2Constructed(json["m2Constructed"].toInt());

    if (json.contains("m2available") && json["m2available"].isDouble())
        setM2Available(json["m2available"].toInt());

    if (json.contains("m3s") && json["m3s"].isDouble())
        setM3s(json["m3s"].toInt());

    emit loaded();
    checkCompleted();
}

void habitat_item::read(const QByteArray &bytes)
{
    const auto json = QJsonDocument::fromJson(bytes).object();
    read(json);
}

void habitat_item::write(QJsonObject& json) const
{
    QJsonObject jsonAddress{};
    address.write(jsonAddress);

    json["address"] = jsonAddress;
    json["habitatType"] = habitatType;
    json["rooms"] = rooms;
    json["rawSurface"] = rawSurface;
    json["surface"] = surface;
    json["m2Constructed"] = m2Constructed;
    json["m2Available"] = m2Available;
    json["m3s"] = m3s;
}

void habitat_item::clear()
{
    address.street = QString{""};
    emit streetChanged();
    address.city = QString{""};
    emit cityChanged();
    address.zip = 9000;
    emit zipChanged();
    address.canton = QString{"Appenzell"};
    emit cantonChanged();
    habitatType = None;
    emit habitatTypeChanged();
    rooms = 2;
    emit roomsChanged();
    rawSurface = 50;
    emit rawSurfaceChanged();
    surface = 50;
    emit surfaceChanged();
    m2Constructed = 25;
    emit m2ConstructedChanged();
    m2Available = 25;
    emit m2AvailableChanged();
    m3s = 1000;
    emit m3sChanged();
    completed = false;
    emit completedChanged();
}

const QString &habitat_item::getStreet() const
{
    return address.street;
}

void habitat_item::setStreet(const QString &newStreet)
{
    if (address.street == newStreet)
        return;
    address.street = newStreet;
    emit streetChanged();
    checkCompleted();
}

int habitat_item::getZip() const
{
    return address.zip;
}

void habitat_item::setZip(int newZip)
{
    if (address.zip == newZip)
        return;
    address.zip = newZip;
    emit zipChanged();
}

const QString &habitat_item::getCanton() const
{
    return address.canton;
}

void habitat_item::setCanton(const QString &newCanton)
{
    if (address.canton == newCanton)
        return;
    address.canton = newCanton;
    emit cantonChanged();
}

const QString &habitat_item::getCity() const
{
    return address.city;
}

void habitat_item::setCity(const QString &newCity)
{
    if (address.city == newCity)
        return;
    address.city = newCity;
    emit cityChanged();
}

const habitat_item::habitatTypes& habitat_item::getHabitatType() const
{
    return habitatType;
}

void habitat_item::setHabitatType(const habitatTypes& newHabitatType)
{
    if (habitatType == newHabitatType)
        return;
    habitatType = newHabitatType;
    emit habitatTypeChanged();
    checkCompleted();
}

int habitat_item::getRooms() const
{
    return rooms;
}

void habitat_item::setRooms(int newRooms)
{
    if (rooms == newRooms)
        return;
    rooms = newRooms;
    emit roomsChanged();
}

int habitat_item::getRawSurface() const
{
    return rawSurface;
}

void habitat_item::setRawSurface(int newRawSurface)
{
    if (rawSurface == newRawSurface)
        return;
    rawSurface = newRawSurface;
    emit rawSurfaceChanged();
}

int habitat_item::getSurface() const
{
    return surface;
}

void habitat_item::setSurface(int newSurface)
{
    if (surface == newSurface)
        return;
    surface = newSurface;
    emit surfaceChanged();
}

int habitat_item::getM2Constructed() const
{
    return m2Constructed;
}

void habitat_item::setM2Constructed(int newM2Constructed)
{
    if (m2Constructed == newM2Constructed)
        return;
    m2Constructed = newM2Constructed;
    emit m2ConstructedChanged();
}

int habitat_item::getM2Available() const
{
    return m2Available;
}

void habitat_item::setM2Available(int newM2Available)
{
    if (m2Available == newM2Available)
        return;
    m2Available = newM2Available;
    emit m2AvailableChanged();
}

int habitat_item::getM3s() const
{
    return m3s;
}

void habitat_item::setM3s(int newM3s)
{
    if (m3s == newM3s)
        return;
    m3s = newM3s;
    emit m3sChanged();
}

void habitat_item::checkCompleted()
{
    if (!address.is_completed())
    {
        setCompleted(false);
        return;
    }

    if (habitatType == None)
    {
        setCompleted(false);
        return;
    }

    setCompleted(true);
}

}
}
