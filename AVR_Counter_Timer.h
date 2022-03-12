
#ifndef AVR_COUNTER_TIMER_H_
#define AVR_COUNTER_TIMER_H_

void Waveform_Gen_NM(uint8_t Comp_Value);
void Waveform_Gen_CTC_FP(uint8_t Comp_Value);
void Waveform_Gen_CTC_DP(uint8_t LP_Comp_Value, uint8_t HP_Comp_Value);

#endif /* AVR_COUNTER_TIMER_H_ */