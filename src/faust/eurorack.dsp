// Converts 1 V/oct to frequency in Hertz.
//
// The conversion formula is: 440 * 2 ^ (volts - 0.75)
// The factor 0.75 shifts 0 V to C-4 (261.6256 Hz)
cv_pitch2freq(cv_pitch) = cv_pitch , 0.75 : 2 , - : 440 , ^ : * : _;


// Converts frequency in Hertz to 1 V/oct.
//
// The conversion formula is: log2(hertz / 440) + 0.75
// The factor 0.75 shifts 0 V to C-4 (261.6256 Hz)
freq2cv_pitch(freq) = freq , 440 : / : ma.log2 , 0.75 : + : _;


// Converts 200 mV/oct to frequency in Hertz.
i_cv_pitch2freq(i_cv_pitch) = i_cv_pitch : internal2cv_pitch : cv_pitch2freq : _;


// Converts frequency in Hertz to 200 mV/oct.
freq2i_cv_pitch(freq) = freq : freq2cv_pitch : cv_pitch2internal : _;


// Converts Eurorack's 1 V/oct to internal 200 mv/oct.
cv_pitch2internal(cv_pitch) = cv_pitch , 5 : / : _;


// Converts internal 200 mv/oct to Eurorack's 1 V/oct.
internal2cv_pitch(i_cv_pitch) = i_cv_pitch , 5 : * : _;


// Converts Eurorack's CV (range of 10V) to internal CV (range of 1V)
cv2internal(cv) = cv , 10 : / : _;


// Converts internal CV (range of 1V) to Eurorack's CV (range of 10V)
internal2cv(i_cv) = i_cv , 10 : * : _;
