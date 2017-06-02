/* Copyright (c) 2014-2015, 2017, Chan Beom Park <cbpark@gmail.com> */

#ifndef SRC_PDG_NUMBERING_H_
#define SRC_PDG_NUMBERING_H_

#include "particle.h"

namespace lhef {
const ParticleID Electron = {11, -11};
const ParticleID ElecNeutrino = {12, -12};
const ParticleID Muon = {13, -13};
const ParticleID MuonNeutrino = {14, -14};
const ParticleID Tau = {15, -15};
const ParticleID TauNeutrino = {16, -16};

const ParticleID Charm = {4, -4};
const ParticleID Bottom = {5, -5};
const ParticleID Top = {6, -6};

const ParticleID Gluon = {21};
const ParticleID Photon = {22};
const ParticleID Zboson = {23};
const ParticleID Wboson = {24};
const ParticleID Higgs = {25};
}  // namespace lhef

#endif  // SRC_PDG_NUMBERING_H_
