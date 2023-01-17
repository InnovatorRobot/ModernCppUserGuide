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
    std::vector<int> matrix;
    std::unordered_map<int, std::string> map;

    template<class Archive>
    void serialize(Archive& ar)
    {
        ar(x, y, z, description, matrix, map);
    }

    template<class Archive>
    void load(Archive& ar) const
    {
        ar(x, y, z, description, matrix, map);
    }

    template<class Archive>
    void save(Archive& ar)
    {
        ar(x, y, z, description, matrix, map);
    }
};

// namespace cereal
//{
//     template<class Archive>
//     void save(Archive& archive, MyData& data)
//     {
//     }

//    template<class Archive>
//    void load(Archive& archive, MyData& data)
//    {
//    }
//} // namespace cereal

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
        m.matrix = {7, 8, 9};
        m.map = {{1, "a"}, {2, "b"}, {3, "c"}};

        archive(CEREAL_NVP(m));
    }
}
#endif // CEREAL_H
