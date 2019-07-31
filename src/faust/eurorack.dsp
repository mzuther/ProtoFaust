// Converts 1 V/oct to frequency in Hertz.
//
// The conversion formula is: 440 * 2 ^ (volts - 0.75)
// The factor 0.75 shifts 0 V to C-4 (261.6256 Hz)
volts2frequency(v_oct) = v_oct , 0.75 : 2 , - : 440 , ^ : * : _;


// Converts frequency in Hertz to 1 V/oct.
//
// The conversion formula is: log2(hertz / 440) + 0.75
// The factor 0.75 shifts 0 V to C-4 (261.6256 Hz)
frequency2volts(freq) = freq , 440 : / : ma.log2 , 0.75 : + : _;
