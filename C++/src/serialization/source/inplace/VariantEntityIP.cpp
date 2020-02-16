//
// Created by saeed on 11/29/19.
//

#include "VariantEntityIP.h"

VariantEntityIP::VariantEntityIP() {}

VariantEntityIP::~VariantEntityIP() {}

VariantEntityIP::VariantEntityIP(VariantEntity *variantEntity) {

    this->serialize(variantEntity);

}

void VariantEntityIP::serialize(VariantEntity *variantEntity) {
    this->bitrate=variantEntity->bitrate;

    this->contentType = malloc <char> (strlen (variantEntity->contentType.c_str ()) + 1);
    strcpy (this->contentType, variantEntity->contentType.c_str ());

    this->url = malloc <char> (strlen (variantEntity->url.c_str ()) + 1);
    strcpy (this->url, variantEntity->url.c_str ());

}
