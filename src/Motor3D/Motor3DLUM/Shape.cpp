#include "Shape.hpp"

Shape::Shape() : radius_{1.f}, center_ {1.f,1.f,1.f} {}
Shape::Shape( float radius, glm::vec3 center ) : radius_ {radius}, center_ {center.x,center.y,center.z} {}

bool Shape::isOnFrustum(CameraLUM * cam, glm::mat4 & mat) const
{
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(mat, scale, rotation, translation, skew, perspective);
    const glm::vec3 center {mat* glm::vec4(center_, 1.f)};
    Shape globalShape{1.f, center};
    globalShape.top_ =   scale.y;
    globalShape.bot_ =   scale.y;
    globalShape.left_ =  scale.x;
    globalShape.right_ = scale.x;
    globalShape.near_ =  scale.z;
    globalShape.far_ =   scale.z;


    if (!
        (
            globalShape.inTopPlan(cam->frustum_[0], globalShape) &&
            globalShape.inBotPlan(cam->frustum_[1], globalShape) &&
            globalShape.inRhtPlan(cam->frustum_[2], globalShape) &&
            globalShape.inLftPlan(cam->frustum_[3], globalShape) &&
            globalShape.inNerPlan(cam->frustum_[2], globalShape) &&
            globalShape.inFarPlan(cam->frustum_[3], globalShape)
        )
    )  
        return false;
    return true;
}
bool Shape::inTopPlan(const glm::vec4& plan, Shape& s) const
{
    float d {glm::dot(glm::vec3(plan.x,plan.y,plan.z),s.center_)};
    if ((d-s.top_)<plan.w)
    {
        return true;
    }
    return false;
}
bool Shape::inBotPlan(const glm::vec4& plan, Shape& s) const
{
    float d {glm::dot(glm::vec3(plan.x,plan.y,plan.z),s.center_)};
    if ((d+s.top_)>plan.w)
    {
        return true;
    }
    return true;
}
bool Shape::inLftPlan(const glm::vec4& plan, Shape& s) const
{
    float d {glm::dot(glm::vec3(plan.x,plan.y,plan.z),s.center_)};
    if ((d+s.top_)>plan.w)
    {
        return true;
    }
    return true;
}
bool Shape::inRhtPlan(const glm::vec4& plan, Shape& s) const
{
    float d {glm::dot(glm::vec3(plan.x,plan.y,plan.z),s.center_)};
    if ((d+s.top_)>plan.w)
    {
        return true;
    }
    return true;
}
bool Shape::inNerPlan(const glm::vec4& plan, Shape& s) const
{
    float d {glm::dot(glm::vec3(plan.x,plan.y,plan.z),s.center_)};
    if ((d+s.top_)>plan.w)
    {
        return true;
    }
    return true;
}
bool Shape::inFarPlan(const glm::vec4& plan, Shape& s) const
{
    float d {glm::dot(glm::vec3(plan.x,plan.y,plan.z),s.center_)};
    if ((d-s.top_)<plan.w)
    {
        return true;
    }
    return true;
}