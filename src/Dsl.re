// LCM of all durations, time signature, etc.
let measureResolution = 288

type duration = Sixteenth | Eighth | Quarter | Half | Whole

type pitch = C4 | D4 | E4 | F4 | G4 | A4 | B4 | Rest | Sustain
	
// Position of note is represented by the total length between the start of measure and itself
type noteInfo = {
	duration: duration,
	pos: list(pitch) // a list of notes of maybe different pitches, none means Rest
}

// All time signatures share a same number of minimal units of measureResolution
type measureSig = FourFour | ThreeFour

// Any measure must have total notes length added up to measureResolution
type measure = {
 	timeSig: measureSig,
    notes: list(noteInfo)
}

let durationToUnit = (d: duration) => (s: measureSig): int => {
	switch (s) {
	| FourFour => {
		switch (d) {
		| Sixteenth => measureResolution/16;
		| Eighth => measureResolution/8;
		| Quarter => measureResolution/4;
		| Half => measureResolution/2;
		| Whole => measureResolution;
		}
	}
	| ThreeFour => {
		switch (d) {
		| Sixteenth => measureResolution/12;
		| Eighth => measureResolution/6;
		| Quarter => measureResolution/3;
		| Half => (measureResolution/3)*2;
		| Whole => measureResolution;
		}
	}
	}
}

let calcMeasure = (m: measure): int => {
	List.fold_left((i, n) => {
		i + durationToUnit(n.duration, m.timeSig);
	}, 0, m.notes);
}
