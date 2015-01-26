#ifndef SRC_PDG_NUMBERING_H_
#define SRC_PDG_NUMBERING_H_

#include "type.h"

namespace lhef {
const ParticleID Electron = {11, -11};
const ParticleID ElecNeu  = {12};
const ParticleID Muon     = {13, -13};
const ParticleID MuonNeu  = {14};
const ParticleID Tau      = {15, -15};
const ParticleID TauNeu   = {16};

const ParticleID Charm    = {4, -4};
const ParticleID Bottom   = {5, -5};
const ParticleID Top      = {6, -6};

const ParticleID Gluon    = {21};
const ParticleID Photon   = {22};
const ParticleID Zboson   = {23};
const ParticleID Wboson   = {24};
const ParticleID Higgs    = {25};
}  // namespace lhef

#endif  // SRC_PDG_NUMBERING_H_
