#define	COMMANDREG	 0x01 		// starts and stops command execution
#define	COMIENREG		 0x02 		// enable and disable interrupt request control bits
#define	DIVIENREG		 0x03 		// enable and disable interrupt request control bits
#define	COMIRQREG		 0x04 		// interrupt request bits
#define	DIVIRQREG		 0x05 		// interrupt request bits
#define	ERRORREG		 0x06 		// error bits showing the error status of the last command executed 
#define	STATUS1REG		 0x07 		// communication status bits
#define	STATUS2REG		 0x08 		// receiver and transmitter status bits
#define	FIFODATAREG		 0x09 		// input and output of 64 byte FIFO buffer
#define	FIFOLEVELREG	 0x0A 		// number of bytes stored in the FIFO buffer
#define	WATERLEVELREG	 0x0B 		// level for FIFO underflow and overflow warning
#define	CONTROLREG		 0x0C 		// miscellaneous control registers
#define	BITFRAMINGREG	 0x0D 		// adjustments for bit-oriented frames
#define	COLLREG			 0x0E 		// bit position of the first bit-collision detected on the RF interface
// Page 1: Command
#define	MODEREG			 0x11 		// defines general modes for transmitting and receiving 
#define	TXMODEREG		 0x12 		// defines transmission data rate and framing
#define	RXMODEREG		 0x13 		// defines reception data rate and framing
#define	TXCONTROLREG	 0x14 		// controls the logical behavior of the antenna driver pins TX1 and TX2
#define	TXASKREG		 0x15 		// controls the setting of the transmission modulation
#define	TXSELREG		 0x16 		// selects the internal sources for the antenna driver
#define	RXSELREG		 0x17 		// selects internal receiver settings
#define	RXTHRESHOLDREG	 0x18 		// selects thresholds for the bit decoder
#define	DEMODREG		 0x19 		// defines demodulator settings
#define	MFTXREG			 0x1C 		// controls some MIFARE communication transmit parameters
#define	MFRXREG			 0x1D 		// controls some MIFARE communication receive parameters
#define	SERIALSPEEDREG	 0x1F 		// selects the speed of the serial UART interface
// Page 2: Configuration
#define	CRCRESULTREGH	 0x21 		// shows the MSB and LSB values of the CRC calculation
#define	CRCRESULTREGL	 0x22 	
#define	MODWIDTHREG		 0x24 		// controls the ModWidth setting?
#define	RFCFGREG		 0x26 		// configures the receiver gain
#define	GSNREG			 0x27 		// selects the conductance of the antenna driver pins TX1 and TX2 for modulation 
#define	CWGSPREG		 0x28 		// defines the conductance of the p-driver output during periods of no modulation
#define	MODGSPREG		 0x29 		// defines the conductance of the p-driver output during periods of modulation
#define	TMODEREG		 0x2A 		// defines settings for the internal timer
#define	TPRESCALERREG	 0x2B 		// the lower 8 bits of the TPrescaler value. The 4 high bits are in TModeReg.
#define	TRELOADREGH		 0x2C 		// defines the 16-bit timer reload value
#define	TRELOADREGL		 0x2D 	
#define	TCOUNTERVALUEREGH		0x2E 		// shows the 16-bit timer value
#define	TCOUNTERVALUEREGL		0x2F 	
// Page 3: Test Registers
#define	TESTSEL1REG		 0x31 		// general test signal configuration
#define	TESTSEL2REG		 0x32 		// general test signal configuration
#define	TESTPINENREG	 0x33 		// enables pin output driver on pins D1 to D7
#define	TESTPINVALUEREG	 0x34 		// defines the values for D1 to D7 when it is used as an I/O bus
#define	TESTBUSREG		 0x35 		// shows the status of the internal test bus
#define	AUTOTESTREG		 0x36 		// controls the digital self test
#define	VERSIONREG		 0x37 		// shows the software version
#define	ANALOGTESTREG	 0x38 		// controls the pins AUX1 and AUX2
#define	TESTDAC1REG		 0x39 		// defines the test value for TestDAC1
#define	TESTDAC2REG		 0x3A 		// defines the test value for TestDAC2
#define	TESTADCREG		 0x3B << 1		// shows the value of ADC I and Q channels

#define	PCD_IDLE				0x00	// no action, cancels current command execution
#define	PCD_MEM					0x01	// stores 25 bytes into the internal buffer
#define	PCD_GENERATERANDOMID	0x02	// generates a 10-byte random ID number
#define	PCD_CALCCRC				0x03	// activates the CRC coprocessor or performs a self test
#define	PCD_TRANSMIT			0x04	// transmits data from the FIFO buffer
#define	PCD_NOCMDCHANGE			0x07	// no command change, can be used to modify the CommandReg register bits without affecting the command, for example, the PowerDown bit
#define	PCD_RECEIVE				0x08	// activates the receiver circuits
#define	PCD_TRANSCEIVE 			0x0C	// transmits data from FIFO buffer to antenna and automatically activates the receiver after transmission
#define	PCD_MFAUTHENT 			0x0E	// performs the MIFARE standard authentication as a reader
#define	PCD_SOFTRESET			0x0F		// resets the MFRC522
