#ifndef DOCUMENTS_ITEM_HPP
#define DOCUMENTS_ITEM_HPP

#include <QJsonObject>

#include <wobjectdefs.h>

#include "base_item.hpp"

namespace Data
{
struct url_list;

class documents_item : public base_item
{
    W_OBJECT(documents_item)

public:
    explicit documents_item(QObject* parent = nullptr);

    const constexpr char* key() override { return "documents"; };
    static const constexpr auto qmlName{"DocumentsItem"};
    static const constexpr auto uri{"Data"};

    void read(const QJsonObject& json);
    void read(const QByteArray& bytes);
    void write(QJsonObject &json) const override;

    url_list *getId() const;
    void setId(url_list *newId);
    url_list* getRegisteryExcerpt() const;
    void setRegisteryExcerpt(const url_list* newRegisteryExcerpt);
    url_list* getPursuitExcerpt() const;
    void setPursuitExcerpt(const url_list* newPursuitExcerpt);
    url_list* getTaxDeclaration() const;
    void setTaxDeclaration(const url_list* newTaxDeclaration);
    url_list* getBuildingDetails() const;
    void setBuildingDetails(const url_list* newBuildingDetails);
    url_list* getPicture() const;
    void setPicture(const url_list* newPicture);
    url_list* getInsurance() const;
    void setInsurance(const url_list* newInsurance);
    url_list* getBeb() const;
    void setBeb(const url_list* newBeb);
    url_list* getJobs() const;
    void setJobs(const url_list* newJobs);
    url_list* getFutureJobs() const;
    void setFutureJobs(const url_list* newFutureJobs);

    void idChanged()
    W_SIGNAL(idChanged)
    void registeryExcerptChanged()
    W_SIGNAL(registeryExcerptChanged)
    void pursuitExcerptChanged()
    W_SIGNAL(pursuitExcerptChanged)
    void taxDeclarationChanged()
    W_SIGNAL(taxDeclarationChanged)
    void buildingDetailsChanged()
    W_SIGNAL(buildingDetailsChanged)
    void pictureChanged()
    W_SIGNAL(pictureChanged)
    void insuranceChanged()
    W_SIGNAL(insuranceChanged)
    void bebChanged()
    W_SIGNAL(bebChanged)
    void jobsChanged()
    W_SIGNAL(jobsChanged)
    void futureJobsChanged()
    W_SIGNAL(futureJobsChanged)

    void validate(int parentIndex)
    W_SIGNAL(validate, parentIndex)

    W_PROPERTY(url_list*, id READ getId WRITE setId NOTIFY idChanged)
    W_PROPERTY(url_list*, registeryExcerpt READ getRegisteryExcerpt WRITE setRegisteryExcerpt NOTIFY registeryExcerptChanged)
    W_PROPERTY(url_list*, pursuitExcerpt READ getPursuitExcerpt WRITE setPursuitExcerpt NOTIFY pursuitExcerptChanged)
    W_PROPERTY(url_list*, taxDeclaration READ getTaxDeclaration WRITE setTaxDeclaration NOTIFY taxDeclarationChanged)
    W_PROPERTY(url_list*, buildingDetails READ getBuildingDetails WRITE setBuildingDetails NOTIFY buildingDetailsChanged)
    W_PROPERTY(url_list*, picture READ getPicture WRITE setPicture NOTIFY pictureChanged)
    W_PROPERTY(url_list*, insurance READ getInsurance WRITE setInsurance NOTIFY insuranceChanged)
    W_PROPERTY(url_list*, beb READ getBeb WRITE setBeb NOTIFY bebChanged)
    W_PROPERTY(url_list*, jobs READ getJobs WRITE setJobs NOTIFY jobsChanged)
    W_PROPERTY(url_list*, futureJobs READ getFutureJobs WRITE setFutureJobs NOTIFY futureJobsChanged)

private:
    url_list* id;
    url_list* registeryExcerpt;
    url_list* pursuitExcerpt;
    url_list* taxDeclaration;
    url_list* buildingDetails;
    url_list* picture;
    url_list* insurance;
    url_list* beb;
    url_list* jobs;
    url_list* futureJobs;
};

}

#endif // DOCUMENTS_ITEM_HPP
