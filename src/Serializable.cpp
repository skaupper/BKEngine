#include "Serializable.h"

using namespace bkengine;


std::map<std::string, std::shared_ptr<Serializable>(*)()> Serializer::factories;


Serializable::Serializable(const Json::Value &json)
{
    Json::Value v(json);
    swap(v);
}

std::string Serializable::serialize() const
{
    Json::StyledWriter writer;
    std::string output = writer.write(*this);
    return output;
}

std::shared_ptr<Serializable> Serializable::deserialize(
    const std::string &serializedString)
{
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(serializedString, root);

    if (!parsingSuccessful) {
        return nullptr;
    }

    return std::make_shared<Serializable>(root);
}
