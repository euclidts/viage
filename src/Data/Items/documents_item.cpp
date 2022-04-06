#include <QJsonDocument>
#include <QJsonArray>
#include <wobjectimpl.h>

#include "documents_item.hpp"
#include <Lists/url_list.hpp>

namespace Data
{
W_OBJECT_IMPL(documents_item)

documents_item::documents_item(QObject* parent)
    : Data::data_notifyer{parent}
    , id{new url_list(parent)}
    , registeryExcerpt{new url_list(parent)}
    , pursuitExcerpt{new url_list(parent)}
    , taxDeclaration{new url_list(parent)}
    , buildingDetails{new url_list(parent)}
    , picture{new url_list(parent)}
    , insurance{new url_list(parent)}
    , beb{new url_list(parent)}
    , jobs{new url_list(parent)}
    , futureJobs{new url_list(parent)}
{
}

void documents_item::read(const QJsonObject& json)
{
    if (json.contains("id") && json["id"].isArray())
        id->setFromArray(json["id"].toArray());
        emit idChanged();

    if (json.contains("registeryExcerpt") && json["registeryExcerpt"].isArray())
        registeryExcerpt->setFromArray(json["registeryExcerpt"].toArray());
        emit registeryExcerptChanged();

    if (json.contains("pursuitExcerpt") && json["pursuitExcerpt"].isArray())
        pursuitExcerpt->setFromArray(json["pursuitExcerpt"].toArray());
        emit pursuitExcerptChanged();

    if (json.contains("taxDeclaration") && json["taxDeclaration"].isArray())
        taxDeclaration->setFromArray(json["taxDeclaration"].toArray());
        emit taxDeclarationChanged();

    if (json.contains("buildingDetails") && json["buildingDetails"].isArray())
        buildingDetails->setFromArray(json["buildingDetails"].toArray());
        emit buildingDetailsChanged();

    if (json.contains("picture") && json["picture"].isArray())
        picture->setFromArray(json["picture"].toArray());
        emit pictureChanged();

    if (json.contains("insurance") && json["insurance"].isArray())
        insurance->setFromArray(json["insurance"].toArray());
        emit insuranceChanged();

    if (json.contains("beb") && json["beb"].isArray())
        beb->setFromArray(json["beb"].toArray());
        emit bebChanged();

    if (json.contains("jobs") && json["jobs"].isArray())
        jobs->setFromArray(json["jobs"].toArray());
        emit jobsChanged();

    if (json.contains("futureJobs") && json["futureJobs"].isArray())
        futureJobs->setFromArray(json["futureJobs"].toArray());
        emit futureJobsChanged();

    emit loaded();
}

void documents_item::read(const QByteArray &bytes)
{
    const auto json = QJsonDocument::fromJson(bytes).object();
    read(json);
}

void documents_item::write(QJsonObject& json) const
{
    json["id"] = id->arrayFromList();
    json["registeryExcerpt"] = registeryExcerpt->arrayFromList();
    json["pursuitExcerpt"] = pursuitExcerpt->arrayFromList();
    json["taxDeclaration"] = taxDeclaration->arrayFromList();
    json["buildingDetails"] = buildingDetails->arrayFromList();
    json["picture"] = picture->arrayFromList();
    json["insurance"] = insurance->arrayFromList();
    json["beb"] = beb->arrayFromList();
    json["jobs"] = jobs->arrayFromList();
}

url_list *documents_item::getId() const
{
    return id;
}

void documents_item::setId(url_list *newId)
{
    id->set_list(newId->get_list());
    emit idChanged();
}

url_list* documents_item::getRegisteryExcerpt() const
{
    return registeryExcerpt;
}

void documents_item::setRegisteryExcerpt(const url_list* newRegisteryExcerpt)
{
    registeryExcerpt->set_list(newRegisteryExcerpt->get_list());
    emit registeryExcerptChanged();
}

url_list* documents_item::getPursuitExcerpt() const
{
    return pursuitExcerpt;
}

void documents_item::setPursuitExcerpt(const url_list* newPursuitExcerpt)
{
    pursuitExcerpt->set_list(newPursuitExcerpt->get_list());
    emit pursuitExcerptChanged();
}

url_list* documents_item::getTaxDeclaration() const
{
    return taxDeclaration;
}

void documents_item::setTaxDeclaration(const url_list* newTaxDeclaration)
{
    taxDeclaration->set_list(newTaxDeclaration->get_list());
    emit taxDeclarationChanged();
}

url_list* documents_item::getBuildingDetails() const
{
    return buildingDetails;
}

void documents_item::setBuildingDetails(const url_list* newBuildingDetails)
{
    buildingDetails->set_list(newBuildingDetails->get_list());
    emit buildingDetailsChanged();
}

url_list* documents_item::getPicture() const
{
    return picture;
}

void documents_item::setPicture(const url_list* newPicture)
{
    picture->set_list(newPicture->get_list());
    emit pictureChanged();
}

url_list* documents_item::getInsurance() const
{
    return insurance;
}

void documents_item::setInsurance(const url_list* newInsurance)
{
    insurance->set_list(newInsurance->get_list());
    emit insuranceChanged();
}

url_list* documents_item::getBeb() const
{
    return beb;
}

void documents_item::setBeb(const url_list* newBeb)
{
    beb->set_list(newBeb->get_list());
    emit bebChanged();
}

url_list* documents_item::getJobs() const
{
    return jobs;
}

void documents_item::setJobs(const url_list* newJobs)
{
    jobs->set_list(newJobs->get_list());
    emit jobsChanged();
}

url_list* documents_item::getFutureJobs() const
{
    return futureJobs;
}

void documents_item::setFutureJobs(const url_list* newFutureJobs)
{
    futureJobs->set_list(newFutureJobs->get_list());
    emit futureJobsChanged();
}

}
