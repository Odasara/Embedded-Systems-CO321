void EEPROMwrite (unsigned int address, char data){
	//wait for completion of previous write
	while(EECR & (1<<EEPE));
	
	//set up address and data regs
	EEAR = address;
	EEDR = data;
	
	//write logical 1 to EEMPE
	EECR |= (1<<EEMPE);
	
	//start EEPROM write
	EECR |= (1<<EEPE);
}

char EEPROMread(unsigned int address){
	//wait for completion of writes
	while(EECR & (1<<EEPE));
	
	//set up address
	EEAR = address;
	
	//start EEPROM read
	EECR |= (1<<EERE);
	
	//return data
	return EEDR;
}
