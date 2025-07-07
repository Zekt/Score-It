module App = {
  let style =
    ReactDOM.Style.make(~fontSize="1.5em", ~display="flex", ~gap="0.5em", ());

  type note = {x: int, y: int};

  let sheetStyle =
    ReactDOM.Style.make(~border="1px solid black", ~width="500px", ~height="300px", ~position="relative", ());

  let noteStyle =
    ReactDOM.Style.make(~width="10px", ~height="10px", ~backgroundColor="black", ~borderRadius="50%", ~position="absolute", ());

  [@react.component]
  let make = () => {

    let (notes, setNotes) = React.useState(() => []);
    let handleClick = _ => {
    //   let rect = ReactDOM.Dom.getBoundingClientRect(event.target);
    //   let x = event.clientX - rect.left;
    //   let y = event.clientY - rect.top;
    //   setNotes([...notes, {x, y}]);
      setNotes(notes => notes @ [{x: 0, y: 0}]);
    };

    <div style=sheetStyle onClick=handleClick>
      {notes
       |> List.map(note =>
            <div
              key={string_of_int(note.x) ++ "_" ++ string_of_int(note.y)}
              style={ReactDOM.Style.combine(noteStyle, ReactDOM.Style.make(~left=string_of_int(note.x) ++ "px", ~top=string_of_int(note.y) ++ "px", ()))} />)
       |> Array.of_list
       |> React.array}
    </div>;
  };
  // [@react.component]
  // let make = () =>
  //   <div>
  //     <h1> {React.string("melange-opam-template")} </h1>
  //     {["Hello " ++ World.name ++ "!", "This is ReasonReact!"]
  //      |> List.map(text =>
  //           <div key=text style>
  //             {React.string(text)}
  //             <button
  //               onClick={_ => text |> Speech.makeUtterance |> Speech.speak}>
  //               {React.string("speak")}
  //             </button>
  //           </div>
  //         )
  //      |> Array.of_list
  //      |> React.array}
  //   </div>;
};

let () =
  switch (ReactDOM.querySelector("#root")) {
  | None =>
    Js.Console.error("Failed to start React: couldn't find the #root element")
  | Some(element) =>
    let root = ReactDOM.Client.createRoot(element);
    ReactDOM.Client.render(root, <App />);
  };
