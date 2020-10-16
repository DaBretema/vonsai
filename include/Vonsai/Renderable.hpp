#pragma once

#include "Bindable.hpp"
#include "Transform.hpp"
#include "Wraps/_glm.hpp"

#include <unordered_map>
#include <vector>

#include "CPP_HELPERS.hpp"

namespace Vonsai {

//---------------------------------------------------------------------------------------------------------------------

enum class VoTexs {
  DIFFUSE,
  SPECULAR,
  AMBIENT,
  EMISSIVE,
  HEIGHT,
  NORMALS,
  SHININESS,
  OPACITY,
  DISPLACEMENT,
  LIGHTMAP,
  REFLECTION,
  UNKNOWN,
};

//---------------------------------------------------------------------------------------------------------------------

struct VoMaterial {
  std::string                             name{""};
  float                                   shine{0.f}, shineI{0.f}, reflectivity{0.f}, refraction{0.f};
  glm::vec4                               diffuse{1.f}, ambient{1.f}, specular{1.f}, emissive{1.f};
  std::unordered_map<VoTexs, std::string> texPaths{
      {VoTexs::DIFFUSE, ""},      {VoTexs::SPECULAR, ""}, {VoTexs::AMBIENT, ""},   {VoTexs::EMISSIVE, ""},
      {VoTexs::HEIGHT, ""},       {VoTexs::NORMALS, ""},  {VoTexs::SHININESS, ""}, {VoTexs::OPACITY, ""},
      {VoTexs::DISPLACEMENT, ""}, {VoTexs::LIGHTMAP, ""}, {VoTexs::REFLECTION, ""}};

  void info() const;
};

//---------------------------------------------------------------------------------------------------------------------

struct RenderablePOD {
  std::vector<unsigned int> indices{};
  std::vector<glm::vec3>    positions{};
  std::vector<glm::vec3>    normals{};
  std::vector<glm::vec2>    texCoords{};
  std::vector<glm::vec3>    tangents{};
  std::vector<glm::vec3>    bitangents{};
};

//---------------------------------------------------------------------------------------------------------------------

class Renderable : public Bindable {
public:
  Transform transform;

  Renderable(std::string const &name, RenderablePOD const &a_data);
  DC_DISALLOW_COPY(Renderable)
  DC_ALLOW_MOVE_H(Renderable)
  virtual ~Renderable() = default;

  void draw() const;
  bool isValid() const;

  void setEBO(const std::vector<unsigned int> &a_data);
  void addVBO(const std::vector<glm::vec3> &a_data);
  void addVBO(const std::vector<glm::vec2> &a_data);
  void addVBO(const std::vector<float> &a_data, int a_dataSize);

private:
  std::string                                                 m_name;
  static inline std::unordered_map<std::string, unsigned int> s_uniqueRenderableNames{};

  bool         m_valid{false};
  mutable bool m_alertOnceInvalid{false};
  mutable bool m_alertOnceDraw{false};

  mutable unsigned int m_location{0u};
  unsigned int         m_VAO{0u};
  unsigned int         m_EBO{0u};
  unsigned int         m_indexCount{0u};

  void bind() const override;
  void unbind() const override;
};

// --------------------------------------------------------------------------------------------------------------------

class RenderableGroup {
public:
  explicit RenderableGroup(std::string const &name) : m_name(name) {}
  DC_DISALLOW_COPY(RenderableGroup)
  DC_ALLOW_MOVE_H(RenderableGroup)

  /*TEMP*/ inline std::vector<Renderable> const &group() const { return m_group; }

  Transform * transform(unsigned int idx);
  inline void addMaterial(VoMaterial &material) { m_materials.push_back(material); }
  inline void addRenderable(std::string const &name, RenderablePOD const &data) { m_group.emplace_back(name, data); }


private:
  std::string             m_name{};
  std::vector<Renderable> m_group{};
  std::vector<VoMaterial> m_materials{};
};

// --------------------------------------------------------------------------------------------------------------------

} // namespace Vonsai
