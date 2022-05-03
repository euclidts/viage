#ifndef EXTERIOR_ITEM_HPP
#define EXTERIOR_ITEM_HPP

#include <QJsonArray>
#include <QJsonObject>

#include <wobjectdefs.h>

#include "base_item.hpp"

namespace Data
{
namespace Places
{
class exterior_item : public base_item
{
W_OBJECT(exterior_item)

public:
    explicit exterior_item(QObject* parent = nullptr);

    const constexpr char* key() override { return "exterior"; };
    static const constexpr auto qmlName{"ExteriorItem"};
    static const constexpr auto uri{"Places"};

    void read(const QJsonObject& json);
    void read(const QByteArray& bytes);
    void write(QJsonObject& json) const override;
    void clear() override;
    W_SLOT(clear)

    bool getHasParking() const;
    void setHasParking(bool newHasParking);
    int getParkingSpots() const;
    void setParkingSpots(int newParkingSpots);
    const QString &getParkingType() const;
    void setParkingType(const QString &newParkingType);
    int getParkingSurface() const;
    void setParkingSurface(int newParkingSurface);
    const QString &getTerrainDescription() const;
    void setTerrainDescription(const QString &newTerrainDescription);
    int getTerrainSurface() const;
    void setTerrainSurface(int newTerrainSurface);
    int getRating() const;
    void setRating(int newRating);

    void hasParkingChanged()
    W_SIGNAL(hasParkingChanged)
    void parkingSpotsChanged()
    W_SIGNAL(parkingSpotsChanged)
    void parkingTypeChanged()
    W_SIGNAL(parkingTypeChanged)
    void parkingSurfaceChanged()
    W_SIGNAL(parkingSurfaceChanged)
    void terrainDescriptionChanged()
    W_SIGNAL(terrainDescriptionChanged)
    void terrainSurfaceChanged()
    W_SIGNAL(terrainSurfaceChanged)
    void ratingChanged()
    W_SIGNAL(ratingChanged)

    W_PROPERTY(bool, hasParking READ getHasParking WRITE setHasParking NOTIFY hasParkingChanged)
    W_PROPERTY(int, parkingSpots READ getParkingSpots WRITE setParkingSpots NOTIFY parkingSpotsChanged)
    W_PROPERTY(QString, parkingType READ getParkingType WRITE setParkingType NOTIFY parkingTypeChanged)
    W_PROPERTY(int, parkingSurface READ getParkingSurface WRITE setParkingSurface NOTIFY parkingSurfaceChanged)
    W_PROPERTY(QString, terrainDescription READ getTerrainDescription WRITE setTerrainDescription NOTIFY terrainDescriptionChanged)
    W_PROPERTY(int, terrainSurface READ getTerrainSurface WRITE setTerrainSurface NOTIFY terrainSurfaceChanged)
    W_PROPERTY(int, rating READ getRating WRITE setRating NOTIFY ratingChanged)

private:
    // --- Exterior ---
    // Parking
    bool hasParking;
    int parkingSpots;
    QString parkingType;
    int parkingSurface;
    // Terrain
    QString terrainDescription;
    int terrainSurface;
    int rating;
};

}
}

#endif // EXTERIOR_ITEM_HPP
