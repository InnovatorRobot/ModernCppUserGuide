#ifndef TEMPLATES_H
#define TEMPLATES_H
#include <iostream>
#include <string>

///////////////////////////////// Function Template /////////////////////////////////
template<typename T>
T maximum(T a, T b)
{
    return (a > b) ? a : b;
}

// template<typename T>
// T const& maximum(T const& a, T const& b)
//{
//    return a > b ? a : b;
//}

// template<>
// const char* maximum<const char*>(const char* a, const char* b)
//{
//    return (std::strcmp(a, b) > 0) ? a : b;
//}

auto func_add(auto a, auto b)
{

    auto function_add_lambda = [](auto a, auto b) { return a + b; };
    return a + b; // this will be generate as function template by compiler! as below:
    /*
     template <typename T, typename P>
     decltype(auto) func_add(T a, P b)
    {
        return a + b;
    }
     */
}
void testExplicitTemplateFunction()
{
    auto max = maximum<double>(3, 3.5); // explicit function template!
}

///////////////////////////////// Concept /////////////////////////////////

template<typename T>
requires std::integral<T> T add(T a, T b)
{
    return a + b;
}

template<std::integral T> // same as above
T sub(T a, T b)
{
    return a - b;
}

auto multi(std::integral auto a, std::integral auto b) // same as above
{
    return a * b;
}

///// There are alot of other concepts that you can use for programming stuff like:
/// same_as
/// drived_from
/// signed_integral
/// unsigned_integral
/// floating_point
/// assignable_from
/// ...
void testConcept()
{
    add(5, 2);
    // add(5.2, 2); Comppile Error!
}

///////////////////////////////// Class Template /////////////////////////////////
AsyncTask egoPathLogger(FrameGraph const& frameGraph, api::SubjectSubscriber<sal::PointCloudSample> const& lidarSubscriber)
{

    auto frameGraphChannel = foxglove::Channel<geometry::FrameTransform<double>>{"/env/frame-graph"};
    auto lidarChannels = std::unordered_map<std::string, foxglove::Channel<sal::PointCloudSample>>{};
    lidarChannels.try_emplace("lidar_front_frame", "/env/sensor/lidar-front");
    lidarChannels.try_emplace("lidar_rear_frame", "/env/sensor/lidar-rear");

    return (AsyncTask{
        "Logging100ms", [=, &lidarSubscriber, &frameGraph](auto const& app) mutable
        {
            auto now = app.clock().now();
            geometry::WriteFrameGraphToChannel(frameGraphChannel, frameGraph, now);

            while (auto pcs = lidarSubscriber.tryReceive())
            {
                try
                {
                    lidarChannels.at(pcs->frameName()).write(*pcs);
                }
                catch (std::out_of_range const& e)
                {
                    ENV_LOG_WARNING("Unknown frame in lidar data: '{}'", pcs->frameName());
                }
            }

            using namespace std::chrono;
            std::this_thread::sleep_for(100ms);
        }});
}

#endif // TEMPLATES_H
