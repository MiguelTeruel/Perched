#pragma once

#include "CameraLUM.hpp"
#include "../../glm/gtx/string_cast.hpp"
#include "../../glm/gtx/matrix_decompose.hpp"

struct Shape
{
    glm::vec3 center_;
    float radius_;
    float top_;
    float bot_;
    float right_;
    float left_;
    float far_;
    float near_;

    Shape();
    Shape( float radius, glm::vec3 center );
    
    bool isOnFrustum(CameraLUM * cam, glm::mat4 & mat) const;
    bool isOnForwardPlan(const glm::vec4& plan, Shape& s) const;
    
    bool inTopPlan(const glm::vec4& plan, Shape& s) const;
    bool inBotPlan(const glm::vec4& plan, Shape& s) const;
    bool inLftPlan(const glm::vec4& plan, Shape& s) const;
    bool inRhtPlan(const glm::vec4& plan, Shape& s) const;
    bool inNerPlan(const glm::vec4& plan, Shape& s) const;
    bool inFarPlan(const glm::vec4& plan, Shape& s) const;
};
