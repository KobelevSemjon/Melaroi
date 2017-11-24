#include "scomponent.h"



SMainComponent::SMainComponent(const QImage &src)
{
    SCovarienceMatrix cov_mat(src);
    eigenvalues=cov_mat.eigenvalues();
    eigenvectors=cov_mat.eigenvectors(eigenvalues);
    auto v=eigenvectors.col(eigenvalues.posMax());
    r=v.x;  g=v.y;  b=v.z;
}
