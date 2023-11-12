#include "mapHelper.h"

mapHelper::mapHelper()
{
    corePath = "Enclib";
    EnclSENCInit(corePath.toUtf8());

}

mapHelper::~mapHelper()
{
}
