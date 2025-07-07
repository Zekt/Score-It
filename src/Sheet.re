// Sheet.re

// Define common constants for a single page of sheet music
type constants = {
    songName: string,
    timestamp: (int, int), // Common time signature
    numberOfLines: int, // Number of lines in the sheet music
    measuresPerLine: int, // Number of measures in each line
};


// type step = 
//   | Step(int) // 0 to 11, representing the 12 semitones in an octave, can go over or under
//   | Rest;
// 
// type note = Note(step, int); // Note with a step and length
// // | Sixteenth(step)
// // | Eighth(step)
// // | Quarter(step)
// // | Half(step)
// // | Whole(step)
// 
// type measure = {
//     notes: list((note, int)), // List of notes with their positions in the measure, 
//     resolutionn: int // Resolution of the measure, e.g., 16 for sixteenth notes
// };

type note = {x: int, y: int};
let noteStyle =
  ReactDOM.Style.make(~width="10px", ~height="10px", ~backgroundColor="black", ~borderRadius="50%", ~position="absolute", ());

module Sheet = {

  [@react.component]
  let make = (~nMeasures: int) => {
    //open ReactDOM;
    
    //let style = Style.make(~fontSize="1.5em", ~display="flex", ~gap="0.5em", ());
    
    let (notes, setNotes) = React.useState(() => []);

    let sheetStyle =
      ReactDOM.Style.make(~border="1px solid black", ~width="500px", ~height="300px", ~position="relative", ());

    let handleClick = (event: React.Event.Mouse.t) => {
      open Webapi.Dom;
      let bodyMargin = (ReactDOM.querySelector("body"));
      let (bodyTop, bodyLeft) = switch (bodyMargin) {
        | Some(e) => {
            let computedStyle = Window.getComputedStyle(e, window);
            let topMargin  = CssStyleDeclaration.marginTop(computedStyle);
            let leftMargin = CssStyleDeclaration.marginLeft(computedStyle);
            let top  = int_of_string(List.hd(String.split_on_char('p', topMargin)));
            let left = int_of_string(List.hd(String.split_on_char('p', leftMargin)));
            (top, left)
          }
        | None => (0, 0)
      };
      let x = React.Event.Mouse.pageX(event) - bodyLeft;
      let y = React.Event.Mouse.pageY(event) - bodyTop;
      setNotes(notes => [ {x, y}, ...notes]);
    };
    // Example of how to use the constants
    <div style=sheetStyle onClick=handleClick>
      {notes
       |> List.map(note =>
            <div
              key={string_of_int(note.x) ++ "_" ++ string_of_int(note.y)}
              style={ReactDOM.Style.combine(noteStyle, ReactDOM.Style.make(~left=string_of_int(note.x) ++ "px", ~top=string_of_int(note.y) ++ "px", ()))} />)
       |> Array.of_list
       |> React.array}
      {React.int(nMeasures)}
    </div>
  };

};
