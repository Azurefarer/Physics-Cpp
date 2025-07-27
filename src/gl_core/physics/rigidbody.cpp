#include "physics/rigidbody.h"


RigidBody::RigidBody(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material) 
    : Image(mesh, material)
{};


// TODO: look at Godot's implementation
