//===-- RISCVSubtarget.h - Define Subtarget for the RISCV -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the RISCV specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_RISCV_RISCVSUBTARGET_H
#define LLVM_LIB_TARGET_RISCV_RISCVSUBTARGET_H

#include "RISCVFrameLowering.h"
#include "RISCVISelLowering.h"
#include "RISCVInstrInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "RISCVGenSubtargetInfo.inc"

namespace llvm {
class StringRef;

class RISCVSubtarget : public RISCVGenSubtargetInfo {
protected:
  enum RISCVArchEnum {
    RV32,
    RV64
  };

  RISCVArchEnum RISCVArchVersion;

  bool HasM;
  bool HasA;
  bool HasF;
  bool HasD;

  bool UseSoftFloat;

private:
  virtual void anchor();
  RISCVInstrInfo InstrInfo;
  RISCVFrameLowering FrameLowering;
  RISCVTargetLowering TLInfo;
  const SelectionDAGTargetInfo TSInfo;
  bool HasRV64;

  RISCVSubtarget &initializeSubtargetDependencies(StringRef CPU, StringRef FS);

public:
  // Initializes the data members to match that of the specified triple.
  RISCVSubtarget(const Triple &TT, const std::string &CPU,
                 const std::string &FS, const TargetMachine &TM);

  // Parses features string setting specified subtarget options. The
  // definition of this function is auto-generated by tblgen.
  void ParseSubtargetFeatures(StringRef CPU, StringRef FS);

  const RISCVFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }
  const RISCVInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const TargetRegisterInfo *getRegisterInfo() const override {
    return &InstrInfo.getRegisterInfo();
  }
  const RISCVTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
  const SelectionDAGTargetInfo *getSelectionDAGInfo() const override {
    return &TSInfo;
  }
  bool isRV32() const { return RISCVArchVersion == RV32; };
  bool isRV64() const { return RISCVArchVersion == RV64; };

  bool hasM() const { return HasM; };
  bool hasA() const { return HasA; };
  bool hasF() const { return HasF; };
  bool hasD() const { return HasD; };

  bool useSoftFloat() const { return UseSoftFloat; }
};
} // End llvm namespace

#endif
