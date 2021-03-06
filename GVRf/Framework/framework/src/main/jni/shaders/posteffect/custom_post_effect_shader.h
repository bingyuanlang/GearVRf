/* Copyright 2015 Samsung Electronics Co., LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/***************************************************************************
 * A user-made shader for a post effects.
 ***************************************************************************/

#ifndef CUSTOM_POST_EFFECT_SHADER_H_
#define CUSTOM_POST_EFFECT_SHADER_H_

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <mutex>

#include "gl/gl_headers.h"
#include "glm/glm.hpp"

#include "objects/hybrid_object.h"
#include "objects/components/camera.h"
#include "engine/memory/gl_delete.h"

namespace gvr {
class GLProgram;
class RenderTexture;
class PostEffectData;

class CustomPostEffectShader: public HybridObject {
public:
    CustomPostEffectShader(const char* vertex_shader, const char* fragment_shader);
    virtual ~CustomPostEffectShader();

    void addTextureKey(const std::string& variable_name, const std::string& key);
    void addFloatKey(const std::string& variable_name, const std::string& key);
    void addVec2Key(const std::string& variable_name, const std::string& key);
    void addVec3Key(const std::string& variable_name, const std::string& key);
    void addVec4Key(const std::string& variable_name, const std::string& key);
    void addMat4Key(const std::string& variable_name, const std::string& key);
    void render(Camera* camera,
            RenderTexture* render_texture,
            PostEffectData* post_effect_data,
            std::vector<glm::vec3>& vertices,
            std::vector<glm::vec2>& tex_coords,
            std::vector<unsigned short>& triangles);
    static int getGLTexture(int n);


private:
    CustomPostEffectShader(
            const CustomPostEffectShader& custom_post_effect_shader);
    CustomPostEffectShader(CustomPostEffectShader&& custom_post_effect_shader);
    CustomPostEffectShader& operator=(
            const CustomPostEffectShader& custom_post_effect_shader);
    CustomPostEffectShader& operator=(
            CustomPostEffectShader&& custom_post_effect_shader);

private:
    GLProgram* program_;
    GLuint a_position_;
    GLuint a_tex_coord_;
    GLuint u_texture_;
    GLuint u_projection_matrix_;
    GLuint u_right_eye_;

    std::mutex lock_;
    std::map<std::pair<std::string, std::string>, GLint> texture_keys_;
    std::map<std::pair<std::string, std::string>, GLint> float_keys_;
    std::map<std::pair<std::string, std::string>, GLint> vec2_keys_;
    std::map<std::pair<std::string, std::string>, GLint> vec3_keys_;
    std::map<std::pair<std::string, std::string>, GLint> vec4_keys_;
    std::map<std::pair<std::string, std::string>, GLint> mat4_keys_;

    std::string vertex_shader_;
    std::string fragment_shader_;

    // add vertex array object
    GLuint vaoID_;
    GlDelete* deleter_;
};

}
#endif
