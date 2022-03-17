#pragma once


struct PhysicsComponent_t;


struct Point2D_t{
    double x { 0.0 }, y { 0.0 };
};

namespace STBEH{

    struct Steer_t {
        double linear       { 0.0 };
        double angular      { 0.0 };
        constexpr bool operator==(Steer_t const&) const noexcept = default;
    };

    Steer_t arrive(PhysicsComponent_t *, Point2D_t * target, double & time2arrive, double & arrivalRadius);
    Steer_t seek(PhysicsComponent_t *, Point2D_t * target, double & time2arrive, double & arrivalRadius);
    Steer_t seek_one(PhysicsComponent_t *, Point2D_t * target, double & time2arrive, double arrivalRadius);
}