/******************************************************************************
Copyright (c) 2018, Alexander W. Winkler. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#include <towr/models/robot_model.h>

#include <towr/models/examples/monoped_model.h>
#include <towr/models/examples/biped_model.h>
#include <towr/models/examples/hyq_model.h>
#include <towr/models/examples/anymal_model.h>
#include <towr/models/examples/mini_model.h>
#include <towr/models/examples/speedy_model.h>
#include <towr/models/examples/universal_model.h>
#include <towr/models/examples/universalpayload_model.h>
#include <towr/models/examples/massivo_model.h>
#include <towr/models/examples/centaur_model.h>
#include <towr/models/examples/vertex_model.h>
#include <towr/models/examples/vitruvianbiped_model.h>
#include <towr/models/examples/anymalbear_model.h>


namespace towr {


RobotModel::RobotModel(Robot robot)
{
  switch (robot) {
    case Monoped:
      dynamic_model_   = std::make_shared<MonopedDynamicModel>();
      kinematic_model_ = std::make_shared<MonopedKinematicModel>();
      break;
    case VitruvianBiped:
      dynamic_model_   = std::make_shared<VitruvianBipedDynamicModel>();
      kinematic_model_ = std::make_shared<VitruvianBipedKinematicModel>();
      break;
    case Biped:
      dynamic_model_   = std::make_shared<BipedDynamicModel>();
      kinematic_model_ = std::make_shared<BipedKinematicModel>();
      break;
    case Hyq:
      dynamic_model_   = std::make_shared<HyqDynamicModel>();
      kinematic_model_ = std::make_shared<HyqKinematicModel>();
      break;
    case Anymal:
      dynamic_model_   = std::make_shared<AnymalDynamicModel>();
      kinematic_model_ = std::make_shared<AnymalKinematicModel>();
      break;
    case AnymalBear:
      dynamic_model_   = std::make_shared<AnymalBearDynamicModel>();
      kinematic_model_ = std::make_shared<AnymalBearKinematicModel>();
      break;
    case Mini:
      dynamic_model_   = std::make_shared<MiniDynamicModel>();
      kinematic_model_ = std::make_shared<MiniKinematicModel>();
      break;
    case Speedy:
      dynamic_model_   = std::make_shared<SpeedyDynamicModel>();
      kinematic_model_ = std::make_shared<SpeedyKinematicModel>();
      break;
    case Universal:
      dynamic_model_   = std::make_shared<UniversalDynamicModel>();
      kinematic_model_ = std::make_shared<UniversalKinematicModel>();
      break;
    case UniversalPayload:
      dynamic_model_   = std::make_shared<UniversalPayloadDynamicModel>();
      kinematic_model_ = std::make_shared<UniversalPayloadKinematicModel>();
      break;
    case Massivo:
      dynamic_model_   = std::make_shared<MassivoDynamicModel>();
      kinematic_model_ = std::make_shared<MassivoKinematicModel>();
      break;
    case Centaur:
      dynamic_model_   = std::make_shared<CentaurDynamicModel>();
      kinematic_model_ = std::make_shared<CentaurKinematicModel>();
      break;
    case Vertex:
      dynamic_model_   = std::make_shared<VertexDynamicModel>();
      kinematic_model_ = std::make_shared<VertexKinematicModel>();
      break;
    default:
      assert(false); // Error: Robot model not implemented.
      break;
  }
}


} // namespace towr


