#ifndef CEREAL_H
#define CEREAL_H
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>

#include <fstream>

struct MyData
{
    int x;
    uint16_t y;
    float z;

    std::string description;

    //    template<class Archive>
    //    void serialize(Archive& ar)
    //    {
    //        ar(x, y, z, description);
    //    }
};

namespace cereal
{
    template<class Archive>
    void save(Archive& archive, MyData const& data)
    {
        archive(
            cereal::make_nvp<Archive>("x", data.x), cereal::make_nvp<Archive>("y", data.y),
            cereal::make_nvp<Archive>("z", data.z), cereal::make_nvp<Archive>("description", data.description));
    }

    template<class Archive>
    void load(Archive& archive, MyData& data)
    {
        int x;
        uint16_t y;
        float z;

        std::string description;
        archive(
            cereal::make_nvp<Archive>("x", x), cereal::make_nvp<Archive>("y", y), cereal::make_nvp<Archive>("z", z),
            cereal::make_nvp<Archive>("description", description));
        data = MyData{x, y, z, description};
    }
} // namespace cereal

void testCereal()
{
    {
        std::ofstream os("data.json");

        cereal::JSONOutputArchive archive(os);

        MyData m;

        m.description = "Saman";
        m.x = -1;
        m.y = 2;
        m.z = 1.5;

        archive(m);
    }
}
#endif // CEREAL_H
