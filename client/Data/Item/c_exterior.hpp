#ifndef C_EXTERIOR_HPP
#define C_EXTERIOR_HPP

#include <wobjectdefs.h>
#include <c_base_data.hpp>
#include <Item/exterior_item.hpp>

namespace Data
{
namespace Places
{
class c_exterior : public exterior_item
                 , public c_base_data
{
    W_OBJECT(c_exterior)

public:
    explicit c_exterior(QObject* parent = nullptr);

    static const constexpr auto uri{"Places"};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    void clear() override;
    W_SLOT(clear)

    bool getHasParking() const;
    void setHasParking(bool newHasParking);
    int getParkingSpots() const;
    void setParkingSpots(int newParkingSpots);
    const parkingTypes &getParkingType() const;
    void setParkingType(const parkingTypes &newParkingType);
    int getParkingSurface() const;
    void setParkingSurface(int newParkingSurface);
    const QString getTerrainDescription() const;
    void setTerrainDescription(const QString &newTerrainDescription);
    int getTerrainSurface() const;
    void setTerrainSurface(int newTerrainSurface);
    const equipements &getEquipements() const;
    void setEquipements(const equipements &newEquipements);
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
    void equipementsChanged()
    W_SIGNAL(equipementsChanged)
    void ratingChanged()
    W_SIGNAL(ratingChanged)

    W_PROPERTY(bool, hasParking READ getHasParking WRITE setHasParking NOTIFY hasParkingChanged)
    W_PROPERTY(int, parkingSpots READ getParkingSpots WRITE setParkingSpots NOTIFY parkingSpotsChanged)
    W_PROPERTY(parkingTypes, parkingType READ getParkingType WRITE setParkingType NOTIFY parkingTypeChanged)
    W_PROPERTY(int, parkingSurface READ getParkingSurface WRITE setParkingSurface NOTIFY parkingSurfaceChanged)
    W_PROPERTY(QString, terrainDescription READ getTerrainDescription WRITE setTerrainDescription NOTIFY terrainDescriptionChanged)
    W_PROPERTY(int, terrainSurface READ getTerrainSurface WRITE setTerrainSurface NOTIFY terrainSurfaceChanged)
    W_PROPERTY(equipements, equipement READ getEquipements WRITE setEquipements NOTIFY equipementsChanged)
    W_PROPERTY(int, rating READ getRating WRITE setRating NOTIFY ratingChanged)

private:
    void checkCompleted() override;
};

}
}

#endif // EXTERIOR_ITEM_HPP
