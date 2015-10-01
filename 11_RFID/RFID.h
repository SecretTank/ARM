#define	CommandReg	 0x01 		// starts and stops command execution
#define	ComIEnReg		 0x02 		// enable and disable interrupt request control bits
#define	DivIEnReg		 0x03 		// enable and disable interrupt request control bits
#define	ComIrqReg		 0x04 		// interrupt request bits
#define	DivIrqReg		 0x05 		// interrupt request bits
#define	ErrorReg		 0x06 		// error bits showing the error status of the last command executed 
#define	Status1Reg		 0x07 		// communication status bits
#define	Status2Reg		 0x08 		// receiver and transmitter status bits
#define	FIFODataReg		 0x09 		// input and output of 64 byte FIFO buffer
#define	FIFOLevelReg	 0x0A 		// number of bytes stored in the FIFO buffer
#define	WaterLevelReg	 0x0B 		// level for FIFO underflow and overflow warning
#define	ControlReg		 0x0C 		// miscellaneous control registers
#define	BitFramingReg	 0x0D 		// adjustments for bit-oriented frames
#define	CollReg			 0x0E 		// bit position of the first bit-collision detected on the RF interface
//						  0x0F			// reserved for future use

// Page 1: Command
// 						  0x10			// reserved for future use
#define	ModeReg			 0x11 		// defines general modes for transmitting and receiving 
#define	TxModeReg		 0x12 		// defines transmission data rate and framing
#define	RxModeReg		 0x13 		// defines reception data rate and framing
#define	TxControlReg	 0x14 		// controls the logical behavior of the antenna driver pins TX1 and TX2
#define	TxASKReg		 0x15 		// controls the setting of the transmission modulation
#define	TxSelReg		 0x16 		// selects the internal sources for the antenna driver
#define	RxSelReg		 0x17 		// selects internal receiver settings
#define	RxThresholdReg	 0x18 		// selects thresholds for the bit decoder
#define	DemodReg		 0x19 		// defines demodulator settings
#define	MfTxReg			 0x1C 		// controls some MIFARE communication transmit parameters
#define	MfRxReg			 0x1D 		// controls some MIFARE communication receive parameters
// 						  0x1E			// reserved for future use
#define	SerialSpeedReg	 0x1F 		// selects the speed of the serial UART interface
	
// Page 2: Configuration
// 						  0x20			// reserved for future use
#define	CRCResultRegH	 0x21 		// shows the MSB and LSB values of the CRC calculation
#define	CRCResultRegL	 0x22 	
#define	ModWidthReg		 0x24 		// controls the ModWidth setting?
#define	RFCfgReg		 0x26 		// configures the receiver gain
#define	GsNReg			 0x27 		// selects the conductance of the antenna driver pins TX1 and TX2 for modulation 
#define	CWGsPReg		 0x28 		// defines the conductance of the p-driver output during periods of no modulation
#define	ModGsPReg		 0x29 		// defines the conductance of the p-driver output during periods of modulation
#define	TModeReg		 0x2A 		// defines settings for the internal timer
#define	TPrescalerReg	 0x2B 		// the lower 8 bits of the TPrescaler value. The 4 high bits are in TModeReg.
#define	TReloadRegH		 0x2C 		// defines the 16-bit timer reload value
#define	TReloadRegL		 0x2D 	
#define	TCounterValueRegH		0x2E 		// shows the 16-bit timer value
#define	TCounterValueRegL		0x2F 	
	
// Page 3: Test Registers
// 						  0x30			// reserved for future use
#define	TestSel1Reg		 0x31 		// general test signal configuration
#define	TestSel2Reg		 0x32 		// general test signal configuration
#define	TestPinEnReg	 0x33 		// enables pin output driver on pins D1 to D7
#define	TestPinValueReg	 0x34 		// defines the values for D1 to D7 when it is used as an I/O bus
#define	TestBusReg		 0x35 		// shows the status of the internal test bus
#define	AutoTestReg		 0x36 		// controls the digital self test
#define	VersionReg		 0x37 		// shows the software version
#define	AnalogTestReg	 0x38 		// controls the pins AUX1 and AUX2
#define	TestDAC1Reg		 0x39 		// defines the test value for TestDAC1
#define	TestDAC2Reg		 0x3A 		// defines the test value for TestDAC2
#define	TestADCReg		 0x3B << 1		// shows the value of ADC I and Q channels

#define	COMMAND_Idle				0x00	// no action, cancels current command execution
#define	COMMAND_Mem					0x01	// stores 25 bytes into the internal buffer
#define	COMMAND_GenerateRandomID	0x02	// generates a 10-byte random ID number
#define	COMMAND_CalcCRC				0x03	// activates the CRC coprocessor or performs a self test
#define	COMMAND_Transmit			0x04	// transmits data from the FIFO buffer
#define	COMMAND_NoCmdChange			0x07	// no command change, 
#define	COMMAND_Receive				0x08	// activates the receiver circuits
#define	COMMAND_Transceive 			0x0C
#define	COMMAND_MFAuthent 			0x0E	// performs the MIFARE standard authentication as a reader
#define	COMMAND_SoftReset			0x0F		// resets the MFRC522
