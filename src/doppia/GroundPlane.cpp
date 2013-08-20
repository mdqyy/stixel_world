// Copyright (c) 2009-2012, KU Leuven All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// Neither the name of the KU Leuven nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
// The source code and the binaries created using them can only be used for scientific research and education purposes. Any commercial use of this software is prohibited. For a different license, please contact the contributors directly.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL KU Leuven BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// The original version of this code can be found at https://bitbucket.org/rodrigob/doppia

#include "GroundPlane.hpp"

#include <cmath>

namespace doppia {


GroundPlane::GroundPlane()
    :  Eigen::Hyperplane<float, 3>()
{
    // nothing to do here
    return;
}



GroundPlane::GroundPlane(const GroundPlane::VectorType& n, GroundPlane::Scalar d)
    :  Eigen::Hyperplane<float, 3>(n,d)
{
    // nothing to do here
    return;
}


void GroundPlane::set_from_metric_units(const float pitch, const float roll, const float height)
{
    GroundPlane &the_plane = (*this);

    Eigen::Vector3f normal;

    // ground plane normal should be similar to x = 0, y = -1, z =0;
    normal(IDX_X) = sin(roll);
    normal(IDX_Z) = sin(pitch);
    // ensure a vector of length 1
    normal(IDX_Y) = -sqrt(1 - (normal(IDX_X)* normal(IDX_X) +  normal(IDX_Z)* normal(IDX_Z)));

    the_plane = GroundPlane(normal, height);

    return;
}

const float &GroundPlane::get_height() const
{
    return this->offset();
}

float &GroundPlane::get_height()
{
    return this->offset();
}

float GroundPlane::get_pitch() const
{
    // we assume no roll
    return std::asin(this->normal()(IDX_Z));
}

} // end of namespace doppia