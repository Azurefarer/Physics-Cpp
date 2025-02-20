#ifndef GL_CORE_TYPES_H_
#define GL_CORE_TYPES_H_

#include <functional>
#include "glm/glm.hpp"
// I will use the glm library for data types.
// It is important to note that the default coordinate system this program works with is Cartesian.
// Using Cartesian Coordinates as the default, I would like to define coordinate system transformations.
// e.g. Cart to Polar, Cart to Sphere, Cart to Cyl, etc...
// I will likely not define transformations from Polar to Sphere or Sphere to Cyl.
// There will be a forward transformation matrix and a backwards tansformation matrix.


// The most important thing about any coordinate system is the Metric Tensor(Metric).
// The Metric will either be given or defined by the Reimann Curvature Tensor and the Energy-Momentum Tensor
// The Metric Transforms one set of coordinates(e.g. R2, R3, Rn) into another with two Forward or two Backward transforms
// The Forward transform would look like the "partial i / partial f"
// The Backward transform would look like the "partial f / partial i"
// Where i and j are contravariant vectors ( i and j are the coordinates )

// Not sure how currently, but I can transform the space-time coordinates into My context's coordinate system.
// This should be useful so I can do easy math in generally accepted Physics notation
// And transform the coordinates on the GPU with the metric tensor.

// Generally we will have some Metric represented in some coordinate system and we will want to
// Transform it back into Minkowski space (Flat Space-Time, Non-Euclidean).
// I believe the Metric will come from Einstein's Field Eqns with the aforementioned RCT & EMT
// This makes things sort of ideal because the Jacobian

// Step 1 figure out what it would look like to implement just flat-space
// Step 2 Implement a coordinate system for light diffraction in water.
//          An object will shrink in the y direction but not x or z
//          i.e. The y basis vector of the new underwater coordinate system is larger than in flat space
//                  xi = xf | yi = 0.5*yf | zi = zf
//      The actual object won't shrink because it is invariant between coord systems
//      The vector components will shrink while the basis vectors enlarge

const float c = 300000000; ///meters per second

class CoordinateSystem {
    private:
        std::vector<glm::vec3> m_basis;
        glm::mat4 m_metric;
};

class Tensor {
    public:
        glm::mat4 m_minkowski()
};

class basis {
    public:

};

namespace CoordTrans {
        const glm::mat2 EucAngJacobian2D(0, 0, 0, 0);

        glm::mat2 Jacobian2;

        // Function for converting 2D Cartesian to Polar
        glm::vec2 Euc2Ang(const glm::vec2& vec) {
            float r = glm::length(vec);          // Calculate radial distance
            float theta = atan2(vec.y, vec.x);   // Calculate angle (in radians)
            return glm::vec2(r, theta);          // Polar coordinates (r, theta)
        }

        // Function for converting 3D Cartesian to Spherical
        glm::vec3 Euc2Ang(const glm::vec3& vec) {
            float r = glm::length(vec);           // Calculate radial distance
            float theta = atan2(vec.y, vec.x);    // Calculate angle (in radians)
            float phi = acos(vec.z / r);          // Calculate elevation angle (in radians)
            return glm::vec3(r, theta, phi);      // Spherical coordinates (r, theta, phi)
        }

        // Function for converting 4D Cartesian to Hyperspherical
        glm::vec4 Euc2Ang(const glm::vec4& vec) {
            float r = glm::length(vec);            // Calculate radial distance
            float theta = atan2(vec.y, vec.x);     // Calculate angle (in radians)
            float phi = acos(vec.z / r);           // Calculate elevation angle (in radians)
            float psi = atan2(sqrt(vec.x * vec.x + vec.y * vec.y), vec.w); // Additional angle for 4D
            return glm::vec4(r, theta, phi, psi);  // Hyperspherical coordinates (r, theta, phi, psi)
        }
};


// Cartesian 2D vector
class Cart2 {
    public:
        float x, y;

        Cart2(float x = 1.0f, float y = 1.0f) : x(x), y(y) {}

        Cart2 operator+(const Cart2& vec2) const {
            return Cart2(x + vec2.x, y + vec2.y);
        }
        Cart2 operator-(const Cart2& vec2) const {
            return Cart2(x - vec2.x, y - vec2.y);
        }
        Cart2 operator*(const float& scalar) const {
            return Cart2(x * scalar, y * scalar);
        }
        float operator*(const Cart2& vec2) const {
            return x * vec2.x + y * vec2.y;
        }
        // Cart2 operator*(const Cart2& vec2) const {
        //     return Cart2(x * scalar, y * scalar);
        // }
        float cross(const Cart2& vec2);
};

// Polar 2D vector
class Polar2 {
    public:
    float r, theta;
        Polar2(float r = 1.0f, float theta = 1.0f) : r(r), theta(theta) {}

        Polar2 operator+(const Polar2& addition) const {
            return Polar2(r + addition.r, theta + addition.theta);
        }
};

#endif
