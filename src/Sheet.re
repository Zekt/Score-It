// Sheet.re

// Define common constants for a single page of sheet music
type constants = {
	songName: string,
	timestamp: (int, int), // Common time signature
	nLines: int,    // Number of lines in the sheet music
	measuresPerLine: int,  // Number of measures in each line
	resolution: int        // A common denominator between possible durations
};


// type step = 
//   | Step(int) // 0 to 11, representing the 12 semitones in an octave, can go over or under
//   | Rest;
// 
// type note = Note(step, int); // Note with a step and length
// | Sixteenth(step)
// | Eighth(step)
// | Quarter(step)
// | Half(step)
// | Whole(step)
// 
// type measure = {
//     notes: list((note, int)), // List of notes with their positions in the measure, 
//     resolutionn: int // Resolution of the measure, e.g., 16 for sixteenth notes
// };

type note = {x: int, y: int};

type duration =
Sixteenth
| Eighth
| Quarter
| Half
| Whole

// Position of note is represented by the total length between the start of measure and itself
type noteInfo = {
	measure: int,
	duration: duration,
	pos: list(duration)
}

//--- Styles
let noteStyle =
ReactDOM.Style.make(
	~width="10px",
	~height="10px",
	~backgroundColor="black",
	~borderRadius="50%",
	~position="absolute",
	());

let makeSheetStyle = (~width: int, ~height: int, ~constants: constants) => {
	let widthStr = string_of_int(width) ++ "px";
	let heightStr = string_of_int(height) ++ "px";
	ReactDOM.Style.make(
		~display="grid",
		~gridTemplateColumns=List.init(constants.measuresPerLine, _ => "1fr") |> String.concat(" "), 
		~border="1px solid black",
		~width=widthStr,
		~height=heightStr,
		~position="relative",
		~margin="auto",
		());
}

let measureStyle = ReactDOM.Style.make(
	~margin="0px",
	~border="1px solid black",
	~height="100px",
	());
//-----------

module Sheet = {
	[@react.component]
	let make = (~constants: constants) => {

		let (notes, setNotes) = React.useState(() => []);

		let sheetStyle = makeSheetStyle(~width=800, ~height=1000, ~constants=constants);

		let handleSheetClick = (event: React.Event.Mouse.t) => {
			open Webapi.Dom;
			let getMargin: string => (int, int) = s => {
				let elem = (ReactDOM.querySelector(s));
				switch (elem) {
					| Some(e) => {
						let computedStyle = Window.getComputedStyle(e, window);
						let topMargin  = CssStyleDeclaration.marginTop(computedStyle);
						let leftMargin = CssStyleDeclaration.marginLeft(computedStyle);
						let getPx = s => String.split_on_char('p', s) |> List.hd |> float_of_string |> int_of_float;
						(getPx(topMargin), getPx(leftMargin))
					  }
					| _ => (0, 0)
					}
			};
			let (bodyTop, bodyLeft) = getMargin("body");
			let (sheetTop, sheetLeft) = getMargin("#sheet");
			// Js.Console.log("body: " ++ string_of_int(bodyTop) ++ " " ++ string_of_int(bodyLeft));
			// Js.Console.log("sheet: " ++ string_of_int(sheetTop) ++ " " ++ string_of_int(sheetLeft));
			let x = React.Event.Mouse.pageX(event) - bodyLeft - sheetLeft;
			let y = React.Event.Mouse.pageY(event) - bodyTop - sheetTop;
			setNotes(notes => [ {x, y}, ...notes]);
		};
		<div id="sheet" key="sheet" style=sheetStyle onClick=handleSheetClick>
			{List.init(constants.measuresPerLine*constants.nLines,
					   _ => <div style=measureStyle></div>)
				|> Array.of_list |> React.array}
			{notes |> List.map(note =>
				<div key={string_of_int(note.x) ++ "_" ++ string_of_int(note.y)}
				     style={ReactDOM.Style.combine(noteStyle,
											       ReactDOM.Style.make(
											     	  ~left=string_of_int(note.x) ++ "px",
											     	  ~top=string_of_int(note.y) ++ "px",
											     	  ()))}
				/>)
				|> Array.of_list
				|> React.array}
		</div>
	};

};
