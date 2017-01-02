When you declare a ramfunc in your C, the linker will automatically reserve a block of RAM for the Kernel Program by setting the BMXDKPBA.  So if you want to make more space for your own RAM program with dynamically loading ability, you can shrink the LENGTH of kseg1_data_mem in the linker file.

// a dummy ram function to set the value of BMXDKPBA 
__attribute__((ramfunc,section(".ramfunc"),far,unique_section))
unsigned int myramfunct (void)
{ return 62499; }

in the linker file

/* add this line before the MEMORY{} block*/
__BMXDRMSZ = 0x8000;
...
/*kseg1_data_mem (w!x) : ORIGIN = 0xA0000000, LENGTH = 0x8000 */
kseg1_data_mem (w!x) : ORIGIN = 0xA0000000, LENGTH = 0x4000
...
_bmxdudba_address = __BMXDRMSZ; /* LENGTH(kseg1_data_mem) ; */
_bmxdupba_address = __BMXDRMSZ; /* LENGTH(kseg1_data_mem) ; */

 
