#ifndef C_HABITAT_HPP
#define C_HABITAT_HPP

#include <wobjectdefs.h>
#include <c_base_data.hpp>
#include <Item/habitat_item.hpp>

namespace Data
{
namespace Places
{
class c_habitat : public habitat_item
                , public c_base_data
{
    W_OBJECT(c_habitat)

public:
    explicit c_habitat(QObject* parent = nullptr);

    static const constexpr auto uri{"Places"};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    void clear() override;
    W_SLOT(clear)

    const QString getStreet() const;
    void setStreet(const QString &newStreet);
    int getZip() const;
    void setZip(int newZip);
    const QString getCanton() const;
    void setCanton(const QString &newCanton);
    const QString getCity() const;
    void setCity(const QString& newCity);
    const habitatTypes& getHabitatType() const;
    void setHabitatType(const habitatTypes& newHabitatType);
    int getRooms() const;
    void setRooms(int newRooms);
    int getRawSurface() const;
    void setRawSurface(int newRawSurface);
    int getSurface() const;
    void setSurface(int newSurface);
    int getM2Constructed() const;
    void setM2Constructed(int newM2Constructed);
    int getM2Available() const;
    void setM2Available(int newM2available);
    int getM3s() const;
    void setM3s(int newM3s);

    void streetChanged()
    W_SIGNAL(streetChanged)
    void zipChanged()
    W_SIGNAL(zipChanged)
    void cantonChanged()
    W_SIGNAL(cantonChanged)
    void cityChanged()
    W_SIGNAL(cityChanged)
    void habitatTypeChanged()
    W_SIGNAL(habitatTypeChanged)
    void roomsChanged()
    W_SIGNAL(roomsChanged)
    void rawSurfaceChanged()
    W_SIGNAL(rawSurfaceChanged)
    void surfaceChanged()
    W_SIGNAL(surfaceChanged)
    void m2ConstructedChanged()
    W_SIGNAL(m2ConstructedChanged)
    void m2AvailableChanged()
    W_SIGNAL(m2AvailableChanged)
    void m3sChanged()
    W_SIGNAL(m3sChanged)

    W_PROPERTY(QString, street READ getStreet WRITE setStreet NOTIFY streetChanged)
    W_PROPERTY(int, zip READ getZip WRITE setZip NOTIFY zipChanged)
    W_PROPERTY(QString, canton READ getCanton WRITE setCanton NOTIFY cantonChanged)
    W_PROPERTY(QString, city READ getCity WRITE setCity NOTIFY cityChanged)
    W_PROPERTY(habitatTypes, habitatType READ getHabitatType WRITE setHabitatType NOTIFY habitatTypeChanged)
    W_PROPERTY(int, rooms READ getRooms WRITE setRooms NOTIFY roomsChanged)
    W_PROPERTY(int, rawSurface READ getRawSurface WRITE setRawSurface NOTIFY rawSurfaceChanged)
    W_PROPERTY(int, surface READ getSurface WRITE setSurface NOTIFY surfaceChanged)
    W_PROPERTY(int, m2Constructed READ getM2Constructed WRITE setM2Constructed NOTIFY m2ConstructedChanged)
    W_PROPERTY(int, m2Available READ getM2Available WRITE setM2Available NOTIFY m2AvailableChanged)
    W_PROPERTY(int, m3s READ getM3s WRITE setM3s NOTIFY m3sChanged)

private:
    void checkCompleted() override;
};

}
}

#endif // HABITAT_ITEM_HPP
