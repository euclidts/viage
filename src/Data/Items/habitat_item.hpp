#ifndef HABITAT_ITEM_HPP
#define HABITAT_ITEM_HPP

#include <QJsonDocument>
#include <QJsonObject>

#include <wobjectdefs.h>

#include "base_item.hpp"
#include "address_item.hpp"

namespace Data
{
namespace Places
{
class habitat_item : public base_item
{
    W_OBJECT(habitat_item)

public:
    explicit habitat_item(QObject* parent = nullptr);

    const constexpr char* key() override { return "habitat"; };
    static const constexpr auto qmlName{"HabitatItem"};
    static const constexpr auto uri{"Places"};

    void read(const QJsonObject& json);
    void read(const QByteArray& bytes);
    void write(QJsonObject &json) const override;
    void clear() override;
    W_SLOT(clear)

    enum habitatTypes
    {
        None = 0,
        DetachedHouse,
        AdjacentHouse,
        Appartement
    };

    const QString &getStreet() const;
    void setStreet(const QString &newStreet);
    int getZip() const;
    void setZip(int newZip);
    const QString &getCanton() const;
    void setCanton(const QString &newCanton);
    const QString &getCity() const;
    void setCity(const QString& newCity);
    const QString &getEquipements() const;
    void setEquipements(const QString &newEquipements);
    const QString &getProblems() const;
    void setProblems(const QString &newProblems);
    const habitatTypes& getType() const;
    void setType(habitatTypes newType);
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
    void equipementsChanged()
    W_SIGNAL(equipementsChanged)
    void problemsChanged()
    W_SIGNAL(problemsChanged)
    void typeChanged()
    W_SIGNAL(typeChanged)
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
    W_PROPERTY(QString, equipements READ getEquipements WRITE setEquipements NOTIFY equipementsChanged)
    W_PROPERTY(QString, problems READ getProblems WRITE setProblems NOTIFY problemsChanged)
    W_PROPERTY(habitatTypes, type READ getType WRITE setType NOTIFY typeChanged)
    W_PROPERTY(int, rooms READ getRooms WRITE setRooms NOTIFY roomsChanged)
    W_PROPERTY(int, rawSurface READ getRawSurface WRITE setRawSurface NOTIFY rawSurfaceChanged)
    W_PROPERTY(int, surface READ getSurface WRITE setSurface NOTIFY surfaceChanged)
    W_PROPERTY(int, m2Constructed READ getM2Constructed WRITE setM2Constructed NOTIFY m2ConstructedChanged)
    W_PROPERTY(int, m2Available READ getM2Available WRITE setM2Available NOTIFY m2AvailableChanged)
    W_PROPERTY(int, m3s READ getM3s WRITE setM3s NOTIFY m3sChanged)

private:
    // --- Habitat ---
    Places::address_item address;
    // Global
    QString equipements;
    QString problems;
    // Habitat data
    habitatTypes type;
    int rooms;
    int rawSurface;
    int surface;
    int m2Constructed;
    int m2Available;
    int m3s;
};

}
}

#endif // HABITAT_ITEM_HPP
