#include "misc/tensor.h"

// Tensor::Tensor(Tensor& t) {
//     m_i = t.get_mi();
//     m_j = t.get_mj();
// }

glm::vec4 Tensor::get_vec(TensorCon tcon) {
    glm::vec4 out = glm::vec4(tcon.u1, tcon.u2, tcon.u3, tcon.u4);
    return out;
}

glm::vec4 Tensor::get_basis(TensorCo tco) {
    glm::vec4 out = glm::vec4(tco.l1, tco.l2, tco.l3, tco.l4);
    return out;
}
