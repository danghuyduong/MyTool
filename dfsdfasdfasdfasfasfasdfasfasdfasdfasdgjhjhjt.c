/*Transmit NPDU more than 8 byte*/
CanTp_Transmit => s_CreateTxSegmentConnection=> s_CreateFF => CanIf_Transmit(LSduId, &FF) => 1(First Frame)

receiver 2(Fllow Control Frame) = > s_Processs_FlowControlFrame => s_GetTxSegmentConnection( get data in buffer which have dara of cosecutive) => s_CreateCF (this is first FC, create CF and send)
=> CanIf_Transmit=> 3(Consecutive Frame)

CanTp_MainFunction(The main function will be called by the Schedule Manager or by the FREE RUNNING TIMER MODULE according of the call period needed) = > s_CreateCF (this is first FC, create CF and send)
=> CanIf_Transmit	=>  4 (Consecutive Frame)
					=>  5
					=>	6
					.......
					.......

/* Receiver First Frame */
1(First Frame) => Can_MainFunction_Read(This function performs the polling of RX indications when  CAN_RX_PROCESSING is set to POLLING.)
=>CanIf_RxIndication => CanTp_RxIndication => s_Processs_FirstFrame => PduR_CanTpStartOfReception( CanTp  ask  PDU  Router  to  make  a  buffer available  for incoming  data  with  PduR_CanTpStartOfReception callback) => s_CreateFirstFC=> CanIf_Transmit(LSduIdFC, &FC)=> 2(Fllow Control Frame)

receiver 3(Consecutive Frame) => s_Processs_ConsecutiveFrame(NSduId, PduInfoPtr) => PduR_CanTpCopyRxData( coppy data from buffer) => if 3 is not last consecutive of message or last block size => Do nothing

 Can_MainFunction_Read(This function performs the polling of RX indications when  CAN_RX_PROCESSING is set to POLLING.)
=>CanIf_RxIndication => CanTp_RxIndication => s_Processs_SingleFrame => PduR_CanTpStartOfReception( CanTp  ask  PDU  Router  to  make  a  buffer available  for incoming  data  with  PduR_CanTpStartOfReception callback)=> PduR_CanTpCopyRxData