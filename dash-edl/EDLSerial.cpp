#include "EDLSerial.h"

void EDLSerial::begin(Stream &stream) {
  _stream = &stream;
  _index = 0;
}

bool EDLSerial::update() {
  while (_stream->available()) {
    uint8_t byte = _stream->read();
    if (_index < 260) {
      _buffer[_index++] = byte;
    }

    if (_index >= 260) {
      if (parseFrame(_buffer, _frame)) {
        _index = 0;
        return true;
      }
      _index = 0; // reset on invalid frame
    }
  }
  return false;
}

bool EDLSerial::parseFrame(uint8_t *data, EDLFrame &frame) {
  if (data[0] != 0x32 || data[1] != 0x40 || data[2] != 0x50 || data[3] != 0x60) return false;

  frame.frameStamp=data[4] | (data[5] << 8);
  frame.RPM=data[6] | (data[7] << 8);
  frame.MAP=data[8] | (data[9] << 8);
  frame.TPS=(uint8_t)data[10];
  frame.IAT=(int8_t)data[11];
  frame.debugUnused=(int8_t)data[12];
  frame.Batt=(data[13] | (data[14] << 8)) / 37.0f;
  frame.TPSRate=(int8_t)data[15];
  frame.VE=(data[16] | (data[17] << 8)) / 10.0f;
  frame.IgnAngle=data[18] / 2.0f;
  frame.Warmup=(uint8_t)data[19];
  frame.InjOpeningTime=data[20] / 32.0f;
  frame.EMUState=(uint8_t)data[21];
  frame.Egt1=data[22] | (data[23] << 8);
  frame.Egt2=data[24] | (data[25] << 8);
  frame.knockValue=data[26] / 51.0f;
  frame.ignDTH=data[27] | (data[28] << 8);
  frame.ignDTL=data[29] | (data[30] << 8);
  frame.mainLoopSpeed=(data[31] | (data[32] << 8)) / 500.0f;
  frame.idleTarget=data[33] | (data[34] << 8);
  frame.idleDC=(uint8_t)data[35];
  frame.idleStep=(uint8_t)data[36];
  frame.idleAngleCorr=data[37] / 2.0f;
  frame.idleControlActive=(uint8_t)data[38];
  frame.curentPIDCorrection=(int8_t)data[39];
  frame.dwellTime=data[40] / 20.0f;
  frame.dwellError=data[41] / 62.0f;
  frame.overdwell=(uint8_t)data[42];
  frame.pulseWidth=(data[43] | (data[44] << 8)) / 62.0f;
  frame.ase=(uint8_t)data[45];
  frame.fuelCut=(uint8_t)data[46];
  frame.wboRI=data[47] / 51.0f;
  frame.wboHeaterDC=(uint8_t)data[48];
  frame.wboVS=data[49] / 51.0f;
  frame.accEnrich=(uint8_t)data[50];
  frame.accEnrichPW=(data[51] | (data[52] << 8)) / 62.0f;
  frame.egoCorrection=data[53] / 2.0f;
  frame.wboIPMeas=(data[54] | (data[55] << 8)) / 128.0f;
  frame.wboIPNorm=(data[56] | (data[57] << 8)) / 128.0f;
  frame.wboLambda=data[58] / 128.0f;
  frame.pidPTerm=(data[59] | (data[60] << 8)) / 128.0f;
  frame.pidITerm=(data[61] | (data[62] << 8)) / 32.0f;
  frame.pidDTerm=(data[63] | (data[64] << 8)) / 128.0f;
  frame.wasReset=(uint8_t)data[65];
  frame.engineNoise=data[66] / 51.0f;
  frame.wboAFR=data[67] / 10.0f;
  frame.afrTarget=data[68] / 10.0f;
  frame.profiler=(data[69] | (data[70] << 8)) / 500.0f;
  frame.debugW=data[71] | (data[72] << 8);
  frame.knockLevel=data[73] / 51.0f;
  frame.knockFuelEnrich=data[74] / 8.0f;
  frame.knockIgnRetard=data[75] / 8.0f;
  frame.iatIgnTrim=data[76] / 2.0f;
  frame.cltIgnTrim=data[77] / 2.0f;
  frame.ignFromTable=data[78] / 2.0f;
  frame.vssFreq=(data[79] | (data[80] << 8)) / 4.0f;
  frame.vssSpeed=(data[81] | (data[82] << 8)) / 4.0f;
  frame.gearRatio=(data[83] | (data[84] << 8)) / 8.0f;
  frame.gear=(int8_t)data[85];
  frame.shiftLightOn=(uint8_t)data[86];
  frame.pwmOutputDC=(uint8_t)data[87];
  frame.Baro=(uint8_t)data[88];
  frame.BaroCorr=(uint8_t)data[89];
  frame.lcActive=(uint8_t)data[90];
  frame.lcIgnRetard=data[91] / 2.0f;
  frame.lcFuelEnrich=(int8_t)data[92];
  frame.analogIn1=data[93] / 51.0f;
  frame.analogIn2=data[94] / 51.0f;
  frame.analogIn3=data[95] / 51.0f;
  frame.analogIn4=data[96] / 51.0f;
  frame.ignSyncStatus=(uint8_t)data[97];
  frame.ignError=(uint8_t)data[98];
  frame.boostDC=(uint8_t)data[99];
  frame.boostDCFromTable=(uint8_t)data[100];
  frame.boostTarget=data[101] | (data[102] << 8);
  frame.boostCorrection=(uint8_t)data[103];
  frame.boostTableSet=(uint8_t)data[104];
  frame.boostTargetFromTable=data[105] | (data[106] << 8);
  frame.boostPIDCorrection=(int8_t)data[107];
  frame.camSyncPrimTooth=(uint8_t)data[108];
  frame.nitrousActive=(uint8_t)data[109];
  frame.nitrousIgnMod=data[110] / 2.0f;
  frame.nitrousFuelScale=(uint8_t)data[111];
  frame.flatShiftActive=(uint8_t)data[112];
  frame.flatShiftCutSpark=(uint8_t)data[113];
  frame.flatShiftCutFuel=(uint8_t)data[114];
  frame.parametricOutput1=(uint8_t)data[115];
  frame.camSyncPresent=(uint8_t)data[116];
  frame.parametricOutput2=(uint8_t)data[117];
  frame.accIgnCorr=data[118] / 2.0f;
  frame.injDC=data[119] / 2.0f;
  frame.emuTemp=(int8_t)data[120];
  frame.iatFuelCorr=(uint8_t)data[121];
  frame.parametricOutput3=(uint8_t)data[122];
  frame.parametricOutput4=(uint8_t)data[123];
  frame.cam1Angle=(data[124] | (data[125] << 8)) / 2.0f;
  frame.cam2Angle=(data[126] | (data[127] << 8)) / 2.0f;
  frame.cam1ValveDC=(uint8_t)data[128];
  frame.cam2ValveDC=(uint8_t)data[129];
  frame.cam1AngleTarget=(data[130] | (data[131] << 8)) / 2.0f;
  frame.cam2AngleTarget=(data[132] | (data[133] << 8)) / 2.0f;
  frame.cam2Present=(uint8_t)data[134];
  frame.pitLimiterActive=(uint8_t)data[135];
  frame.pitLimiterTorqueReduction=(uint8_t)data[136];
  frame.oilPressure=data[137] / 16.0f;
  frame.oilTemperature=(uint8_t)data[138];
  frame.fuelPressure=data[139] / 32.0f;
  frame.CLT=data[140] | (data[141] << 8);
  frame.sparkCutPercent=(uint8_t)data[142];
  frame.etcDC=data[143] / 2.0f;
  frame.etcTarget=data[144] / 2.0f;
  frame.etcPos=data[145] / 2.0f;
  frame.etcError=(data[146] | (data[147] << 8)) / 4.0f;
  frame.etcDeltaError=data[148] / 4.0f;
  frame.tablesSet=(uint8_t)data[149];
  frame.vtecOn=(uint8_t)data[150];
  frame.flexFuelFrequency=(data[151] | (data[152] << 8)) / 2.0f;
  frame.flexFuelEthanolContent=data[153] / 2.0f;
  frame.ffBlendVE=data[154] / 2.0f;
  frame.ffBlendIgn=data[155] / 2.0f;
  frame.ffBlendAFR=data[156] / 2.0f;
  frame.ffBlendBoost=data[157] / 2.0f;
  frame.ffTemp=(int8_t)data[158];
  frame.ffTempFuelCorr=(uint8_t)data[159];
  frame.alsActive=(uint8_t)data[160];
  frame.alsIgnAngle=data[161] / 2.0f;
  frame.alsSparkCut=(uint8_t)data[162];
  frame.alsFuelCorr=(int8_t)data[163];
  frame.ffBlendCrankingFuel=data[164] / 2.0f;
  frame.ignSparkCount=(uint8_t)data[165];
  frame.idleIgnCutPercent=(uint8_t)data[166];
  frame.tpsVoltage=data[167] / 51.0f;
  frame.dbwPotError=data[168] / 51.0f;
  frame.cel=data[169] | (data[170] << 8);
  frame.tcdRPM=data[171] | (data[172] << 8);
  frame.tcdRPMRaw=data[173] | (data[174] << 8);
  frame.tcTorqueReduction=data[175] / 2.0f;
  frame.ffBlendWarmup=data[176] / 2.0f;
  frame.ffBlendASE=data[177] / 2.0f;
  frame.canBUSState=(uint8_t)data[178];
  frame.canBUSSwitech=(uint8_t)data[179];
  frame.tcAdjPos=(uint8_t)data[180];
  frame.RPM2nd=data[181] | (data[182] << 8);
  frame.deltaFPR=data[183] | (data[184] << 8);
  frame.fprCorrection=data[185] | (data[186] << 8);
  frame.muxSwitch=(uint8_t)data[187];
  frame.fuelLevel=(uint8_t)data[188];
  frame.CANain1=data[189] / 51.0f;
  frame.CANain2=data[190] / 51.0f;
  frame.CANain3=data[191] / 51.0f;
  frame.CANain4=data[192] / 51.0f;
  frame.inj1Trim=(uint8_t)data[193];
  frame.inj2Trim=(uint8_t)data[194];
  frame.inj3Trim=(uint8_t)data[195];
  frame.inj4Trim=(uint8_t)data[196];
  frame.inj5Trim=(uint8_t)data[197];
  frame.inj6Trim=(uint8_t)data[198];
  frame.boostDCErrCor=(int8_t)data[207];
  frame.knockBits=data[208] | (data[209] << 8);
  frame.ralTarget=data[210] | (data[211] << 8);
  frame.ralIgnition=data[212] / 2.0f;
  frame.ralActive=(uint8_t)data[213];
  frame.etcFrictionCorr=data[214] / 2.0f;
  frame.canSwitch=(uint8_t)data[219];
  frame.acPressure=data[220] | (data[221] << 8);
  frame.acClutch=(uint8_t)data[222];
  frame.chargeTemp=(int8_t)data[223];
  frame.lambdaTarget=data[224] / 100.0f;
  frame.acEvap=(int8_t)data[225];
  frame.scondarypulseWidth=(data[226] | (data[227] << 8)) / 62.0f;
  frame.secondaryInjDC=data[228] / 2.0f;
  frame.secondaryInjSplit=data[229] / 2.0f;
  frame.miscOutputs=(uint8_t)data[230];
  frame.miscFlags=(uint8_t)data[231];
  frame.decEnrich=(uint8_t)data[232];
  frame.decEnrichPW=(data[233] | (data[234] << 8)) / 62.0f;
  frame.ignCorrections=data[235] | (data[236] << 8);
  frame.fuelCorrections=data[237] | (data[238] << 8);
  frame.timer1=data[239] / 4.0f;
  frame.timer2=data[240] / 4.0f;
  frame.timerFuelEnrich=(uint8_t)data[241];
  frame.timerBoostCorr=(uint8_t)data[242];
  frame.timerIgnCorr=data[243] / 2.0f;
  frame.nitrousFuelAdder=data[244] / 8.0f;
  frame.mswitchState=(uint8_t)data[245];
  frame.fcProbability=data[246] / 2.0f;
  frame.ffFuelScale=(uint8_t)data[247];
  frame.gcActive=(uint8_t)data[248];
  frame.fuelUsage=(data[249] | (data[250] << 8)) / 100.0f;
  frame.injectionAngle=data[251] | (data[252] << 8);
  frame.gearBoxOilTemperature=(uint8_t)data[253];
  frame.reserved1b=(uint8_t)data[254];
  frame.reserved2=data[255] | (data[256] << 8);
  frame.reserved3=data[257] | (data[258] << 8);
  frame.reserved4=(uint8_t)data[259];

  return true;
}

const EDLFrame &EDLSerial::getFrame() const {
  return _frame;
}